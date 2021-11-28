#include <algorithm>
#include "Application/application_data.h"
#include "ecs_core.h"
#include "ecs_event.h"
#include "manager/system_description.h"
#include "common.h"
#include "manager/entity_container.h"
#define ECS_DEBUG_INFO 0
namespace ecs
{
  Core::Core()
  {
    entityContainer = new EntityContainer();
  }
  
  Core::~Core()
  {
  }
  Core &core()
  {
    static Core *singleton = new Core();
    return *singleton;
  }
  void Core::destroy_entities()
  {
    for (auto it = entityContainer->entityPull.begin(), end = entityContainer->entityPull.end(); it != end; ++it)
    {
      EntityId eid = it.eid();
      if (eid)
      {
#if ECS_DEBUG_INFO
        debug_log("add %d %d entity to destroy queue", eid.archetype_index(), eid.array_index());
#endif
        send_event_immediate(eid, OnEntityDestroyed());
        toDestroy.push(eid);
      }
    }
    entityContainer->entityPull.clear();
  }

  void register_archetype(Archetype *archetype);
  void Core::replace_entity_container(EntityContainer *container)
  {
    core().events = {};
    for (QueryDescription *query: core().queries)
      query->archetypes.clear();
    for (SystemDescription *system: core().systems)
      system->archetypes.clear();
    for (QueryDescription *system: core().event_queries)
      system->archetypes.clear();
    entityContainer = container;
    for (Archetype *archetype : container->archetypes)
      register_archetype(archetype);
  }

  static void register_archetype_to(QueryDescription *query, Archetype *archetype)
  {
    if (query->withoutArgs)
      return;
    std::vector<SystemCashedArchetype> &sys_archetypes = query->archetypes;
    std::vector<ComponentContainer*> containers(query->args.size());
    bool breaked = false;
    int i = 0;
    for(auto& arg : query->args)
    {
      if (arg.descr.type_name_hash() != 0)//singleton case
      {
        ComponentContainer* container = archetype->get_container(arg.descr);
        if (!arg.optional)
        {
          if (container == nullptr || container->typeNameHash != arg.descr.type_name_hash())
          {
            breaked = true;
            break;
          }
        }
        containers[i] = container;
      }
      i++;
    }
    if (!breaked)
    {
      sys_archetypes.emplace_back(archetype, std::move(containers));
#if ECS_DEBUG_INFO
      debug_log("processed by %s",query->name.c_str());
#endif
    }
  }

  
  void register_archetype(Archetype *archetype)
  {
    
#if ECS_DEBUG_INFO
    debug_log("register archetype");
    for (const auto &component : archetype->components)
    {
      auto &ecsType = core().types[component.first];
      auto &cppType = TypeInfo::types()[ecsType.typeHash];
      debug_log("  %s %s",cppType.name.c_str(), ecsType.name.c_str());
    }
#endif
    for (QueryDescription *query: core().queries)
      register_archetype_to(query, archetype);
    for (SystemDescription *system: core().systems)
      register_archetype_to(system, archetype);
    for (QueryDescription *system: core().event_queries)
      register_archetype_to(system, archetype);
    
  }
  Archetype *add_archetype(const vector<string_hash> &type_hashes, int capacity, const string &synonim)
  {
    Archetype *archetype = new Archetype(type_hashes, capacity, synonim);
    core().entityContainer->archetypes.push_back(archetype);

    register_archetype(archetype);
    
    return archetype;
  }

  
  pair<EntityId, Archetype&> add_entity(const vector<string_hash> & type_hashes)
  {
    Archetype *found_archetype = nullptr;
    int archetype_ind = 0;
    for (Archetype *archetype : core().entityContainer->archetypes)
    {
      if (archetype->in_archetype(type_hashes))
      {
        found_archetype = archetype;
        break;
      }
      archetype_ind++;
    }
    if (!found_archetype)
    {
      found_archetype = add_archetype(type_hashes, 1, "template[" + to_string(core().entityContainer->archetypes.size()) + "]");
    }
    int index = found_archetype->count++;
    return {core().entityContainer->entityPull.create_entity(archetype_ind, index), *found_archetype};
  }

  void destroy_entity(const EntityId &eid)
  {
    if (eid)
    {
      send_event_immediate(eid, OnEntityDestroyed());
      core().toDestroy.push(eid);
    }
    else
      assert(0);
  }
  void destroy_scene()
  {    
    core().destroy_entities();
    core().events = {};
    Application::instance().sceneManager.destroy_entities(false);
  }

  EntityId find_entity(uint archetype, uint index)
  {
    return core().entityContainer->entityPull.find_entity(archetype, index);
  }

  bool get_iterator(const QueryDescription &descr, const EntityId &eid, QueryIterator &iterator)
  {
    if (eid)
    {
      int index = eid.array_index();
      int archetypeInd = eid.archetype_index();
      Archetype *archetype = core().entityContainer->archetypes[archetypeInd];

      auto it = std::find_if(descr.archetypes.begin(), descr.archetypes.end(),
        [archetype](const SystemCashedArchetype &cashed_archetype){return cashed_archetype.archetype == archetype;});
      if (it != descr.archetypes.end())
      {
        iterator = QueryIterator(&descr, it - descr.archetypes.begin(), index);
        return true;
      }
    }
    return false;
  }
  bool get_iterator(const SingleQueryDescription &descr, const EntityId &eid, QueryIterator &iterator)
  {
    return get_iterator((const QueryDescription &)descr, eid, iterator);
  }

  void system_statistic()
  {
    debug_log("\nSystems statistics");
    for (const SystemDescription *descr : core().systems)
    {
      int archetypesCount = descr->archetypes.size();
      debug_log("%s has %d archetypes", descr->name.c_str(), archetypesCount);
      printf("{\n");
      for (const SystemCashedArchetype &archetype : descr->archetypes)
      {
        printf("---\n");
        for (const auto &component : archetype.archetype->components)
        {
          auto &ecsType = core().types[component.first];
          auto &cppType = TypeInfo::types()[ecsType.typeHash];
          printf("  %s %s\n",cppType.name.c_str(), ecsType.name.c_str());
        }
      }
      printf("}\n");
    }
  }
}

