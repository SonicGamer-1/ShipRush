#pragma once

constexpr int PLAYER_SIZE = 64;
constexpr int PLAYER_TEXTURE_SIZE = 16;
constexpr int WIN_H = 900;
constexpr int WIN_W = 1600;

constexpr float ACCEL = 1000.0f;
constexpr float ACCEL_BOOST = 25.0f;
constexpr float BULLET_SPEED = 2000.0f;
constexpr float DIAGONAL_NORMALIZE = 1.4142f;

constexpr float PLAYER_BOOST_DURATION = 0.5f;
constexpr float PLAYER_SHOT_COOLDOWN = 0.2f;
constexpr float PLAYER_SHOT_FLASH_TIME = 0.2f;
constexpr float PLAYER_BOOST_THRESHOLD = 0.45f;

constexpr float BULLET_WIDTH = 6.0f;
constexpr float BULLET_HEIGHT = 20.0f;
constexpr float BULLET_COLLIDER_OFFSET_X = 3.0f;
constexpr float BULLET_COLLIDER_OFFSET_Y = 10.0f;
constexpr float MOUSE_CURSOR_SIZE = 10.0f;
constexpr float PLAYER_ANGLE_OFFSET = 90.0f;
constexpr float HALF_ROTATION = 180.0f;

constexpr int NETWORK_PORT = 12345;
inline constexpr char DEFAULT_IP[] = "127.0.0.1";