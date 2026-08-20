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
    mousePos = GetMousePosition();

    if (shot)
    {
        shoot(peer);
        shot = false;
    }

    if (!peer)
    {
        acceleration = {0};

        boostT.update(dt);
        bulletT.update(dt);

        acceleration.x += ACCEL * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
        acceleration.y -= ACCEL * (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));

        if ((IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) && (IsKeyDown(KEY_W) - IsKeyDown(KEY_S)))
            acceleration /= 1.4142;

        if (IsMouseButtonDown(0) && bulletTimer <= 0)
        {
            shot = true;
        }

        if (IsMouseButtonDown(1) && boostTimer <= 0)
        {
            acceleration *= ACCEL_BOOST;
            boostT.reset();
        }
    }

    velocity = Vector2Scale(velocity, exp(-5 * dt));

    velocity += acceleration * dt;
    position += velocity * dt;

        if (position.x < PLAYER_SIZE / 2)
        position.x = PLAYER_SIZE / 2, velocity *= -2;
    if (position.x > WIN_W - PLAYER_SIZE / 2)
        position.x = WIN_W - PLAYER_SIZE / 2, velocity *= -2;
    if (position.y < PLAYER_SIZE / 2)
        position.y = PLAYER_SIZE / 2, velocity *= -2;
    if (position.y > WIN_H - PLAYER_SIZE / 2)
        position.y = WIN_H - PLAYER_SIZE / 2, velocity *= -2;

    collider = {position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};

    if (!peer)
        angle = 90.0f + (180.0f / PI) * atan2f(GetMousePosition().y - position.y, GetMousePosition().x - position.x);
}

void Player::render()
{
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, PLAYER_SIZE, PLAYER_SIZE}, {PLAYER_SIZE / 2, PLAYER_SIZE / 2}, angle, WHITE);
    DrawRectangle(mousePos.x, mousePos.y, 1, 1, RED);
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