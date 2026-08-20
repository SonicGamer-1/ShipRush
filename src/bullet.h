#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>

#include "player.h"
#include "consts.h"

class Player;

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

    Rectangle collider = {position.x - 3.0f, position.y - 10.0f, 6.0f, 20.0f};

    Bullet(Vector2 pos, Vector2 vel, Shooter shooterType, float ang)
        : position(pos), velocity(vel), shooter(shooterType), angle(ang) {}

    void update(float dt, const Player &e, int &score);

    void render();
};