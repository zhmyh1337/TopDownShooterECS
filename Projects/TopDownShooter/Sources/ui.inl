#include <ecs/ecs.h>
#include <Engine/imgui/imgui.h>
#include "game_data.h"
#include "init_game_event.h"

SYSTEM(ecs::SystemOrder::UI) ShowKillStat(const GameData& gameData)
{
    if (gameData.isGameOver)
    {
        return;
    }

    if (ImGui::Begin("Score"))
    {
        ImGui::Text("%zu kills", gameData.killsCount);
        ImGui::End();
    }
}

SYSTEM(ecs::SystemOrder::UI) ShowNewGamePrompt(GameData& gameData)
{
    if (gameData.isGameOver)
    {
        if (ImGui::Begin("Game over"))
        {
            ImGui::Text("You kill score is: %zu", gameData.killsCount);
            if (ImGui::Button("New game"))
            {
                ecs::destroy_scene();
                ecs::send_event<InitGameEvent>({});
            }
            ImGui::End();
        }
    }
}
