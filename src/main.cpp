#include <raylib.h>
#include <iostream>
#include "player.h"
#include "network.h"

int main(int argc, char *argv[])
{
    char mode = 'h'; // Default to Host Peer ('h' or 's')
    if (argc > 1 && (argv[1][0] == 'c' || argv[1][0] == 'C'))
    {
        mode = 'c'; // Client Peer
    }

    InitWindow(1600, 900, mode == 'h' ? "P2P Game - Peer A" : "P2P Game - Peer B");
    SetTargetFPS(120);

    NetworkManager netManager;
    if (!netManager.initialize(mode))
    {
        std::cerr << "Failed to initialize P2P Network!" << std::endl;
        CloseWindow();
        return -1;
    }

    Player localPlayer;
    Player remotePeerPlayer;

    localPlayer.load();
    remotePeerPlayer.load();

    // Set initial spawn points to distinguish entities
    if (mode == 'h')
    {
        localPlayer.position = {800.0f, 100.0f};
        remotePeerPlayer.position = {800.0f, 800.0f};
    }
    else
    {
        localPlayer.position = {800.0f, 800.0f};
        remotePeerPlayer.position = {800.0f, 100.0f};
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

        // 4. Render
        BeginDrawing();
        ClearBackground(RAYWHITE);

        localPlayer.render();
        remotePeerPlayer.render();

        DrawText(mode == 'h' ? "PEER A (Local)" : "PEER B (Local)", 20, 20, 20, MAROON);
        DrawFPS(20, 50);

        EndDrawing();
    }

    localPlayer.unload();
    remotePeerPlayer.unload();
    CloseWindow();

    return 0;
}