#include "common_ui.inl"
//Code-generator production

void fps_ui_func();

ecs::SystemDescription fps_ui_descr("fps_ui", {
}, fps_ui_func, ecs::SystemOrder::UI, (uint)(ecs::SystemTag::Game));

void fps_ui_func()
{
  for (ecs::QueryIterator begin = fps_ui_descr.begin(), end = fps_ui_descr.end(); begin != end; ++begin)
  {
    fps_ui(
    );
  }
}


void debug_console_ui_func();

ecs::SystemDescription debug_console_ui_descr("debug_console_ui", {
}, debug_console_ui_func, ecs::SystemOrder::UI, (uint)(ecs::SystemTag::Game));

void debug_console_ui_func()
{
  for (ecs::QueryIterator begin = debug_console_ui_descr.begin(), end = debug_console_ui_descr.end(); begin != end; ++begin)
  {
    debug_console_ui(
    );
  }
}



