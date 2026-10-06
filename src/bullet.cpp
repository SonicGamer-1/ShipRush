#include "bullet.h"

void Bullet::update(float dt, Player &e, int &score, Sound *shot)
{
    position += velocity * dt;
    collider = {position.x - BULLET_COLLIDER_OFFSET_X, position.y - BULLET_COLLIDER_OFFSET_Y, BULLET_WIDTH, BULLET_HEIGHT};
    if (CheckCollisionRecs(e.collider, collider))
    {
        position = Vector2{-WIN_W, -WIN_H};
        score++;
        PlaySound(*shot);
        e.isShot = true;
    }
};

void Bullet::render()
{
    DrawRectanglePro(
        Rectangle{position.x, position.y, BULLET_WIDTH, BULLET_HEIGHT},
        Vector2{BULLET_COLLIDER_OFFSET_X, BULLET_COLLIDER_OFFSET_Y},
        angle,
        BLACK);
}