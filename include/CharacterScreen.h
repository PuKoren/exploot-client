#pragma once
#include <irrlicht/irrlicht.h>
#include <vector>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "config.h"
#include "CConverter.h"
#include "CGUITTFont.h"
#include "CGUIEmptyElement.h"
#include "Network.h"
#include "exploot-protobuf/build/Message.pb.h"
#include "exploot-protobuf/build/Characters.pb.h"

namespace CharacterStates{
    enum States{
        LIST,
        LIST_PENDING,
        LIST_DONE,
        CREATE,
        CREATE_PENDING,
        CREATE_DONE,
        SELECT
	};
}

struct Character{
    int char_id;
    int char_level;
    std::string char_name;
};

class CharacterScreen: public IGameObject, public IEventReceiver{
private:
    Network* mNet;
    EventReceiver* eventmgr;

    IrrlichtDevice* device;
    gui::CGUITTFont* title_font;

	gui::IGUIElement* selectScreen;
	gui::IGUIElement* createScreen;
    gui::IGUIEditBox* mCreationCharName;
    gui::IGUIStaticText* mSelectedCharName;

    scene::ICameraSceneNode* camera;

    CharacterStates::States mScreenState;

    void updateCharacterList();
    void requestCharacterList();
    void sendCharacterCreation();
    virtual bool OnEvent(const SEvent& event);

    std::vector<Character> mCharList;
    irr::u32 mSelectedCharId;
public:
    CharacterScreen(irr::IrrlichtDevice* device, Network* pNet);
    virtual ~CharacterScreen();

    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE& gs);
    virtual void drawAll();
};
