#pragma once
#include <irrlicht/irrlicht.h>
#include <vector>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "config.h"
#include "CConverter.h"
#include "CGUITTFont.h"
#include "Network.h"
#include "exploot-protobuf/build/Message.pb.h"
#include "exploot-protobuf/build/Characters.pb.h"

namespace CharacterStates{
    enum States{
        LIST,
        LIST_PENDING,
        LIST_DONE,
		SELECT,
		CREATE
	};
}

struct Character{
    int char_id;
    int char_level;
    std::string char_name;
};

class CharacterScreen: public IGameObject{
private:
    Network* mNet;
    EventReceiver* eventmgr;

    IrrlichtDevice* device;
    gui::CGUITTFont* title_font;
    irr::u32 mSelectedCharId;
    gui::IGUIStaticText* mSelectedCharName;
    scene::ICameraSceneNode* camera;

    CharacterStates::States mScreenState;
    std::vector<Character> mCharList;

    void updateCharacterList();
    void requestCharacterList();

public:
    CharacterScreen(irr::IrrlichtDevice* device, Network* pNet);
    ~CharacterScreen();

    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE& gs);
    virtual void drawAll();
};
