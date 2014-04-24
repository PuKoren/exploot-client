#include "CharacterScreen.h"
using namespace irr;

enum GUICharacterScreen{
    GUI_ID_CREATE_BUTTON,
    GUI_ID_CREATECONFIRM_BUTTON,
	GUI_ID_CREATECANCEL_BUTTON
};

CharacterScreen::CharacterScreen(IrrlichtDevice *device, Network *pNet){
    mScreenState = CharacterStates::LIST;
    mNet = pNet;
    mSelectedCharId = 0;
    this->device = device;
    this->device->getCursorControl()->setVisible(true);

    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    video::IVideoDriver* driver = device->getVideoDriver();
    eventmgr = (EventReceiver*)device->getEventReceiver();

    smgr->addLightSceneNode(0, core::vector3df(-20, 20, -10));
    camera = smgr->addCameraSceneNode(0, core::vector3df(0, 0, -25));
	createScreen = new CGUIEmptyElement(guienv, guienv->getRootGUIElement());
	selectScreen = new CGUIEmptyElement(guienv, guienv->getRootGUIElement());

    title_font = gui::CGUITTFont::createTTFont(guienv, "../resources/fonts/BEBAS.ttf", 78);

    gui::IGUIStaticText* title = guienv->addStaticText(L"Character Select", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3), false, true, selectScreen);
    title->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    title->setOverrideFont(title_font);
	
	gui::IGUIStaticText* titlec = guienv->addStaticText(L"Character Create", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3), false, true, createScreen);
    titlec->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    titlec->setOverrideFont(title_font);

    mSelectedCharName = guienv->addStaticText(L"", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3), false, true, selectScreen);
    mSelectedCharName->setRelativePosition(core::position2di(0, driver->getScreenSize().Height - driver->getScreenSize().Height/3));
    mSelectedCharName->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);


    gui::IGUIButton* create = guienv->addButton(core::rect<s32>(0, 0, 100, 50), selectScreen, GUI_ID_CREATE_BUTTON, L"Create", L"Create a new character");
    create->setRelativePosition(core::position2di(driver->getScreenSize().Width/2 - 50, driver->getViewPort().getHeight() - 150));
	
	gui::IGUIWindow* overlay = guienv->addWindow(core::rect<s32>(0, 150, 300, 300), false, 0, createScreen);
	overlay->setDrawTitlebar(false);
    overlay->getCloseButton()->setVisible(false);
    overlay->setDraggable(false);
	
	guienv->addStaticText(L"Nickname:", core::rect<irr::s32>(500/2 - 250 - 100, 0, 100, 50), false, true, overlay);
	guienv->addEditBox(L"", core::rect<irr::s32>(500/2 - 250/2, 0, 250, 50), true, overlay);
	
	
	gui::IGUIButton* createc = guienv->addButton(core::rect<s32>(0, 0, 200, 50), createScreen, GUI_ID_CREATECONFIRM_BUTTON, L"Confirm Creation", L"Create the character and start play now !");
    createc->setRelativePosition(core::position2di(driver->getScreenSize().Width/2 - 100, driver->getScreenSize().Height - 150));
	
	gui::IGUIButton* createcancel = guienv->addButton(core::rect<s32>(0, 0, 200, 50), createScreen, GUI_ID_CREATECANCEL_BUTTON, L"Cancel", L"Back to character list");
    createcancel->setRelativePosition(createc->getRelativePosition() + core::vector2di(0, 50));
	
	createScreen->setVisible(false);
    eventmgr->setListener(this);
}

CharacterScreen::~CharacterScreen(){
    title_font->drop();
	eventmgr->remListener();
	createScreen->drop();
	selectScreen->drop();
}

bool CharacterScreen::OnEvent(const SEvent& e){
    if (e.EventType == irr::EET_GUI_EVENT){
		s32 id = e.GUIEvent.Caller->getID();
		if(e.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED){
			if(id == GUI_ID_CREATECANCEL_BUTTON){
				createScreen->setVisible(false);
				selectScreen->setVisible(true);
				return true;
			}else if(id == GUI_ID_CREATE_BUTTON){
				createScreen->setVisible(true);
				selectScreen->setVisible(false);
				return true;
			}else if(id == GUI_ID_CREATECONFIRM_BUTTON){
				//send creation information to server
			}
		}
    }

    return false;
}

void CharacterScreen::updateCharacterList(){
    std::cout << "Received character list (" << mCharList.size() << ")"<< std::endl;
    if(mCharList.size() > 0){
        CConverter c;
        mSelectedCharName->setText(c.strToWchart(mCharList[mSelectedCharId].char_name + " (" + std::to_string(mCharList[mSelectedCharId].char_level) + ")"));
    }
}

void CharacterScreen::requestCharacterList(){
    Message msg; Characters msgChar;
    Message_MessageData* msgData = msg.add_message();
    msgChar.set_type(Characters::LIST);
    msgData->set_type(Message::CHARACTER);
    std::string data= msgChar.SerializeAsString();
    msgData->set_data(data);
    mNet->Send(msg);
}

void CharacterScreen::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    if(eventmgr->IsKeyDown(KEY_ESCAPE)){
        gs = GameStates::MENU;
    }

    if(mScreenState ==  CharacterStates::LIST){
        //send character list query
        requestCharacterList();
        mScreenState = CharacterStates::LIST_PENDING;
    }

    ENetEvent ev; Message_MessageType type; std::string data;
    if(mNet->Update(ev, type, data) > 0){
        if(type == Message::CHARACTER){
            Characters msg;
            switch(mScreenState){
                case CharacterStates::LIST_PENDING:
                    msg.ParseFromString(data);
                    for(int i = 0; i < msg.characterlist_size(); i++){
                        Character c;
                        c.char_id = msg.characterlist(i).char_id();
                        c.char_level = msg.characterlist(i).char_level();
                        c.char_name = msg.characterlist(i).char_name();
                        mCharList.push_back(c);
                    }
                    updateCharacterList();
                    mScreenState = CharacterStates::LIST_DONE;
                break;
            default:
                std::cout << "Message type not handled yet." << std::endl;
                break;
            }
        }
    }
}

void CharacterScreen::drawAll(){

}
