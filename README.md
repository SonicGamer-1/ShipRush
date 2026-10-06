# ShipRush

A peer-to-peer 2D arena shooter built with [raylib](https://www.raylib.com/) and [ENet](http://enet.bespin.org/).

## About

ShipRush is a two-player, real-time arena shooter. Two peers connect directly over the network — one acts as the **host** and the other as the **client** — and duel in a 1600×900 arena. Each player controls a ship, dodges incoming fire, and tries to land shots on their opponent to rack up points.

The game is written in C++17, using raylib for rendering, audio, and input, and ENet for low-latency UDP networking.

## Features

- Real-time peer-to-peer multiplayer (ENet)
- Top-down ship movement (WASD) with mouse aiming
- Bullet physics, collision detection, and per-player scoring
- Hit feedback (screen jitter + flashing)
- Speed boost ability
- Host and client modes

## Requirements

- Windows (the project links against Winsock and Win32 libraries)
- [MinGW-w64](https://www.mingw-w64.org/) (g++)
- [raylib](https://www.raylib.com/)
- [ENet](http://enet.bespin.org/)

## Building

The project uses a simple `makefile`. From the repository root:

```bash
make          # build ShipRush.exe
make run      # build and run (host mode by default)
make clean    # remove build artifacts and the executable
```

The makefile links against `raylib`, `enet`, and the following system libraries:
`ws2_32`, `opengl32`, `gdi32`, `winmm`.

## Playing

Two players are required — one host and one client.

### Using Run.bat

Double-click `Run.bat` (or run it from a terminal) and choose a mode:

- `h` — **Host** mode (Peer A)
- `c` — **Client** mode (Peer B)

### Using the executable directly

```bash
ShipRush.exe      # Host mode (Peer A)
ShipRush.exe c    # Client mode (Peer B) — prompts for the host IP
```

### Networking notes

- Both peers communicate over **UDP port 12345**.
- The host listens for incoming connections; the client connects to the host's IP address.
- If the peers are on different machines, ensure port **12345** is allowed through the firewall.

## Controls

| Input                | Action            |
| -------------------- | ----------------- |
| `W` `A` `S` `D`      | Move the ship     |
| Mouse (move)         | Aim               |
| Left Mouse Button    | Shoot             |
| Right Mouse Button   | Boost             |

## Project Structure

```
ShipRush/
├── asset/
│   ├── audio/
│   │   ├── bulletShoot.ogg   # local shoot sound
│   │   └── bulletShot.ogg    # hit-confirmation sound
│   ├── font/
│   │   └── scoreFont.ttf     # score display font
│   └── image/
│       └── player.png        # ship texture
├── src/
│   ├── main.cpp              # game loop, setup, rendering
│   ├── player.h / player.cpp # player movement, shooting, rendering
│   ├── bullet.h / bullet.cpp # bullet physics and collision
│   ├── network.h             # ENet peer-to-peer networking
│   └── consts.h              # shared constants
├── temp/                     # build artifacts (ignored)
├── makefile
├── Run.bat                   # host/client launcher
└── ShipRush.exe              # build output
```

## How It Works

Each peer runs the full simulation and transmits its own state to the other. The state is packed into a `PeerStatePacket` (position, velocity, angle, mouse position, and shot flag) and sent over an unreliable-fragment ENet channel for minimal latency. On receipt, the remote peer's entity is updated directly, keeping both screens in sync.
