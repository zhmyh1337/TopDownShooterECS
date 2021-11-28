#include "archetype.h"
#include "entity_pull.h"
#include "../ecs_event.h"
namespace ecs
{
  static ComponentContainer *dummyContainer = new ComponentContainer();

  Archetype::Archetype(int count, const string &synonim, int type_count):
    components(), count(count), capacity(count), fullTypeDescriptions(type_count), synonim(synonim)
  {}
  
  Archetype::Archetype(const vector<string_hash> &type_hashes, int capacity, const string &synonim):
    components(), count(0), capacity(capacity), fullTypeDescriptions(), synonim(synonim)
  {
    for (string_hash typeNameHash : type_hashes)
    {
      auto it = full_description().find(typeNameHash);
      assert(it->first && "Don't found full descr for type in Archetype");
      auto typeIt = TypeInfo::types().find(it->second.typeHash);
      assert(typeIt->first && "Don't found this type");
      fullTypeDescriptions.push_back(&it->second);
      components.try_emplace(typeNameHash, typeIt->second.hashId, typeNameHash, capacity, typeIt->second.sizeOf);
    }    
  }

  bool Archetype::in_archetype(const vector<string_hash> &type_hashes) const
  {
    if (type_hashes.size() != components.size())
      return false;
    for (string_hash descr : type_hashes)
    {
      auto it = components.find(descr);
      if (it == components.end())
        return false;
    }
    return true;
  }
  ComponentContainer *Archetype::get_container(const TypeDescription &type)
  {
    auto it = components.find(type.type_name_hash());
    return it == components.end() ? dummyContainer : &it->second;
  }
  template<typename T>
  ComponentContainer *Archetype::get_container(const char *name)
  {
    auto it = components.find(TypeDescription::typeDescriptionHash<T>(name));
    return it == components.end() ? dummyContainer : &it->second;
  }

  vector<void*> Archetype::get_entity_data(const vector<string_hash> &type_hashes)
  {
    vector<void*> data(type_hashes.size());
    for (uint i = 0; i < type_hashes.size(); i++)
      data[i] = components[type_hashes[i]].add_component();
    return data;
  }
  void Archetype::destroy_entity(int index, bool with_swap)
  {
    if (count > 0)
    for (auto &container : components)
    {
      container.second.destroy_component(index, with_swap);
    }
    count--;
    if (with_swap && index != count)
    {
      EntityId &eid = *components[get_type_description<EntityId>("eid").type_name_hash()]
      .get_component<EntityId>(index);
      eid.migrate(eid.archetype_index(), index);
    }
    if (count < 0)
    { 
      debug_error("count < 0 in %s", synonim.c_str());
    }
  }


}