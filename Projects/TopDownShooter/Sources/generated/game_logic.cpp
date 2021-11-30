#include "game_logic.inl"
//Code-generator production

ecs::QueryDescription gatherEnemies_descr("gatherEnemies", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<vec2>("viewDirection"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
});

template<typename Callable>
void gatherEnemies(Callable lambda)
{
  for (ecs::QueryIterator begin = gatherEnemies_descr.begin(), end = gatherEnemies_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<vec2>(2)
    );
  }
}


void SpawnEnemies_func();

ecs::SystemDescription SpawnEnemies_descr("SpawnEnemies", {
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<Camera>("camera"), false}
}, SpawnEnemies_func, ecs::SystemOrder::LOGIC - 2, (uint)(ecs::SystemTag::Game));

void SpawnEnemies_func()
{
  for (ecs::QueryIterator begin = SpawnEnemies_descr.begin(), end = SpawnEnemies_descr.end(); begin != end; ++begin)
  {
    SpawnEnemies(
      *begin.get_component<GameData>(0),
      *begin.get_component<Camera>(1)
    );
  }
}


void DirectEnemies_func();

ecs::SystemDescription DirectEnemies_descr("DirectEnemies", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, DirectEnemies_func, ecs::SystemOrder::LOGIC - 1, (uint)(ecs::SystemTag::Game));

void DirectEnemies_func()
{
  for (ecs::QueryIterator begin = DirectEnemies_descr.begin(), end = DirectEnemies_descr.end(); begin != end; ++begin)
  {
    DirectEnemies(
      *begin.get_component<Transform2D>(0)
    );
  }
}


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



