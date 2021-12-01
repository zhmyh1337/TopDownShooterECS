#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/imgui/imgui.h>

void debug_show();
SYSTEM(ecs::SystemOrder::UI) fps_ui()
{
  ImGui::Begin("fps", nullptr, ImGuiWindowFlags_NoTitleBar);
  ImGui::Text("%.1f fps", Time::fps());
  ImGui::End();
}

SYSTEM(ecs::SystemOrder::UI) debug_console_ui()
{
#if not(NDEBUG)
  ImGui::Begin("debug");
  debug_show();
  ImGui::End();
#endif
}