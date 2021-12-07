#include "sound_system.inl"
//Code-generator production

void PlayAllSoundsFromQueue_func();

ecs::SystemDescription PlayAllSoundsFromQueue_descr("PlayAllSoundsFromQueue", {
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<Camera>("camera"), false}
}, PlayAllSoundsFromQueue_func, ecs::SystemOrder::LOGIC + 10, (uint)(ecs::SystemTag::Game));

void PlayAllSoundsFromQueue_func()
{
  for (ecs::QueryIterator begin = PlayAllSoundsFromQueue_descr.begin(), end = PlayAllSoundsFromQueue_descr.end(); begin != end; ++begin)
  {
    PlayAllSoundsFromQueue(
      *begin.get_component<AudioPool>(0),
      *begin.get_component<Camera>(1)
    );
  }
}



