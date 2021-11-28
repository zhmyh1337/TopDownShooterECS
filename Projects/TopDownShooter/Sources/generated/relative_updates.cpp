#include "relative_updates.inl"
//Code-generator production

void UpdateCameraPosition_func();

ecs::SystemDescription UpdateCameraPosition_descr("UpdateCameraPosition", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<Camera>("camera"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, UpdateCameraPosition_func, ecs::SystemOrder::LOGIC + 2, (uint)(ecs::SystemTag::Game));

void UpdateCameraPosition_func()
{
  for (ecs::QueryIterator begin = UpdateCameraPosition_descr.begin(), end = UpdateCameraPosition_descr.end(); begin != end; ++begin)
  {
    UpdateCameraPosition(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<Camera>(1)
    );
  }
}


void UpdateBackground_func();

ecs::SystemDescription UpdateBackground_descr("UpdateBackground", {
  {ecs::get_type_description<Sprite>("sprite"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<Camera>("camera"), false},
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<ecs::Tag>("background"), false}
}, UpdateBackground_func, ecs::SystemOrder::LOGIC + 3, (uint)(ecs::SystemTag::Game));

void UpdateBackground_func()
{
  for (ecs::QueryIterator begin = UpdateBackground_descr.begin(), end = UpdateBackground_descr.end(); begin != end; ++begin)
  {
    UpdateBackground(
      *begin.get_component<Sprite>(0),
      *begin.get_component<Transform2D>(1),
      *begin.get_component<Camera>(2),
      *begin.get_component<WorldRenderer>(3)
    );
  }
}



