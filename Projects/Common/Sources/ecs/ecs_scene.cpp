#include "ecs_scene.h"
#include "ecs/ecs.h"
#include "manager/entity_container.h"
#include "glad/glad.h"
#include "Engine/Profiler/profiler.h"
#include "Engine/imgui/imgui.h"

namespace ecs
{
  bool system_comparator(const SystemDescription *a, const SystemDescription *b)
  {
    return a->order < b->order;
  }
  void SceneManager::init()
  {
    currentScene = 0;

    scenes.emplace_back(Scene{"mainScene", SystemTag::Game, {}});
    ecs::core().currentSceneTags = SystemTag::Game;
    ecs::send_event(OnSceneCreated{"mainScene", SystemTag::Game});

    auto &systems = core().systems;
    std::sort(systems.begin(), systems.end(), system_comparator);
    logic.begin = systems.begin();
    logic.end = std::find_if(systems.begin(), systems.end(),
                             [](const SystemDescription *a)
                             { return a->order >= (int)SystemOrder::RENDER; });
    render.begin = logic.end;
    render.end = std::find_if(systems.begin(), systems.end(),
                              [](const SystemDescription *a)
                              { return a->order >= (int)SystemOrder::UI; });
    ui.begin = render.end;
    ui.end = std::find_if(systems.begin(), systems.end(),
                          [](const SystemDescription *a)
                          { return a->order >= (int)SystemOrder::UIMENU; });
    menu.begin = ui.end;
    menu.end = systems.end();
  }

  void SceneManager::update_range(const SystemRange &range)
  {
    for (SystemIterator it = range.begin; it != range.end; it++)
      if ((*it)->tags & scenes[currentScene].flags)
      {
        // debug_log("execute %s system", (*it)->name.c_str());
        ProfilerLabel label((*it)->name.c_str());
        (*it)->execute();
      }
  }
  void SceneManager::update_logic()
  {
    update_range(logic);
  }
  void SceneManager::update_render()
  {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    update_range(render);
    glFlush();
  }
  void SceneManager::update_ui()
  {
    update_range(ui);
#if not(NDEBUG)
    if (ImGui::BeginMainMenuBar())
    {
      update_range(menu);
      ImGui::EndMainMenuBar();
    }
#endif
  }
  void SceneManager::destroy_entities(bool with_swap)
  {
    auto &toDestroy = core().toDestroy;
    for (int i = 0, n = toDestroy.size(); i < n; i++)
    {
      EntityId &eid = toDestroy.front();
      if (!eid)
      {
        toDestroy.pop();
        continue;
      }
      debug_log("destroy %d %d entity", eid.archetype_index(), eid.array_index());
      core().entityContainer->archetypes[eid.archetype_index()]->destroy_entity(eid.array_index(), with_swap);
      core().entityContainer->entityPull.destroy_entity(eid);
      toDestroy.pop();
    }
  }
  void SceneManager::process_only_events()
  {
    auto &events = core().events;
    for (int i = 0, n = events.size(); i < n; i++)
    {
      events.front()();
      events.pop();
    }
  }
  void SceneManager::process_events()
  {
    process_only_events();
    destroy_entities(true);
  }

  void SceneManager::destroy_scene()
  {
    core().destroy_entities();
    process_only_events();
    destroy_entities(false);
  }
}