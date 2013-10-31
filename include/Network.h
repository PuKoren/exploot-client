#ifndef _NETWORK_H
#define _NETWORK_H

#include <iostream>
#include <enet/enet.h>
#include <string.h>
#include "config.h"

class Network{
public:
    Network();
    ~Network();
    bool Connect();
    void Send(char* message);
    int Update(ENetEvent& event);
private:
    ENetHost* client;
    ENetPeer* peer;
    bool connected;
};

#endif