#include "player.h"
#include <cmath>
#include <iostream>

void Player::load(std::vector<Bullet> *b)
{
    bullets = b;
    texture = LoadTexture("asset/image/player.png");
}

void Player::update(float dt, bool peer)
{
    if (!peer)
    {
        acceleration = {0};

        boostT.update(dt);
        bulletT.update(dt);

        if (IsKeyDown(KEY_A))
            acceleration.x -= ACCEL;

        if (IsKeyDown(KEY_D))
            acceleration.x += ACCEL;

        if (IsMouseButtonDown(0) && bulletTimer <= 0)
            shoot(peer);

        if (IsMouseButtonDown(1) && boostTimer <= 0)
        {
            acceleration *= ACCEL_BOOST;
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
    if (position.x > WIN_W - PLAYER_SIZE / 2)
        position.x = WIN_W - PLAYER_SIZE / 2, velocity *= -2;

    collider = {position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};

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

void Player::shoot(bool peer)
{
    bulletT.reset();
    bullets->emplace_back(position, Vector2Normalize(GetMousePosition() - position) * BULLET_SPEED, peer ? ENEMY : PLAYER, 90.0f + (180.0f / PI) * atan2f(GetMousePosition().y - position.y, GetMousePosition().x - position.x));
}