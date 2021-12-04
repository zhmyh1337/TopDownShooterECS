#pragma once
#include "Engine/input.h"
#include "Engine/time.h"
#include "common.h"
#include "context.h"
#include "ecs/ecs_scene.h"
#include <filesystem>

class Application {
private:
  inline static Application *application;
  Context context;
  Time timer;

public:
  ecs::SceneManager sceneManager;
  const filesystem::path texturesPath;
  const filesystem::path audioPath;
  const filesystem::path shadersPath;
  Application(const string &window_name);
  bool sdl_event_handler();
  void start();
  void main_loop();
  void exit();
  static Application &instance() { return *application; }
  static Context &get_context() { return application->context; }
};