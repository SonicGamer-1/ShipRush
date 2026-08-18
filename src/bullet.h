#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>

enum Shooter
{
    PLAYER,
    ENEMY
};

class Bullet
{
public:
    Vector2 position = {0};
    Vector2 velocity = {0};
    Shooter shooter;

    void update(float dt)
    {
        position += velocity * dt;
    };

    void render();
};