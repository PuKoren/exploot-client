#include "Network.h"

Network::Network(){
    connected = false;
    peer = NULL;
    if (enet_initialize () == 0){
        client = enet_host_create (NULL /* create a client host */,
                    1 /* only allow 1 outgoing connection */,
                    2 /* allow up 2 channels to be used, 0 and 1 */,
                    250000 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
                    35000 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
    }else{
        client = NULL;
    }
    challenge.clear();
}

Network::~Network(){
    if(peer){
        enet_peer_disconnect(peer, 0);
    }
    enet_host_destroy(client);
    enet_deinitialize();
}

bool Network::Connect(){
    if(connected) return true;

    ENetAddress address;
    ENetEvent event;

    enet_address_set_host (& address, SERVER_HOST);
    address.port = UDP_PORT;

    peer = enet_host_connect(client, & address, 2, 0);
    if (peer == NULL){
       return connected;
    }
    std::cout << "Connecting on " <<  SERVER_HOST << ":" << UDP_PORT << "..." << std::endl;
    if (enet_host_service (client, & event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT){
        std::cout << "Connected." << std::endl;
        connected = true;
    }else{
        std::cout << "Connection failure." << std::endl;
    }
    return connected;
}

void Network::Send(char* message){
    ENetPacket * packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peer, 0, packet);
    enet_host_flush(client);
}

int Network::Update(ENetEvent& event, Message::MessageType& type, std::string& data){
    int res = enet_host_service(client, &event, 1);
    if(res >= 0)
    {
        if(event.type == ENET_EVENT_TYPE_RECEIVE){
            Message msg;
            msg.ParseFromString((char*)event.packet->data);
            if(msg.message().size() > 0){
				const Message_MessageData& msgData = msg.message().Get(0);
				type = msgData.type();
				data = msgData.data();
            }

			if(type == Message::CHALLENGE){
				this->challenge = data;
				std::cout << "Received challenge: " << this->challenge << std::endl;
			}

			std::cout << "Received packet: " << type << " with data: " << data << std::endl;
        }
    }
    return res;
}

std::string Network::getChallenge(){
    return this->challenge;
}
