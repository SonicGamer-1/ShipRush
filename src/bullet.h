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
    float angle = 0;

    Bullet(Vector2 pos, Vector2 vel, Shooter shooterType, float ang)
        : position(pos), velocity(vel), shooter(shooterType), angle(ang) {}

    void update(float dt)
    {
        position += velocity * dt;
    };

    void render()
    {
        DrawRectanglePro(
            Rectangle{position.x, position.y, 6.0f, 20.0f},
            Vector2{3.0f, 10.0f},
            angle,
            BLACK);
    }
};