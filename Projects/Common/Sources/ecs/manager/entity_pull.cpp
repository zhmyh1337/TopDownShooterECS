#include "entity_pull.h"
#include "entity_id.h"

namespace ecs
{
  

  constexpr uint entityBinSize = 200;

  EntityPullIterator::EntityPullIterator(const EntityPull &container, int bin, int index):
  container(container), bin(bin), index(index){}

  bool EntityPullIterator::operator!=(const EntityPullIterator &other) const
  {
    return bin != other.bin || index != other.index;
  }
  void EntityPullIterator::operator++()
  {
    index++;
    if (index == entityBinSize)
    {
      index = 0;
      bin++;
    }
  }
  EntityId EntityPullIterator::eid() const
  {
    return EntityId(&container.entities[bin][index]);
  }




  EntityPull::EntityPull():
  entities(), totalCount(0), destroyCount(0), entityCapacity(0)
  {

  }
  EntityPull::~EntityPull()
  {
    for (uint *bins : entities)
      free(bins);
  }
  void EntityPull::clear()
  {
    totalCount = 0;
    destroyCount = 0;
  }
  uint *EntityPull::get_entity()
  {
    if (totalCount == entityCapacity)
    {
      entities.push_back((uint*)malloc(entityBinSize * sizeof(uint)));
      entityCapacity += entityBinSize;
    }
    uint *eid = entities[totalCount / entityBinSize] + (totalCount % entityBinSize);
    return eid;
  }
  EntityId EntityPull::create_entity(uint archetype, uint index)
  {
    uint *entity = get_entity();
    totalCount++;
    return EntityId(entity, archetype, index);
  }
  EntityId EntityPull::find_entity(int archetype, uint index)
  {
    if (archetype >= 0)
    {
      for (auto it = begin(), e = end(); it != e; ++it)
      {
        const EntityId &eid = it.eid();
        if (eid.archetype_index() == (int)archetype && eid.array_index() == index)
          return eid;
      }
    }
    return EntityId();
  }
  void EntityPull::destroy_entity(const EntityId &eid)
  {
    if (eid)
    {
      *eid.eid = bad_eid;
      destroyCount++;
    }
  }
  EntityPullIterator EntityPull::begin() const
  {
    return EntityPullIterator(*this, 0, 0);
  }
  EntityPullIterator EntityPull::end() const
  {
    return EntityPullIterator(*this, totalCount / entityBinSize, totalCount % entityBinSize);
  }
}