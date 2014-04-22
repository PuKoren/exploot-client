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

	int getPing();
    bool Connect();
	std::string getChallenge();

	bool Connected();
    void Send(Message& message);
    int Update(ENetEvent& event, Message::MessageType&, std::string&);
private:
	int ping;
	bool connected;

	ENetPeer* peer;
    ENetHost* client;

    std::string challenge;
};

#endif
