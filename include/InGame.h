#pragma once
#include <irrlicht/irrlicht.h>
#include <vector>
#include <math.h>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "config.h"
#include "CConverter.h"
#include "CGUITTFont.h"
#include "CGUIEmptyElement.h"
#include "Network.h"
#include "WorldGenerator.h"
#include "exploot-protobuf/build/Message.pb.h"
#include "exploot-protobuf/build/Characters.pb.h"
#include "Bullet.h"
#include "Player.h"

namespace InGameStates{
    enum States{
        LOAD,
        PLAY,
        PAUSE,
        QUIT
    };
}

class InGameScreen: public IGameObject, public IEventReceiver{
private:
    Network* mNet;
    EventReceiver* eventmgr;
    IrrlichtDevice* device;
    gui::CGUITTFont* title_font;
    scene::ICameraSceneNode* camera;
    InGameStates::States mGameState;
    virtual bool OnEvent(const SEvent& event);
    Bullet* m_bullet;
    Player* m_player;
public:
    InGameScreen(irr::IrrlichtDevice* device, Network* pNet);
    ~InGameScreen();

    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE& gs);
    virtual void drawAll();
};
