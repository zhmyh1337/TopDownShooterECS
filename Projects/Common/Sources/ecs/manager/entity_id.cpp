#include "entity_id.h"
#include <assert.h>
#include "common.h"
namespace ecs
{
  constexpr uint index_mask = 0x000fffff;
  constexpr uint index_shift = 20u;
  EntityId::EntityId():
    eid(nullptr){}
    EntityId::EntityId(uint *id):
    eid(id){}
  EntityId::EntityId(uint *id, uint archetype, uint index):
    eid(id)
  {
    migrate(archetype, index);
  }
  EntityId::EntityId(const EntityId &id):
    eid(id.eid){}
  EntityId::EntityId(EntityId &&id):
    eid(id.eid)
  {
    id.eid = nullptr;
  }
  bool EntityId::valid() const
  {
    return eid != nullptr && *eid != bad_eid;
  }
  EntityId::operator bool() const
  {
    return valid();
  }
  EntityId &EntityId::operator= (const EntityId &id)
  {
    eid = id.eid;
    return *this;
  }
  bool EntityId::operator== (const EntityId &id)
  {
    return eid == id.eid;
  }
  bool EntityId::operator!= (const EntityId &id)
  {
    return !(*this == id);
  }
  void EntityId::migrate(uint archetype, uint index)
  {
    assert((index & index_mask) == index && "There are a lot of entities in archetype");
    assert(((archetype << index_shift) >> index_shift) == archetype && "Not enought archetypes bits");

    *eid = index | (archetype << index_shift);
  }
  int EntityId::archetype_index() const
  {
    return valid() ? *eid >> index_shift : -1;
  }
  uint EntityId::array_index() const
  {
    return valid() ? *eid & index_mask : 0;
  }

}