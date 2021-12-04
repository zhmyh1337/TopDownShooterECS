#include "context.h"
#include "Engine/imgui/imgui_impl_opengl3.h"
#include "Engine/imgui/imgui_impl_sdl.h"
#include "common.h"
#include "glad/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


// During init, enable debug output
Context::Context(const std::string &window_name) {
  SDL_Init(SDL_INIT_EVERYTHING);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  const char *glsl_version = "#version 450";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_DisplayMode dm;

  if (SDL_GetDesktopDisplayMode(0, &dm)) {
    throw std::runtime_error{"Error getting desktop display mode\n"};
  }
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_OPENGL /*  | SDL_WINDOW_RESIZABLE */ |
                        SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, dm.w, dm.h, window_flags);
  gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(0);

  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    throw std::runtime_error{"Glad error"};
  }
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);
}
void Context::start_imgui() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
  ImGui::NewFrame();
}
void Context::swap_buffer() { SDL_GL_SwapWindow(window); }
Resolution Context::get_screen_resolution() const {
  int w, h;
  SDL_GL_GetDrawableSize(window, &w, &h);
  return {w, h};
}