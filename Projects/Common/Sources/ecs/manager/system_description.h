#pragma once
#include <iterator>
#include "../system_order.h"
#include "archetype.h"

namespace ecs
{
  struct FunctionArgument
  {
    TypeDescription descr;
    bool optional = false;
  };
  struct SystemCashedArchetype
  {
    Archetype *archetype;
    std::vector<ComponentContainer*> containers;
    SystemCashedArchetype(Archetype *archetype, std::vector<ComponentContainer*> &&containers);
  };

  struct QueryIterator;

  struct QueryDescription
  {
    std::string name;
    std::vector<FunctionArgument> args;
    std::vector<SystemCashedArchetype> archetypes;
    void (*function)();
    bool withoutArgs;
    QueryDescription(const char *name, const std::vector<FunctionArgument> &args, bool query = true);
    QueryIterator begin();
    QueryIterator end();
  };
  struct SingleQueryDescription
  {
    std::string name;
    std::vector<FunctionArgument> args;
    std::vector<SystemCashedArchetype> archetypes;
    void (*function)();
    bool withoutArgs;
    SingleQueryDescription(const char *name, const std::vector<FunctionArgument> &args, bool query = true);
    QueryIterator begin();
    QueryIterator end();
  };
  struct SystemDescription : QueryDescription
  {
    void (*function)();
    int order;
    uint tags;
    SystemDescription(const char *name, const std::vector<FunctionArgument> &args, void (*function_pointer)(), int order, uint tags);
    void execute();
  };

  
  struct QueryIterator
  {
    friend struct QueryDescription;
  public:
    QueryIterator();
    QueryIterator(const QueryDescription *query, int archetype, int component);

    bool operator!=(const QueryIterator &other) const;
    void operator++();
    template<typename T>
    T *get_component(int ind)
    {
      if constexpr (is_singleton<T>::value)
        return &get_singleton<T>();
      else
        return query->archetypes[archetypeIndex].containers[ind]->get_component<T>(componentIndex);
    }
  private:
    const QueryDescription *query;
    int archetypeIndex;
    int componentIndex;
    void skip_empty_archetype();
  };
}