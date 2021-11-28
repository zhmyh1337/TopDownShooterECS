#include "camera_update.inl"
//Code-generator production

void move_camera_func();

ecs::SystemDescription move_camera_descr("move_camera", {
  {ecs::get_type_description<Camera>("camera"), false}
}, move_camera_func, ecs::SystemOrder::RENDER - 2, (uint)(ecs::SystemTag::Game));

void move_camera_func()
{
  for (ecs::QueryIterator begin = move_camera_descr.begin(), end = move_camera_descr.end(); begin != end; ++begin)
  {
    move_camera(
      *begin.get_component<Camera>(0)
    );
  }
}


void setup_background_func();

ecs::SystemDescription setup_background_descr("setup_background", {
  {ecs::get_type_description<Sprite>("sprite"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<Camera>("camera"), false},
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<ecs::Tag>("background"), false}
}, setup_background_func, ecs::SystemOrder::RENDER - 1, (uint)(ecs::SystemTag::Game));

void setup_background_func()
{
  for (ecs::QueryIterator begin = setup_background_descr.begin(), end = setup_background_descr.end(); begin != end; ++begin)
  {
    setup_background(
      *begin.get_component<Sprite>(0),
      *begin.get_component<Transform2D>(1),
      *begin.get_component<Camera>(2),
      *begin.get_component<WorldRenderer>(3)
    );
  }
}


void change_zoom_handler(const MouseWheelEvent &event);

ecs::EventDescription<MouseWheelEvent> change_zoom_descr("change_zoom", {
  {ecs::get_type_description<Camera>("camera"), false}
}, change_zoom_handler, (uint)(ecs::SystemTag::Game));

void change_zoom_handler(const MouseWheelEvent &event)
{
  for (ecs::QueryIterator begin = change_zoom_descr.begin(), end = change_zoom_descr.end(); begin != end; ++begin)
  {
    change_zoom(
      event,
      *begin.get_component<Camera>(0)
    );
  }
}


void change_zoom_singl_handler(const MouseWheelEvent &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<MouseWheelEvent> change_zoom_singl_descr("change_zoom", {
  {ecs::get_type_description<Camera>("camera"), false}
}, change_zoom_singl_handler, (uint)(ecs::SystemTag::Game));

void change_zoom_singl_handler(const MouseWheelEvent &event, ecs::QueryIterator &begin)
{
  change_zoom(
    event,
      *begin.get_component<Camera>(0)
  );
}



