#include "CharacterScreen.h"
using namespace irr;

CharacterScreen::CharacterScreen(IrrlichtDevice *device, Network *net){
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

    gui::IGUIStaticText* character = guienv->addStaticText(L"Koren (13)", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3));
    character->setRelativePosition(core::position2di(0, driver->getScreenSize().Height - driver->getScreenSize().Height/3));
    //character->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
    character->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_UPPERLEFT);
    character->setOverrideColor(video::SColor(255, 255, 255, 255));


    gui::IGUIButton* create = guienv->addButton(core::rect<s32>(0, 0, 100, 50), character, -1, L"Create", L"Create a new character");
    create->setRelativePosition(core::position2di(driver->getScreenSize().Width/2 - 50, character->getTextHeight()));
    //character->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
}

CharacterScreen::~CharacterScreen(){
    title_font->drop();
}

void CharacterScreen::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    if(eventmgr->IsKeyDown(KEY_ESCAPE)){
        gs = GameStates::MENU;
    }
}

void CharacterScreen::drawAll(){

}
