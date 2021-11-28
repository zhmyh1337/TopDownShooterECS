#include "physics.inl"
//Code-generator production

void MoveEntitiesWithVelocity_func();

ecs::SystemDescription MoveEntitiesWithVelocity_descr("MoveEntitiesWithVelocity", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false}
}, MoveEntitiesWithVelocity_func, ecs::SystemOrder::LOGIC + 1, (uint)(ecs::SystemTag::Game));

void MoveEntitiesWithVelocity_func()
{
  for (ecs::QueryIterator begin = MoveEntitiesWithVelocity_descr.begin(), end = MoveEntitiesWithVelocity_descr.end(); begin != end; ++begin)
  {
    MoveEntitiesWithVelocity(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1)
    );
  }
}



