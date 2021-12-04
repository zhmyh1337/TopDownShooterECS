#include <ecs/ecs.h>
#include <Engine/Profiler/profiler.h>
#include <stack>
#include <3dmath.h>
#include "Engine/imgui/imgui.h"

void profiler()
{
  auto& history = get_profiler().get_frame_history();
  if (history.size() == 0)
  {
    ImGui::End();
    return;
  }
  float maxdt = get_profiler().get_averange(history.back().label);

  stack<float> openTimes;
  openTimes.push(0.f);

  float lastCloseTime = 0.f;
  for (const TimeLabel &label : history)
  {
    float dt = get_profiler().get_averange(label.label);
    int level = openTimes.size();
    if (label.open)
    {
      openTimes.push(lastCloseTime);
      float hardness = sqrt(dt / maxdt);
      vec3 color = glm::lerp(vec3(1), vec3(1,0,0), hardness);
      ImGui::TextColored(ImVec4(color.x, color.y, color.z, 1.f), "%*c%s: %.2f ms",level*3, ' ', label.label.c_str(), dt);
    }
    else
    {
      float dt = get_profiler().get_averange(label.label);
      float openTime = openTimes.top();
      float closeTime = openTime + dt;
      lastCloseTime = closeTime;
      openTimes.pop();
    }
  }
}

SYSTEM(ecs::SystemOrder::UIMENU) menu_profiler()
{
#if not(NDEBUG)
  if (ImGui::BeginMenu("Profiler"))
  {
    profiler();
    ImGui::EndMenu();
  }
#endif
}
