#include "ui.inl"
//Code-generator production

void ShowKillStat_func();

ecs::SystemDescription ShowKillStat_descr("ShowKillStat", {
  {ecs::get_type_description<GameData>("gameData"), false}
}, ShowKillStat_func, ecs::SystemOrder::UI, (uint)(ecs::SystemTag::Game));

void ShowKillStat_func()
{
  for (ecs::QueryIterator begin = ShowKillStat_descr.begin(), end = ShowKillStat_descr.end(); begin != end; ++begin)
  {
    ShowKillStat(
      *begin.get_component<GameData>(0)
    );
  }
}


void ShowNewGamePrompt_func();

ecs::SystemDescription ShowNewGamePrompt_descr("ShowNewGamePrompt", {
  {ecs::get_type_description<GameData>("gameData"), false}
}, ShowNewGamePrompt_func, ecs::SystemOrder::UI, (uint)(ecs::SystemTag::Game));

void ShowNewGamePrompt_func()
{
  for (ecs::QueryIterator begin = ShowNewGamePrompt_descr.begin(), end = ShowNewGamePrompt_descr.end(); begin != end; ++begin)
  {
    ShowNewGamePrompt(
      *begin.get_component<GameData>(0)
    );
  }
}



