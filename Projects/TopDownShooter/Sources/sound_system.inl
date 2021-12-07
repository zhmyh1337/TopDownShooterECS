#pragma once

#include "audio_pool.h"
#include "camera.h"
#include <ecs/ecs.h>

SYSTEM(ecs::SystemOrder::LOGIC + 10) PlayAllSoundsFromQueue(AudioPool& ap, const Camera& camera)
{
    ap.rifleShot.PlayAll(camera.transform.position);
    ap.localPlayerTakesDamage.PlayAll(camera.transform.position);
    ap.bulletDamage.PlayAll(camera.transform.position);
    ap.gameOver.PlayAll(camera.transform.position);
}
