#pragma once
#include <vector>
#include <iostream>
#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include "EventReceiver.h"
#include "config.h"
#include "Network.h"
#include "exploot-protobuf/build/Message.pb.h"

using namespace irr;

namespace CharacterScreens{
	enum Screen{
		SELECT,
		CREATE
	};
};


class CharacterScreen{
private:
    scene::ICameraSceneNode* camera;
    gui::IGUIEnvironment* guienv;
    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;
    MyEventReceiver eventReceiver;
    Network* net;
public:
    CharacterScreen(IrrlichtDevice* device, Network* net);
    ~CharacterScreen();
    void update(u32 DeltaTime, GameStates::GAME_STATE&);
    void drawAll();
};
