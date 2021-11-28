#include <ecs/ecs.h>
#include <Engine/imgui/imgui.h>
#include <ecs/manager/entity_container.h>

SYSTEM(ecs::SystemOrder::UI) entity_viewer()
{
#if not(NDEBUG)
  if(!ImGui::Begin("Entity viewer"))
  {
    ImGui::End();
    return;
  }
  ImGui::PushItemWidth(170);
  for (ecs::Archetype *archetype : ecs::core().entityContainer->archetypes)
  {
    if (ImGui::TreeNode(archetype->synonim.c_str()))
    {
      for (int j = 0; j < archetype->count; ++j)
      {
        const int N = 255;
        char buf[N];
        snprintf(buf, N, "entity[%d]", j);
        if (ImGui::TreeNode(buf))
        {
          ImGui::SameLine();
          for (const ecs::FullTypeDescription *full_descr : archetype->fullTypeDescriptions)
          {
            const ecs::TypeInfo &typeInfo = ecs::TypeInfo::types()[full_descr->typeHash];
            ImGui::Text("%s %s", typeInfo.name.c_str(), full_descr->name.c_str());
          }
          ImGui::TreePop();
        }
      }
      ImGui::TreePop();
    }
  }
  ImGui::End();
#endif
}
