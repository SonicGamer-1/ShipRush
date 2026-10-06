# ShipRush v1.0.0

Initial public release of **ShipRush** — a peer-to-peer 2D arena shooter built with raylib and ENet.

## Overview

ShipRush is a two-player, real-time arena shooter. One peer acts as the **host** and the other as the **client**, both connecting directly over UDP. Each player pilots a ship inside the 1600×900 arena, dodges incoming fire, and tries to land shots on their opponent to win points. The game simulates movement and combat locally on each peer while syncing state over ENet for low-latency multiplayer.

## Release Highlights

- Real-time peer-to-peer multiplayer using ENet
- Top-down ship combat with WASD movement and mouse aiming
- Bullet physics, hit detection, and score tracking
- Hit feedback with jitter and flash effects
- Speed boost ability via right mouse click
- Host/client mode support for local multiplayer matches
- Centralized game constants in `src/consts.h` for easier tuning and maintenance

## Included in v1.0.0

- Initial game implementation with player and network systems
- Bullet firing and enemy collision logic
- Mouse-based aiming and firing angle calculation
- Scoreboard rendering with custom font assets
- Audio feedback for firing and successful hits
- Network packet sync for position, velocity, angle, mouse position, and shot state
- `Run.bat` launcher for host/client selection
- Project documentation and build instructions

## Known Notes

- Both peers must be reachable over UDP port **12345**; make sure firewall rules allow it.
- This release does not include NAT traversal, so both peers should be on the same local network for reliable play.

## Getting Started

Requirements: Windows, MinGW-w64 (g++), raylib, and ENet.

```bash
make          # build ShipRush.exe
make run      # build and run in host mode by default
```

Run the game as host (`ShipRush.exe`) or client (`ShipRush.exe c`), or use `Run.bat` to select a mode. See the project README for full setup and play instructions.

## Version

- Version: `v1.0.0`
- Release date: `2026-10-07`
