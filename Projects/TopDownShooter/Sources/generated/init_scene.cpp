#include "init_scene.inl"
//Code-generator production

void InitScene_handler(const ecs::OnSceneCreated &event);

ecs::EventDescription<ecs::OnSceneCreated> InitScene_descr("InitScene", {
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<SpriteFactory>("sf"), false},
  {ecs::get_type_description<Camera>("camera"), false}
}, InitScene_handler, (uint)(ecs::SystemTag::Game));

void InitScene_handler(const ecs::OnSceneCreated &event)
{
  for (ecs::QueryIterator begin = InitScene_descr.begin(), end = InitScene_descr.end(); begin != end; ++begin)
  {
    InitScene(
      event,
      *begin.get_component<WorldRenderer>(0),
      *begin.get_component<SpriteFactory>(1),
      *begin.get_component<Camera>(2)
    );
  }
}


void InitScene_singl_handler(const ecs::OnSceneCreated &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<ecs::OnSceneCreated> InitScene_singl_descr("InitScene", {
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<SpriteFactory>("sf"), false},
  {ecs::get_type_description<Camera>("camera"), false}
}, InitScene_singl_handler, (uint)(ecs::SystemTag::Game));

void InitScene_singl_handler(const ecs::OnSceneCreated &event, ecs::QueryIterator &begin)
{
  InitScene(
    event,
      *begin.get_component<WorldRenderer>(0),
      *begin.get_component<SpriteFactory>(1),
      *begin.get_component<Camera>(2)
  );
}



