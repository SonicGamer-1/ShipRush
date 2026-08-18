#pragma once

#include <raylib.h>
#include <raymath.h>

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

    Timer boostT = Timer(boostTimer, 0.5);
    Timer bulletT = Timer(bulletTimer, 1);

    Texture2D texture;

    void load();
    void update(float dt, bool peer);
    void render();
    void unload();
};