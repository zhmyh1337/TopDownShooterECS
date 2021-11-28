#pragma once
#include <vector>
#include <stdint.h>
namespace ecs
{
  typedef uint32_t uint;
  class EntityId;
  class EntityPull;

  class EntityPullIterator
  {
  private:
    const EntityPull &container;
    int bin, index;
  public:
    EntityPullIterator(const EntityPull &container, int bin, int index);

    bool operator!=(const EntityPullIterator &other) const;
    void operator++();
    EntityId eid() const;

  };
  class EntityPull
  {
    friend class EntityPullIterator;
    friend class EntityId;
    std::vector<uint*> entities;
    int totalCount, destroyCount, entityCapacity;
    uint *get_entity();
  public:
    EntityPull();
    ~EntityPull();
    void clear();
    EntityId create_entity(uint archetype, uint index);
    EntityId find_entity(int archetype, uint index);
    void destroy_entity(const EntityId &eid);
    EntityPullIterator begin() const;
    EntityPullIterator end() const;
  };
}