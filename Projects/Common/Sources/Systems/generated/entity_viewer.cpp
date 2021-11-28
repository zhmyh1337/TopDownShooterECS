#include "entity_viewer.inl"
//Code-generator production

void entity_viewer_func();

ecs::SystemDescription entity_viewer_descr("entity_viewer", {
}, entity_viewer_func, ecs::SystemOrder::UI, (uint)(ecs::SystemTag::Game));

void entity_viewer_func()
{
  for (ecs::QueryIterator begin = entity_viewer_descr.begin(), end = entity_viewer_descr.end(); begin != end; ++begin)
  {
    entity_viewer(
    );
  }
}



