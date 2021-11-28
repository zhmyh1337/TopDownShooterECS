#include "system_description.h"
#include "core_interface.h"
namespace ecs
{
  SystemCashedArchetype::SystemCashedArchetype(Archetype *archetype, std::vector<ComponentContainer*> &&containers):
    archetype(archetype), containers(containers){}

  SystemDescription::SystemDescription(const char *name, const std::vector<FunctionArgument> &args, 
    void (*function_pointer)(), int order, uint tags):
    QueryDescription(name, args, false),
    function(function_pointer),
    order(order),
    tags(tags)
  {
    add_system(this);
  }
  void SystemDescription::execute()
  {
    function();
  }


  QueryDescription::QueryDescription(const char *name, const std::vector<FunctionArgument> &in_args, bool query):
    name(name), args(std::move(in_args)), archetypes()
  {
    if (query)
      add_query(this);
    withoutArgs = true;
    for (auto &arg : args)
      if(arg.descr.type_name_hash())
        withoutArgs = false;
  }
  SingleQueryDescription::SingleQueryDescription(const char *name, const std::vector<FunctionArgument> &in_args, bool query):
    name(name), args(std::move(in_args)), archetypes()
  {
    if (query)
      add_query((QueryDescription*)this);
    withoutArgs = true;
    for (auto &arg : args)
      if(arg.descr.type_name_hash())
        withoutArgs = false;
  }

  QueryIterator QueryDescription::begin()
  {
    QueryIterator it(this, 0, 0);
    if (!withoutArgs)
      it.skip_empty_archetype();
    return it;
  }
  QueryIterator QueryDescription::end()
  {
    return !withoutArgs ? QueryIterator(this, archetypes.size(), 0) : QueryIterator(this, 0, 1);
  }

  QueryIterator::QueryIterator():
  query(nullptr), archetypeIndex(-1), componentIndex(0){}

  QueryIterator::QueryIterator(const QueryDescription *query, int archetype, int component):
    query(query), archetypeIndex(archetype), componentIndex(component){}


  bool QueryIterator::operator!=(QueryIterator const& other) const
  {
    return archetypeIndex != other.archetypeIndex || componentIndex != other.componentIndex;
  }
  void QueryIterator::operator++()
  {
    componentIndex++;
    skip_empty_archetype();
  }

  void QueryIterator::skip_empty_archetype()
  {
    while ((uint)archetypeIndex < query->archetypes.size() && query->archetypes[archetypeIndex].archetype->count <= componentIndex)
    {
      componentIndex = 0;
      archetypeIndex++;
    }
  }
}