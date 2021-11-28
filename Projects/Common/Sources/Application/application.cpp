#include "application_data.h"
#include "application.h"
#include "glad/glad.h"
#include "Engine/imgui/imgui_impl_opengl3.h"
#include "Engine/imgui/imgui_impl_sdl.h"
#include "Engine/Profiler/profiler.h"
#include <SDL2/SDL.h>
#include "ecs/system_tag.h"
#include "ecs/ecs_scene.h"

void compile_shaders();

Application::Application(const string &window_name, const string &project_path):
context(window_name), timer(), sceneManager(),
projectPath(project_path),
projectResourcesPath(project_path + "/Resources"),
projectShaderPath(project_path + "/Shaders")
{
  application = this;
  compile_shaders();
}
void Application::start()
{
  sceneManager.init();
  get_profiler();
}
bool Application::sdl_event_handler()
{
  SDL_Event event;
  bool running = true;
  Input &input = Input::input();
  while (SDL_PollEvent(&event))
  {
    ImGui_ImplSDL2_ProcessEvent(&event);
    switch(event.type){
      case SDL_QUIT: running = false; break;
      
      case SDL_KEYDOWN: 
      
      
      case SDL_KEYUP: input.event_process(event.key, Time::time());

      if(event.key.keysym.sym == SDLK_ESCAPE)
        running = false;
        

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP: input.event_process(event.button, Time::time()); break;

      case SDL_MOUSEMOTION: input.event_process(event.motion, Time::time()); break;

      case SDL_MOUSEWHEEL: input.event_process(event.wheel, Time::time()); break;
      
      case SDL_WINDOWEVENT: break;
    }
  }
  return running;
}
void Application::main_loop()
{
  bool running = true;
  while(running){
    get_profiler().start_frame();
    PROFILER(main_loop);
    timer.update();
    PROFILER(sdl_events) 
		running = sdl_event_handler();
    sdl_events.stop();
    if (running)
    {
      PROFILER(ecs_events);
      sceneManager.process_events();
      ecs_events.stop();
      PROFILER(ecs_logic);
      sceneManager.update_logic();
      ecs_logic.stop();
      
      PROFILER(swapchain);
      context.swap_buffer();
      swapchain.stop();
      PROFILER(ecs_render);
      sceneManager.update_render();
      ecs_render.stop();
      
      PROFILER(ui)
      context.start_imgui();
      PROFILER(ecs_ui);
      sceneManager.update_ui();
      ecs_ui.stop();
      PROFILER(imgui_render);
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      imgui_render.stop();
      ui.stop();
    }
    main_loop.stop();
    get_profiler().end_frame();
	}
}
void Application::exit()
{
  sceneManager.destroy_scene();

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();
}
string project_resources_path(const string &path)
{
  return Application::instance().projectResourcesPath.string() + "/" + path;
}
string project_resources_path()
{
  return Application::instance().projectResourcesPath.string();
}

