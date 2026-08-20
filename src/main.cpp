#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "player.h"
#include "network.h"
#include "consts.h"

int main(int argc, char *argv[])
{
    char mode = 'h'; // Default to Host Peer ('h' or 's')
    if (argc > 1 && (argv[1][0] == 'c' || argv[1][0] == 'C'))
    {
        mode = 'c'; // Client Peer
    }

    InitWindow(WIN_W, WIN_H, mode == 'h' ? "P2P Game - Peer A" : "P2P Game - Peer B");
    SetTargetFPS(120);

    NetworkManager netManager;

    if (mode == 'c')
    {
        std::cout << "Enter Host IP:\n";
        std::cin >> netManager.ip;
    }

    if (!netManager.initialize(mode))
    {
        std::cerr << "Failed to initialize P2P Network!" << std::endl;
        CloseWindow();
        return -1;
    }

    Player localPlayer;
    std::vector<Bullet> bullets;
    int score = 0;
    Player remotePeerPlayer;
    std::vector<Bullet> enemBullets;
    int enemScore = 0;

    Font scoreF = LoadFontEx("asset/font/scoreFont.ttf", 64, 0, 0);
    Vector2 textSize;
    Vector2 enemTextSize;

    localPlayer.load(&bullets);
    remotePeerPlayer.load(&enemBullets);

    // Set initial spawn points to distinguish entities
    if (mode == 'h')
    {
        localPlayer.position = {WIN_W / 2.0f, WIN_H / 10.0f};
        remotePeerPlayer.position = {WIN_W / 2.0f, WIN_H * 9.0f / 10.0f};
    }
    else
    {
        localPlayer.position = {WIN_W / 2.0f, WIN_H * 9.0f / 10.0f};
        remotePeerPlayer.position = {WIN_W / 2.0f, WIN_H / 10.0f};
    }

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // 1. Both peers update their OWN player locally with zero lag
        localPlayer.update(dt, false);

        // 2. Receive position & angle updates from the other peer
        netManager.serviceNetwork(remotePeerPlayer);

        // 3. Transmit local position & angle to the other peer
        netManager.sendLocalState(localPlayer);

        remotePeerPlayer.update(dt, true);

        for (auto &bullet : bullets)
            bullet.update(dt, remotePeerPlayer, score);
        for (auto &bullet : enemBullets)
            bullet.update(dt, localPlayer, enemScore);

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &bullet)
                           { return bullet.position.x < 0 || bullet.position.x > WIN_W ||
                                    bullet.position.y < 0 || bullet.position.y > WIN_H; }),
            bullets.end());

        // 4. Render
        BeginDrawing();
        ClearBackground(GRAY);

        localPlayer.render();
        remotePeerPlayer.render();
        for (auto &bullet : bullets)
            bullet.render();
        for (auto &bullet : enemBullets)
            bullet.render();

        textSize = MeasureTextEx(scoreF, std::to_string(score).c_str(), 18, 1);
        DrawTextPro(scoreF, std::to_string(score).c_str(), {WIN_W / 2, WIN_H / 32 - textSize.y}, textSize / 2.0f, 0.0f, 64, 1, BLUE);
        enemTextSize = MeasureTextEx(scoreF, std::to_string(score).c_str(), 18, 1);
        DrawTextPro(scoreF, std::to_string(enemScore).c_str(), {WIN_W / 2, WIN_H * 31 / 32 - enemTextSize.y}, enemTextSize / 2.0f, 0.0f, 64, 1, RED);

        EndDrawing();
    }

    localPlayer.unload();
    remotePeerPlayer.unload();
    CloseWindow();

    return 0;
}