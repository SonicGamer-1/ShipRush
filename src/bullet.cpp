#include "bullet.h"

void Bullet::update(float dt, const Player &e)
{
    position += velocity * dt;
    collider = {position.x - 3.0f, position.y - 10.0f, 6.0f, 20.0f};
    if (CheckCollisionRecs(e.collider, collider))
        position = Vector2{-WIN_W, -WIN_H};
};

void Bullet::render()
{
    DrawRectanglePro(
        Rectangle{position.x, position.y, 6.0f, 20.0f},
        Vector2{3.0f, 10.0f},
        angle,
        BLACK);
}