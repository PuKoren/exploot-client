#ifndef _NETWORK_H
#define _NETWORK_H

#include <iostream>
#include <enet/enet.h>
#include <string.h>
#include "exploot-protobuf/build/Message.pb.h"
#include "config.h"

class Network{
public:
    Network();
    ~Network();
    bool Connect();
    void Send(Message& message);
    int Update(ENetEvent& event, Message::MessageType&, std::string&);
    std::string getChallenge();
	int getPing();
private:
    ENetHost* client;
    ENetPeer* peer;
    std::string challenge;
    bool connected;
	int ping;
};

#endif
