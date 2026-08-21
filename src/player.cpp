#include "player.h"
#include <cmath>
#include <iostream>

void Player::load(std::vector<Bullet> *b)
{
    bullets = b;
    texture = LoadTexture("asset/image/player.png");
    bulletSound = LoadSound("asset/audio/bulletShoot.ogg");
    collider = {position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};
    bulletT.reset();
    boostT.reset();
    isShotT.reset();
}

void Player::update(float dt, bool peer)
{
    if (!peer)
        mousePos = GetMousePosition();

    if (shot)
    {
        shoot(peer);
        shot = false;
    }

    if (isShot)
    {
        isShotT.update(GetFrameTime());
        if (isShotTimer > 0)
            position += {(float)GetRandomValue(-2, 2), (float)GetRandomValue(-2, 2)};
        else
        {
            isShot = 0;
            isShotT.reset();
        }
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
            shot = true;

        if (IsMouseButtonDown(1) && boostTimer <= 0)
            boostT.reset();
    }

    velocity = Vector2Scale(velocity, exp(-5 * dt));

    if (boostTimer > 0.45)
        acceleration *= ACCEL_BOOST;

    velocity += acceleration * dt;
    position += velocity * dt;

    if (position.x < PLAYER_SIZE / 2)
        position.x = PLAYER_SIZE / 2, velocity.x *= -2;
    if (position.x > WIN_W - PLAYER_SIZE / 2)
        position.x = WIN_W - PLAYER_SIZE / 2, velocity.x *= -2;
    if (position.y < PLAYER_SIZE / 2)
        position.y = PLAYER_SIZE / 2, velocity.y *= -2;
    if (position.y > WIN_H - PLAYER_SIZE / 2)
        position.y = WIN_H - PLAYER_SIZE / 2, velocity.y *= -2;

    collider = {position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};

    if (!peer)
        angle = 90.0f + (180.0f / PI) * atan2f(mousePos.y - position.y, mousePos.x - position.x);
}

void Player::render()
{
    Color flashColor = WHITE;
    if (isShotTimer > 0 && isShot && fmodf(isShotTimer, 0.02f) < 0.01f)
        flashColor = BLACK;

    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, PLAYER_SIZE, PLAYER_SIZE}, {PLAYER_SIZE / 2, PLAYER_SIZE / 2}, angle, flashColor);
    DrawRectangle(mousePos.x, mousePos.y, 10, 10, RED);
}

void Player::unload()
{
    UnloadTexture(texture);
    UnloadSound(bulletSound);
}

void Player::shoot(bool peer)
{
    bulletT.reset();
    bullets->emplace_back(position, Vector2Normalize(mousePos - position) * BULLET_SPEED, peer ? ENEMY : PLAYER, 90.0f + (180.0f / PI) * atan2f(mousePos.y - position.y, mousePos.x - position.x));
    PlaySound(bulletSound);
}