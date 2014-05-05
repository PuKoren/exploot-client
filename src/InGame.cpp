#include "InGame.h"

InGameScreen::InGameScreen(IrrlichtDevice *device, Network *pNet){
    this->device = device;
    this->mNet = pNet;
    this->device = device;
    this->device->getCursorControl()->setVisible(true);

    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    video::IVideoDriver* driver = device->getVideoDriver();
    eventmgr = (EventReceiver*)device->getEventReceiver();

    camera = smgr->addCameraSceneNode(0, core::vector3df(0.f, 0.f, -32.f));
    camera->setTarget(core::vector3df(0.f, 0.f, 0.f));

    irr::video::IImage* map = driver->createImageFromFile("../resources/terrain/world_01.png");
    for(irr::u32 x = 0; x < map->getDimension().Width; x++){
        for(irr::u32 y = 0; y < map->getDimension().Height; y++){
            int zone = floor(y/32);
            float z = 20 * zone;
            if(map->getPixel(x, y).getRed() == 170 && map->getPixel(x, y).getGreen() == 85){
                smgr->addCubeSceneNode(1.f, 0, -1, core::vector3df(x, (128-y)-(32*zone), z));
            }
        }
    }
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
