#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "bullet.h"

#include "consts.h"

class Bullet;

class Timer
{
    float &timer;
    float limit = 0;

public:
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

    float angle = 180;

    float bulletTimer = 0, boostTimer = 0;

    Rectangle collider = {position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};

    Timer boostT = Timer(boostTimer, 0.5);
    Timer bulletT = Timer(bulletTimer, 0.2);

    Texture2D texture;

    std::vector<Bullet> *bullets;
    bool shot;
    Vector2 mousePos;

    void load(std::vector<Bullet> *b);
    void update(float dt, bool peer);
    void render();
    void unload();
    void shoot(bool peer);
};