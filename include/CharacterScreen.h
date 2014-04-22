#pragma once
#include <irrlicht/irrlicht.h>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "config.h"
#include "CGUITTFont.h"
#include "Network.h"
#include "exploot-protobuf/build/Message.pb.h"

namespace CharacterScreens{
	enum Screen{
		SELECT,
		CREATE
	};
}


class CharacterScreen: public IGameObject{
private:
    Network* net;
    EventReceiver* eventmgr;

    IrrlichtDevice* device;
    gui::CGUITTFont* title_font;
    scene::ICameraSceneNode* camera;

public:
    CharacterScreen(irr::IrrlichtDevice* device, Network* net);
    ~CharacterScreen();

    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE& gs);
    virtual void drawAll();
};
