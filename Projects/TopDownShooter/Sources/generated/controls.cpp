#include "controls.inl"
//Code-generator production

void ProcessLocalPlayerMovement_func();

ecs::SystemDescription ProcessLocalPlayerMovement_descr("ProcessLocalPlayerMovement", {
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<bool>("isIdling"), false},
  {ecs::get_type_description<bool>("isRunning"), false},
  {ecs::get_type_description<float>("firstStepTime"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, ProcessLocalPlayerMovement_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void ProcessLocalPlayerMovement_func()
{
  for (ecs::QueryIterator begin = ProcessLocalPlayerMovement_descr.begin(), end = ProcessLocalPlayerMovement_descr.end(); begin != end; ++begin)
  {
    ProcessLocalPlayerMovement(
      *begin.get_component<vec2>(0),
      *begin.get_component<bool>(1),
      *begin.get_component<bool>(2),
      *begin.get_component<float>(3),
      *begin.get_component<GameData>(4)
    );
  }
}


void LocalPlayerViewToMouse_func();

ecs::SystemDescription LocalPlayerViewToMouse_descr("LocalPlayerViewToMouse", {
  {ecs::get_type_description<vec2>("viewDirection"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, LocalPlayerViewToMouse_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void LocalPlayerViewToMouse_func()
{
  for (ecs::QueryIterator begin = LocalPlayerViewToMouse_descr.begin(), end = LocalPlayerViewToMouse_descr.end(); begin != end; ++begin)
  {
    LocalPlayerViewToMouse(
      *begin.get_component<vec2>(0),
      *begin.get_component<Transform2D>(1),
      *begin.get_component<WorldRenderer>(2),
      *begin.get_component<GameData>(3)
    );
  }
}


void LocalPlayerShoot_func();

ecs::SystemDescription LocalPlayerShoot_descr("LocalPlayerShoot", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<int>("shootingState"), false},
  {ecs::get_type_description<float>("lastShotTime"), false},
  {ecs::get_type_description<bool>("canShoot"), false},
  {ecs::get_type_description<SpritesPool>("sp"), false},
  {ecs::get_type_description<SpriteSheetsPool>("ssp"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
}, LocalPlayerShoot_func, ecs::SystemOrder::LOGIC + 3, (uint)(ecs::SystemTag::Game));

void LocalPlayerShoot_func()
{
  for (ecs::QueryIterator begin = LocalPlayerShoot_descr.begin(), end = LocalPlayerShoot_descr.end(); begin != end; ++begin)
  {
    LocalPlayerShoot(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<int>(1),
      *begin.get_component<float>(2),
      *begin.get_component<bool>(3),
      *begin.get_component<SpritesPool>(4),
      *begin.get_component<SpriteSheetsPool>(5),
      *begin.get_component<AudioPool>(6),
      *begin.get_component<GameData>(7)
    );
  }
}


void ChangeZoom_handler(const MouseWheelEvent &event);

ecs::EventDescription<MouseWheelEvent> ChangeZoom_descr("ChangeZoom", {
  {ecs::get_type_description<Camera>("camera"), false}
}, ChangeZoom_handler, (uint)(ecs::SystemTag::Game));

void ChangeZoom_handler(const MouseWheelEvent &event)
{
  for (ecs::QueryIterator begin = ChangeZoom_descr.begin(), end = ChangeZoom_descr.end(); begin != end; ++begin)
  {
    ChangeZoom(
      event,
      *begin.get_component<Camera>(0)
    );
  }
}


void ChangeZoom_singl_handler(const MouseWheelEvent &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<MouseWheelEvent> ChangeZoom_singl_descr("ChangeZoom", {
  {ecs::get_type_description<Camera>("camera"), false}
}, ChangeZoom_singl_handler, (uint)(ecs::SystemTag::Game));

void ChangeZoom_singl_handler(const MouseWheelEvent &event, ecs::QueryIterator &begin)
{
  ChangeZoom(
    event,
      *begin.get_component<Camera>(0)
  );
}



