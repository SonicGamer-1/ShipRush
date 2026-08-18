#pragma once

#define NOGDI
#define NOUSER
#define WIN32_LEAN_AND_MEAN

#include <enet/enet.h>
#include <raylib.h>
#include <iostream>
#include <cstdint>
#include <cstring>

#include "player.h"

#pragma pack(push, 1)

std::string ip = "127.0.0.1";

enum PacketType : uint8_t
{
    PACKET_P2P_STATE = 1
};

// Peer State Packet: Each peer transmits its own transformed state
struct PeerStatePacket
{
    uint8_t type = PACKET_P2P_STATE;
    Vector2 position;
    Vector2 velocity;
    float angle;
};

#pragma pack(pop)

class NetworkManager
{
private:
    ENetHost *host = nullptr;
    ENetPeer *peer = nullptr;
    bool isHostPeer = false;

public:
    ~NetworkManager()
    {
        if (host)
            enet_host_destroy(host);
        enet_deinitialize();
    }

    bool initialize(char mode)
    {
        if (enet_initialize() != 0)
            return false;

        isHostPeer = (mode == 's' || mode == 'h');
        ENetAddress address;

        if (isHostPeer)
        {
            // Peer A: Listens on port 12345
            address.host = ENET_HOST_ANY;
            address.port = 12345;
            host = enet_host_create(&address, 32, 2, 0, 0);
        }
        else
        {
            // Peer B: Connects to Peer A on port 12345
            host = enet_host_create(nullptr, 1, 2, 0, 0);
            enet_address_set_host_ip(&address, ip.c_str());
            address.port = 12345;
            peer = enet_host_connect(host, &address, 2, 0);
        }
        return host != nullptr;
    }

    // Process network events and capture peer updates directly
    void serviceNetwork(Player &remotePeerPlayer)
    {
        ENetEvent event;
        while (enet_host_service(host, &event, 0) > 0)
        {
            if (event.type == ENET_EVENT_TYPE_CONNECT)
            {
                // Keep track of the newly connected peer for Peer A
                if (isHostPeer)
                    peer = event.peer;
            }
            else if (event.type == ENET_EVENT_TYPE_RECEIVE)
            {
                uint8_t packetType = event.packet->data[0];

                if (packetType == PACKET_P2P_STATE)
                {
                    PeerStatePacket *state = reinterpret_cast<PeerStatePacket *>(event.packet->data);

                    // Directly apply the received transform onto the remote peer entity
                    remotePeerPlayer.position = state->position;
                    remotePeerPlayer.position = state->velocity;
                    remotePeerPlayer.angle = state->angle;
                }
                enet_packet_destroy(event.packet);
            }
        }
    }

    // Broadcasts/Sends local state to the other peer
    void sendLocalState(const Player &localPlayer)
    {
        if (!host)
            return;

        PeerStatePacket state;
        state.position = localPlayer.position;
        state.angle = localPlayer.angle;
        state.velocity = localPlayer.velocity;

        ENetPacket *packet = enet_packet_create(&state, sizeof(PeerStatePacket), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);

        if (isHostPeer)
        {
            enet_host_broadcast(host, 0, packet);
        }
        else if (peer)
        {
            enet_peer_send(peer, 0, packet);
        }
        enet_host_flush(host);
    }
};