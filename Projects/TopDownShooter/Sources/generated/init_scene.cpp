#include "init_scene.inl"
//Code-generator production

void InitScene_handler(const ecs::OnSceneCreated &event);

ecs::EventDescription<ecs::OnSceneCreated> InitScene_descr("InitScene", {
  {ecs::get_type_description<TexturesPool>("tp"), false},
  {ecs::get_type_description<SpritesPool>("sp"), false},
  {ecs::get_type_description<SpriteSheetsPool>("ssp"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<SoundEffectsFactory>("sef"), false}
}, InitScene_handler, (uint)(ecs::SystemTag::Game));

void InitScene_handler(const ecs::OnSceneCreated &event)
{
  for (ecs::QueryIterator begin = InitScene_descr.begin(), end = InitScene_descr.end(); begin != end; ++begin)
  {
    InitScene(
      event,
      *begin.get_component<TexturesPool>(0),
      *begin.get_component<SpritesPool>(1),
      *begin.get_component<SpriteSheetsPool>(2),
      *begin.get_component<AudioPool>(3),
      *begin.get_component<SoundEffectsFactory>(4)
    );
  }
}


void InitScene_singl_handler(const ecs::OnSceneCreated &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<ecs::OnSceneCreated> InitScene_singl_descr("InitScene", {
  {ecs::get_type_description<TexturesPool>("tp"), false},
  {ecs::get_type_description<SpritesPool>("sp"), false},
  {ecs::get_type_description<SpriteSheetsPool>("ssp"), false},
  {ecs::get_type_description<AudioPool>("ap"), false},
  {ecs::get_type_description<SoundEffectsFactory>("sef"), false}
}, InitScene_singl_handler, (uint)(ecs::SystemTag::Game));

void InitScene_singl_handler(const ecs::OnSceneCreated &event, ecs::QueryIterator &begin)
{
  InitScene(
    event,
      *begin.get_component<TexturesPool>(0),
      *begin.get_component<SpritesPool>(1),
      *begin.get_component<SpriteSheetsPool>(2),
      *begin.get_component<AudioPool>(3),
      *begin.get_component<SoundEffectsFactory>(4)
  );
}



