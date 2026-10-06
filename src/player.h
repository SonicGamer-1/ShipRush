#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "bullet.h"

#include "consts.h"

class Bullet;

struct Timer
{
    float &timer;
    float limit = 0;

    Timer(float &T, float L)
        : timer(T), limit(L) {}

    void update(float dt)
    {
        if (timer > 0)
            timer -= dt;
    }

    void reset()
    {
        timer = limit;
    }
};

class Player
{
public:
    Vector2 position = {0};
    Vector2 velocity = {0};
    Vector2 acceleration = {0};

    float angle = HALF_ROTATION;

    float bulletTimer = 0, boostTimer = 0, isShotTimer = 0;

    Rectangle collider;

    Timer boostT = Timer(boostTimer, PLAYER_BOOST_DURATION);
    Timer bulletT = Timer(bulletTimer, PLAYER_SHOT_COOLDOWN);
    Sound bulletSound;

    Texture2D texture;

    std::vector<Bullet> *bullets;
    bool shot = false;
    bool isShot = false;
    Timer isShotT = Timer(isShotTimer, PLAYER_SHOT_FLASH_TIME);
    Vector2 mousePos;

    void load(std::vector<Bullet> *b);
    void update(float dt, bool peer);
    void render();
    void unload();
    void shoot(bool peer);
};