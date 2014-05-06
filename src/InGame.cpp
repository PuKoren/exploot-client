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

    camera = smgr->addCameraSceneNodeFPS();
    camera->setPosition(core::vector3df(0,0, -100));
    camera->setTarget(core::vector3df(0.f, 0.f, 0.f));

    irr::video::IImage* map = driver->createImageFromFile("../resources/terrain/world_01.png");

    int decal = 32;
    for(irr::u32 zone = 0; zone < 4; zone++){
        for(irr::u32 y = 0; y < decal; y++){
            for(irr::u32 x = 0; x < map->getDimension().Width; x++){
                if(map->getPixel(x, y + (zone*decal)).getRed() == 170 && map->getPixel(x, y + (zone*decal)).getGreen() == 85){
                    irr::u32 until = x;
                    do{
                        until++;
                    }while(until < map->getDimension().Width && map->getPixel(until, y+ (zone*decal)).getRed() == 170 && map->getPixel(until, y+ (zone*decal)).getGreen() == 85);
                    float decalX = (until-x)/2.f;
                    smgr->addCubeSceneNode(1.f, 0, -1, core::vector3df(decalX + x, decal-y, (4-zone) * 40), core::vector3df(0.f, 0.f, 0.f), core::vector3df(until-x, 1.f, 3.f));
                    x = until-1;
                }
            }
        }
    }


    /*
    for(irr::u32 x = 0; x < map->getDimension().Width; x++){
        for(irr::u32 y = 0; y < map->getDimension().Height; y++){
            int zone = floor(y/32);
            float z = 20 * zone;
            if(map->getPixel(x, y).getRed() == 170 && map->getPixel(x, y).getGreen() == 85){
                smgr->addCubeSceneNode(1.f, 0, -1, core::vector3df(x, (128-y)-(32*zone), z));
            }
        }
    }*/
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
