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

    this->m_bullet = new Bullet();
    m_player = new Player(smgr, m_bullet, device->getEventReceiver());
    for(int i = 0; i < 100; i++){
        irr::scene::ISceneNode* tmp = smgr->addCubeSceneNode(1.0f, 0, 0, core::vector3df(rand()%40, rand()%40 + 20, 40.f));
        tmp->getMaterial(0).EmissiveColor = irr::video::SColor(255, 128, 50, 30);
        m_bullet->AddBox(tmp, 1.f)->setLinearFactor(btVector3(1, 1, 0));
    }

    WorldGenerator gen(smgr, device->getVideoDriver(), m_bullet);
    gen.LoadLevel(0, 0);
    gen.LoadLevel(1, 0);
    gen.LoadLevel(2, 0);
}

InGameScreen::~InGameScreen(){
    delete this->m_player;
    delete this->m_bullet;
}

bool InGameScreen::OnEvent(const SEvent &event){
    return false;
}

void InGameScreen::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    this->m_player->update(DeltaTime, gs);
    this->m_bullet->UpdatePhysics(DeltaTime);
}

void InGameScreen::drawAll(){

}
