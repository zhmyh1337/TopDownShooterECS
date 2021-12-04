#pragma once
#include <filesystem>
#include "common.h"
#include "context.h"
#include "Engine/input.h"
#include "Engine/time.h"
#include "ecs/ecs_scene.h"

class Application
{
private:
  inline static Application *application;
  Context context;
  Time timer;
public:
  ecs::SceneManager sceneManager;
  filesystem::path resourcesPath;
  filesystem::path shadersPath;
  Application(const string &window_name);
  bool sdl_event_handler();
  void start();
  void main_loop();
  void exit();
  static Application& instance()
  {
    return *application;
  }
  static Context& get_context()
  {
    return application->context;
  }
};