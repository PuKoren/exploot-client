#include "InGame.h"

InGameScreen::InGameScreen(IrrlichtDevice *device, Network *pNet){
    this->device = device;
    this->mNet = pNet;
    this->device = device;
    this->device->getCursorControl()->setVisible(true);

    //irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    //video::IVideoDriver* driver = device->getVideoDriver();
    eventmgr = (EventReceiver*)device->getEventReceiver();

    camera = smgr->addCameraSceneNode();
    camera->setPosition(core::vector3df(50.f, 20.f, -5.f));
    camera->setTarget(core::vector3df(50.f, 20.f, 0.f));

    /*
    irr::scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(camera->getPosition(), 200.f);
    camera->addAnimator(anim);
    anim->drop();
    */

    WorldGenerator gen(smgr, device->getVideoDriver());
    gen.LoadLevel(0, 0);
    gen.LoadLevel(1, 0);
    gen.LoadLevel(2, 0);
}

InGameScreen::~InGameScreen(){

}

bool InGameScreen::OnEvent(const SEvent &event){
    return false;
}

void InGameScreen::update(u32 DeltaTime, GameStates::GAME_STATE &gs){

}

void InGameScreen::drawAll(){

}
