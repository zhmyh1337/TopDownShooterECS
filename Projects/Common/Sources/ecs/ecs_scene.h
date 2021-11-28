#pragma once
#include <vector>
#include <filesystem>
#include "manager/system_description.h"
#include "Engine/input.h"
#include "manager/entity_container.h"

namespace ecs
{
  struct Scene
  {
    string name;
    uint32_t flags;
    EntityContainer container;
  };
  class SceneManager
  {
  private:
    typedef std::vector<SystemDescription*>::iterator SystemIterator;
    struct SystemRange { SystemIterator begin, end; };
    SystemRange logic, render, ui, menu;
    vector<Scene> scenes;
    int currentScene;
    void update_range(const SystemRange &range);
    void process_only_events();
  public:
    void init();
    void update_logic();
    void update_render();
    void update_ui();
    void process_events();
    void destroy_scene();
    void destroy_entities(bool without_copy);
  };
}