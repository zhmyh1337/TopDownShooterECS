#include "controls.inl"
//Code-generator production

void ProcessLocalPlayerMovement_func();

ecs::SystemDescription ProcessLocalPlayerMovement_descr("ProcessLocalPlayerMovement", {
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<bool>("isIdling"), false},
  {ecs::get_type_description<bool>("isRunning"), false},
  {ecs::get_type_description<float>("firstStepTime"), false},
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
      *begin.get_component<float>(3)
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



