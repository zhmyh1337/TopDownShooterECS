#include "init_game.inl"
//Code-generator production

void InitGame_handler(const InitGameEvent &event);

ecs::EventDescription<InitGameEvent> InitGame_descr("InitGame", {
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<SpritesPool>("sp"), false},
  {ecs::get_type_description<Camera>("camera"), false}
}, InitGame_handler, (uint)(ecs::SystemTag::Game));

void InitGame_handler(const InitGameEvent &event)
{
  for (ecs::QueryIterator begin = InitGame_descr.begin(), end = InitGame_descr.end(); begin != end; ++begin)
  {
    InitGame(
      event,
      *begin.get_component<GameData>(0),
      *begin.get_component<WorldRenderer>(1),
      *begin.get_component<SpritesPool>(2),
      *begin.get_component<Camera>(3)
    );
  }
}


void InitGame_singl_handler(const InitGameEvent &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<InitGameEvent> InitGame_singl_descr("InitGame", {
  {ecs::get_type_description<GameData>("gameData"), false},
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<SpritesPool>("sp"), false},
  {ecs::get_type_description<Camera>("camera"), false}
}, InitGame_singl_handler, (uint)(ecs::SystemTag::Game));

void InitGame_singl_handler(const InitGameEvent &event, ecs::QueryIterator &begin)
{
  InitGame(
    event,
      *begin.get_component<GameData>(0),
      *begin.get_component<WorldRenderer>(1),
      *begin.get_component<SpritesPool>(2),
      *begin.get_component<Camera>(3)
  );
}



