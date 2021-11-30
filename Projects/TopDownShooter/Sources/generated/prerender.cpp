#include "prerender.inl"
//Code-generator production

ecs::QueryDescription getDebugCircle_descr("getDebugCircle", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<int>("id"), false},
  {ecs::get_type_description<ecs::Tag>("debugCircle"), false}
});

template<typename Callable>
void getDebugCircle(Callable lambda)
{
  for (ecs::QueryIterator begin = getDebugCircle_descr.begin(), end = getDebugCircle_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<int>(1)
    );
  }
}


ecs::QueryDescription getSoldierFeet_descr("getSoldierFeet", {
  {ecs::get_type_description<Sprite>("sprite"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("soldierFeet"), false}
});

template<typename Callable>
void getSoldierFeet(Callable lambda)
{
  for (ecs::QueryIterator begin = getSoldierFeet_descr.begin(), end = getSoldierFeet_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Sprite>(0),
      *begin.get_component<Transform2D>(1)
    );
  }
}


ecs::QueryDescription getSoldierBody_descr("getSoldierBody", {
  {ecs::get_type_description<Sprite>("sprite"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("soldierBody"), false}
});

template<typename Callable>
void getSoldierBody(Callable lambda)
{
  for (ecs::QueryIterator begin = getSoldierBody_descr.begin(), end = getSoldierBody_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Sprite>(0),
      *begin.get_component<Transform2D>(1)
    );
  }
}


void UpdateSoldierParts_func();

ecs::SystemDescription UpdateSoldierParts_descr("UpdateSoldierParts", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<bool>("isIdling"), false},
  {ecs::get_type_description<bool>("isRunning"), false},
  {ecs::get_type_description<float>("firstStepTime"), false},
  {ecs::get_type_description<int>("shootingState"), false},
  {ecs::get_type_description<SpritesPool>("sp"), false},
  {ecs::get_type_description<SpriteSheetsPool>("ssp"), false},
  {ecs::get_type_description<ecs::Tag>("soldier"), false}
}, UpdateSoldierParts_func, ecs::SystemOrder::RENDER - 1, (uint)(ecs::SystemTag::Game));

void UpdateSoldierParts_func()
{
  for (ecs::QueryIterator begin = UpdateSoldierParts_descr.begin(), end = UpdateSoldierParts_descr.end(); begin != end; ++begin)
  {
    UpdateSoldierParts(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<bool>(1),
      *begin.get_component<bool>(2),
      *begin.get_component<float>(3),
      *begin.get_component<int>(4),
      *begin.get_component<SpritesPool>(5),
      *begin.get_component<SpriteSheetsPool>(6)
    );
  }
}



