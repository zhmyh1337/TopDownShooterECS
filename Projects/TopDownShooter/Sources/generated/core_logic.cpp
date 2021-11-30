#include "core_logic.inl"
//Code-generator production

void DestroyOldBullets_func();

ecs::SystemDescription DestroyOldBullets_descr("DestroyOldBullets", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<float>("creationTime"), false},
  {ecs::get_type_description<ecs::Tag>("bullet"), false}
}, DestroyOldBullets_func, ecs::SystemOrder::LOGIC - 1, (uint)(ecs::SystemTag::Game));

void DestroyOldBullets_func()
{
  for (ecs::QueryIterator begin = DestroyOldBullets_descr.begin(), end = DestroyOldBullets_descr.end(); begin != end; ++begin)
  {
    DestroyOldBullets(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<float>(1)
    );
  }
}



