#include "physics.inl"
//Code-generator production

ecs::QueryDescription gatherTargets_descr("gatherTargets", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
});

template<typename Callable>
void gatherTargets(Callable lambda)
{
  for (ecs::QueryIterator begin = gatherTargets_descr.begin(), end = gatherTargets_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<Transform2D>(1)
    );
  }
}


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


void BulletCollisionDetection_func();

ecs::SystemDescription BulletCollisionDetection_descr("BulletCollisionDetection", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<ecs::Tag>("bullet"), false}
}, BulletCollisionDetection_func, ecs::SystemOrder::LOGIC + 2, (uint)(ecs::SystemTag::Game));

void BulletCollisionDetection_func()
{
  for (ecs::QueryIterator begin = BulletCollisionDetection_descr.begin(), end = BulletCollisionDetection_descr.end(); begin != end; ++begin)
  {
    BulletCollisionDetection(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<Transform2D>(1),
      *begin.get_component<GameData>(2)
    );
  }
}



