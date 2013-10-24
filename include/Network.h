#include <enet/enet.h>
#include <string.h>
#include "config.h"

class Network{
public:
    Network();
    ~Network();
    bool Connect();
    void Send(char* message);
    void Update();
private:
    ENetHost* client;
    ENetPeer* peer;
};
