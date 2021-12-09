#include "game_logic.inl"
//Code-generator production

ecs::QueryDescription gatherEnemies_descr("gatherEnemies", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<vec2>("viewDirection"), false},
  {ecs::get_type_description<vec2>("roamingDestination"), false},
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
      *begin.get_component<vec2>(2),
      *begin.get_component<vec2>(3)
    );
  }
}


ecs::QueryDescription gatherLeavingEnemies_descr("gatherLeavingEnemies", {
  {ecs::get_type_description<vec2>("roamingDestination"), false},
  {ecs::get_type_description<int>("attackState"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
});

template<typename Callable>
void gatherLeavingEnemies(Callable lambda)
{
  for (ecs::QueryIterator begin = gatherLeavingEnemies_descr.begin(), end = gatherLeavingEnemies_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<vec2>(0),
      *begin.get_component<int>(1)
    );
  }
}


ecs::QueryDescription gatherAttackingEnemies_descr("gatherAttackingEnemies", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<float>("size"), false},
  {ecs::get_type_description<float>("lastAttackTime"), false},
  {ecs::get_type_description<int>("attackState"), false},
  {ecs::get_type_description<bool>("canDamage"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
});

template<typename Callable>
void gatherAttackingEnemies(Callable lambda)
{
  for (ecs::QueryIterator begin = gatherAttackingEnemies_descr.begin(), end = gatherAttackingEnemies_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<float>(1),
      *begin.get_component<float>(2),
      *begin.get_component<int>(3),
      *begin.get_component<bool>(4)
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
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, DirectEnemies_func, ecs::SystemOrder::LOGIC - 1, (uint)(ecs::SystemTag::Game));

void DirectEnemies_func()
{
  for (ecs::QueryIterator begin = DirectEnemies_descr.begin(), end = DirectEnemies_descr.end(); begin != end; ++begin)
  {
    DirectEnemies(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<GameData>(1)
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


void EnemiesAttack_func();

ecs::SystemDescription EnemiesAttack_descr("EnemiesAttack", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<SpriteSheetsPool>("ssp"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, EnemiesAttack_func, ecs::SystemOrder::LOGIC + 2, (uint)(ecs::SystemTag::Game));

void EnemiesAttack_func()
{
  for (ecs::QueryIterator begin = EnemiesAttack_descr.begin(), end = EnemiesAttack_descr.end(); begin != end; ++begin)
  {
    EnemiesAttack(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<SpriteSheetsPool>(1),
      *begin.get_component<GameData>(2)
    );
  }
}


void GameOver_handler(const GameOverEvent &event);

ecs::EventDescription<GameOverEvent> GameOver_descr("GameOver", {
  {ecs::get_type_description<bool>("isIdling"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, GameOver_handler, (uint)(ecs::SystemTag::Game));

void GameOver_handler(const GameOverEvent &event)
{
  for (ecs::QueryIterator begin = GameOver_descr.begin(), end = GameOver_descr.end(); begin != end; ++begin)
  {
    GameOver(
      event,
      *begin.get_component<bool>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<Transform2D>(2),
      *begin.get_component<GameData>(3),
      *begin.get_component<AudioPool>(4)
    );
  }
}


void LocalPlayerReceiveDamage_handler(const LocalPlayerReceiveDamageEvent &event);

ecs::EventDescription<LocalPlayerReceiveDamageEvent> LocalPlayerReceiveDamage_descr("LocalPlayerReceiveDamage", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<float>("health"), false},
  {ecs::get_type_description<float>("lastDamageReceivedTime"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, LocalPlayerReceiveDamage_handler, (uint)(ecs::SystemTag::Game));

void LocalPlayerReceiveDamage_handler(const LocalPlayerReceiveDamageEvent &event)
{
  for (ecs::QueryIterator begin = LocalPlayerReceiveDamage_descr.begin(), end = LocalPlayerReceiveDamage_descr.end(); begin != end; ++begin)
  {
    LocalPlayerReceiveDamage(
      event,
      *begin.get_component<Transform2D>(0),
      *begin.get_component<float>(1),
      *begin.get_component<float>(2),
      *begin.get_component<GameData>(3),
      *begin.get_component<AudioPool>(4)
    );
  }
}


void EnemyGotShot_handler(const EnemyGotShotEvent &event);

ecs::EventDescription<EnemyGotShotEvent> EnemyGotShot_descr("EnemyGotShot", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<float>("health"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
}, EnemyGotShot_handler, (uint)(ecs::SystemTag::Game));

void EnemyGotShot_handler(const EnemyGotShotEvent &event)
{
  for (ecs::QueryIterator begin = EnemyGotShot_descr.begin(), end = EnemyGotShot_descr.end(); begin != end; ++begin)
  {
    EnemyGotShot(
      event,
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<float>(1),
      *begin.get_component<GameData>(2),
      *begin.get_component<AudioPool>(3)
    );
  }
}


void GameOver_singl_handler(const GameOverEvent &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<GameOverEvent> GameOver_singl_descr("GameOver", {
  {ecs::get_type_description<bool>("isIdling"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, GameOver_singl_handler, (uint)(ecs::SystemTag::Game));

void GameOver_singl_handler(const GameOverEvent &event, ecs::QueryIterator &begin)
{
  GameOver(
    event,
      *begin.get_component<bool>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<Transform2D>(2),
      *begin.get_component<GameData>(3),
      *begin.get_component<AudioPool>(4)
  );
}


void LocalPlayerReceiveDamage_singl_handler(const LocalPlayerReceiveDamageEvent &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<LocalPlayerReceiveDamageEvent> LocalPlayerReceiveDamage_singl_descr("LocalPlayerReceiveDamage", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<float>("health"), false},
  {ecs::get_type_description<float>("lastDamageReceivedTime"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, LocalPlayerReceiveDamage_singl_handler, (uint)(ecs::SystemTag::Game));

void LocalPlayerReceiveDamage_singl_handler(const LocalPlayerReceiveDamageEvent &event, ecs::QueryIterator &begin)
{
  LocalPlayerReceiveDamage(
    event,
      *begin.get_component<Transform2D>(0),
      *begin.get_component<float>(1),
      *begin.get_component<float>(2),
      *begin.get_component<GameData>(3),
      *begin.get_component<AudioPool>(4)
  );
}


void EnemyGotShot_singl_handler(const EnemyGotShotEvent &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<EnemyGotShotEvent> EnemyGotShot_singl_descr("EnemyGotShot", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<float>("health"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
}, EnemyGotShot_singl_handler, (uint)(ecs::SystemTag::Game));

void EnemyGotShot_singl_handler(const EnemyGotShotEvent &event, ecs::QueryIterator &begin)
{
  EnemyGotShot(
    event,
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<float>(1),
      *begin.get_component<GameData>(2),
      *begin.get_component<AudioPool>(3)
  );
}



