#include "player.h"
#include <cmath>
#include <iostream>

const int PLAYER_SIZE = 64;

void Player::load()
{
    texture = LoadTexture("asset/image/player.png");
    position = {800, 800};
}

void Player::update(float dt, bool peer)
{
    if (!peer)
    {
        acceleration = {0};

        boostT.update(dt);
        bulletT.update(dt);

        if (IsKeyDown(KEY_A))
            acceleration.x -= 1000.0f;

        if (IsKeyDown(KEY_D))
            acceleration.x += 1000.0f;

        if (IsMouseButtonDown(0) && bulletTimer <= 0)
        {
            // bullet shoot
            bulletT.reset();
        }

        if (IsMouseButtonDown(1) && boostTimer <= 0)
        {
            acceleration *= 100;
            boostT.reset();
        }
    }

    velocity = Vector2Scale(velocity, exp(-5 * dt));

    velocity += acceleration * dt;
    position += velocity * dt;

    // Left boundary
    if (position.x < PLAYER_SIZE / 2)
        position.x = PLAYER_SIZE / 2, velocity *= -2;

    // Right boundary
    if (position.x > 1600 - PLAYER_SIZE / 2)
        position.x = 1600 - PLAYER_SIZE / 2, velocity *= -2;

    if (!peer)
        angle = 90.0f + (180.0f / PI) * atan2f(GetMousePosition().y - position.y, GetMousePosition().x - position.x);
}

void Player::render()
{
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, PLAYER_SIZE, PLAYER_SIZE}, {PLAYER_SIZE / 2, PLAYER_SIZE / 2}, angle, WHITE);
}

void Player::unload()
{
    UnloadTexture(texture);
}