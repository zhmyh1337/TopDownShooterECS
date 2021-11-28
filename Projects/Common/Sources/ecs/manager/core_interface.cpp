#include "core_interface.h"
#include "../ecs_core.h"
#include "entity_container.h"
namespace ecs
{
  uint type_sizeof(uint type)
  {
    return TypeInfo::types()[type].sizeOf;
  }
  Constructor copy_constructor(uint type)
  {
    return TypeInfo::types()[type].constructor;
  }
  CopyConstructor type_copy_constructor(uint type)
  {
    return TypeInfo::types()[type].copy_constructor;
  }
  Destructor type_destructor(uint type)
  {
    return TypeInfo::types()[type].destructor;
  }

  void add_system(SystemDescription *system_description)
  {
    core().systems.push_back(system_description);
  }
  void add_query(QueryDescription *query_description)
  {
    core().queries.push_back(query_description);
  }




  std::unordered_map<uint, FullTypeDescription> &full_description()
  {
    return core().types;
  }
  void print_archetypes()
  {   
    printf("\n- - - - - \n");
    for (const Archetype *archetype : core().entityContainer->archetypes)
    {
      printf("{\n");
      for (const auto &descr : archetype->components)
      {
        auto &ecsType = core().types[descr.first];
        auto &cppType = TypeInfo::types()[descr.second.typeHash];
        printf("  %s %s\n",cppType.name.c_str(), ecsType.name.c_str());
      }

      printf("},\n");
    }
    std::fflush(stdout);
  }
}