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

    Rectangle collider = {position.x - BULLET_COLLIDER_OFFSET_X, position.y - BULLET_COLLIDER_OFFSET_Y, BULLET_WIDTH, BULLET_HEIGHT};

    Bullet(Vector2 pos, Vector2 vel, Shooter shooterType, float ang)
        : position(pos), velocity(vel), shooter(shooterType), angle(ang) {}

    void update(float dt, Player &e, int &score, Sound *shot);

    void render();
};