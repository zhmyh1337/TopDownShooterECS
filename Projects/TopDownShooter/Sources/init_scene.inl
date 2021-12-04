#include <ecs/ecs.h>
#include <Application/application.h>
#include <Engine/Render/sprite.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include "textures_pool.h"
#include "sprites_pool.h"
#include "sprite_sheets_pool.h"
#include "audio_pool.h"
#include "init_game_event.h"

static void InitTexturesPool(TexturesPool &tp)
{
    tp.background = new Texture2D(
        project_textures_path("background.jpg"),
        TextureColorFormat::RGB,
        TextureFormat::UnsignedByte,
        TexturePixelFormat::Linear,
        TextureWrappFormat::Repeat,
        true);
    tp.soldierFeetIdle = new Texture2D(project_textures_path("soldier_feet_idle.png"), TextureColorFormat::RGBA);
    tp.soldierFeetWalk = new Texture2D(project_textures_path("soldier_feet_walk.png"), TextureColorFormat::RGBA);
    tp.soldierFeetRun = new Texture2D(project_textures_path("soldier_feet_run.png"), TextureColorFormat::RGBA);
    tp.soldierRifleIdle = new Texture2D(project_textures_path("soldier_rifle_idle.png"), TextureColorFormat::RGBA);
    tp.soldierRifleMove = new Texture2D(project_textures_path("soldier_rifle_move.png"), TextureColorFormat::RGBA);
    tp.soldierRifleReload = new Texture2D(project_textures_path("soldier_rifle_reload.png"), TextureColorFormat::RGBA);
    tp.soldierRifleMeleeAttack = new Texture2D(project_textures_path("soldier_rifle_meleeattack.png"), TextureColorFormat::RGBA);
    tp.soldierRifleShoot = new Texture2D(project_textures_path("soldier_rifle_shoot.png"), TextureColorFormat::RGBA);
    tp.zombieIdle = new Texture2D(project_textures_path("zombie_idle.png"), TextureColorFormat::RGBA);
    tp.zombieMove = new Texture2D(project_textures_path("zombie_move.png"), TextureColorFormat::RGBA);
    tp.zombieAttack = new Texture2D(project_textures_path("zombie_attack.png"), TextureColorFormat::RGBA);
    tp.bullet = new Texture2D(project_textures_path("bullet.png"), TextureColorFormat::RGBA);
    tp.blood = new Texture2D(project_textures_path("blood.png"), TextureColorFormat::RGBA);
    tp.circle = new Texture2D(project_textures_path("circle.png"), TextureColorFormat::RGBA);
}

static void InitSpritesPool(const TexturesPool &tp, SpritesPool& sp)
{
    sp.background = Sprite(tp.background, get_shader("standard_shader"));
    sp.soldierFeetIdle = Sprite(tp.soldierFeetIdle, get_shader("standard_shader"));
    sp.bullet = Sprite(tp.bullet, get_shader("standard_shader"));
    sp.circle = Sprite(tp.circle, get_shader("standard_shader"));
}

static void InitSpriteSheetsPool(const TexturesPool &tp, SpriteSheetsPool& ssp)
{
    ssp.soldierFeetWalk = SpriteSheet(tp.soldierFeetWalk, get_shader("standard_shader"), 20);
    ssp.soldierFeetRun = SpriteSheet(tp.soldierFeetRun, get_shader("standard_shader"), 20);
    ssp.soldierRifleIdle = SpriteSheet(tp.soldierRifleIdle, get_shader("standard_shader"), 20);
    ssp.soldierRifleMove = SpriteSheet(tp.soldierRifleMove, get_shader("standard_shader"), 20);
    ssp.soldierRifleReload = SpriteSheet(tp.soldierRifleReload, get_shader("standard_shader"), 20);
    ssp.soldierRifleMeleeAttack = SpriteSheet(tp.soldierRifleMeleeAttack, get_shader("standard_shader"), 15);
    ssp.soldierRifleShoot = SpriteSheet(tp.soldierRifleShoot, get_shader("standard_shader"), 3);
    ssp.zombieIdle = SpriteSheet(tp.zombieIdle, get_shader("standard_shader"), 17);
    ssp.zombieMove = SpriteSheet(tp.zombieMove, get_shader("standard_shader"), 17);
    ssp.zombieAttack = SpriteSheet(tp.zombieAttack, get_shader("standard_shader"), 9);
    ssp.blood = SpriteSheet(tp.blood, get_shader("standard_shader"), 4);
}

static void InitAudioPool(AudioPool& ap)
{
    ap.rifleShot = Mix_LoadWAV(project_audio_path("bad.wav").c_str());
}

EVENT() InitScene(
    const ecs::OnSceneCreated& event,
    TexturesPool& tp,
    SpritesPool& sp,
    SpriteSheetsPool &ssp,
    AudioPool& ap)
{
    InitTexturesPool(tp);
    InitSpritesPool(tp, sp);
    InitSpriteSheetsPool(tp, ssp);
    InitAudioPool(ap);

    debug_log("scene %s created", event.scene_name.c_str());

    ecs::send_event_immediate<InitGameEvent>({});
}
