#include "CharacterScreen.h"
using namespace irr;

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

    irr::scene::ISceneNode* cube = smgr->addSphereSceneNode(5.f, 64);
    irr::scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0, 0.2f, 0));
    if(anim){
        cube->addAnimator(anim);
    }
    anim->drop();

    title_font = gui::CGUITTFont::createTTFont(guienv, "../resources/fonts/BEBAS.ttf", 78);

    gui::IGUIStaticText* title = guienv->addStaticText(L"Character Select", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3));
    //title->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
    title->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    title->setOverrideColor(video::SColor(255, 255, 255, 255));
    title->setOverrideFont(title_font);

    mSelectedCharName = guienv->addStaticText(L"", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3));
    mSelectedCharName->setRelativePosition(core::position2di(0, driver->getScreenSize().Height - driver->getScreenSize().Height/3));
    //character->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
    mSelectedCharName->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
    mSelectedCharName->setOverrideColor(video::SColor(255, 255, 255, 255));


    create = guienv->addButton(core::rect<s32>(0, 0, 100, 50), mSelectedCharName, -1, L"Create", L"Create a new character");
    create->setRelativePosition(core::position2di(driver->getScreenSize().Width/2 - 50, mSelectedCharName->getTextHeight()));
    //character->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);

    eventmgr->setListener(this);
}

CharacterScreen::~CharacterScreen(){
    title_font->drop();
	eventmgr->remListener();
}

bool CharacterScreen::OnEvent(const SEvent& e){
    if (e.EventType == irr::EET_GUI_EVENT){
		if(e.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED){
			core::vector3df finalPos = device->getSceneManager()->getRootSceneNode()->getPosition();
			if(mScreenState == CharacterStates::CREATE){
				mScreenState = CharacterStates::LIST;
				create->setText(L"Cancel");
				finalPos.X = 0.0f;
			}else{
				mScreenState = CharacterStates::CREATE;
				create->setText(L"Create");
				finalPos.X = -200.0f;				
			}
			scene::ISceneNodeAnimator* anim = device->getSceneManager()->createFlyStraightAnimator(
						device->getSceneManager()->getRootSceneNode()->getPosition(),
						finalPos, 1000);
			device->getSceneManager()->getRootSceneNode()->addAnimator(anim);
			anim->drop();
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
