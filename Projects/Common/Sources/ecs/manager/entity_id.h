#pragma once
#include <stdlib.h>
#include <vector>
#include "common.h"
namespace ecs
{
  class EntityId
  {
  private:
    friend class EntityPull;
    uint *eid;//archetype index + index in archetype
  public:
    EntityId();
    EntityId(uint *id);
    EntityId(uint *id, uint archetype, uint index);
    void migrate(uint archetype, uint index);
    EntityId(const EntityId &id);
    EntityId(EntityId &&id);
    bool valid() const;
    int archetype_index() const;
    uint array_index() const;
    operator bool() const;
    EntityId &operator= (const EntityId &id);
    bool operator== (const EntityId &id);
    bool operator!= (const EntityId &id);

  };
  constexpr uint bad_eid = 0xffffffff;

}