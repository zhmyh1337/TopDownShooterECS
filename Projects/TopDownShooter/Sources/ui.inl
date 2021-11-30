#include <ecs/ecs.h>
#include <Engine/imgui/imgui.h>
#include "game_data.h"

SYSTEM(ecs::SystemOrder::UI) ShowKillStat(const GameData& gameData)
{
    if (ImGui::Begin("Score"))
    {
        ImGui::Text("%d kills", gameData.killsCount);
        ImGui::End();
    }
}
