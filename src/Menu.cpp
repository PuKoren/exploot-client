#include "Menu.h"

Menu::Menu(IrrlichtDevice* device){
    smgr = device->getSceneManager();
    driver = device->getVideoDriver();

    if(!smgr || !driver)
        return;

    camera = smgr->addCameraSceneNodeFPS(0,100.0f,1.2f);
    camera->setPosition(core::vector3df(2700*2,255*2,2600*2));
    camera->setTarget(core::vector3df(2397*2,343*2,2700*2));
    camera->setFarValue(42000.0f);

    terrain = smgr->addTerrainSceneNode(
                "../resources/terrain/heightmap.jpg",
                0,                  // parent node
                -1,                 // node id
                core::vector3df(0.f, 0.f, 0.f),     // position
                core::vector3df(0.f, 0.f, 0.f),     // rotation
                core::vector3df(40.f, 4.4f, 40.f),  // scale
                video::SColor ( 255, 255, 255, 255 ),   // vertexColor
                5,                  // maxLOD
                scene::ETPS_17,             // patchSize
                4                   // smoothFactor
                );

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
    terrain->setMaterialTexture(0, driver->getTexture("../resources/terrain/texture.jpg"));
    terrain->scaleTexture(1.0f, 20.0f);
}

Menu::~Menu(){
    camera->remove();
    terrain->remove();
}

void Menu::Update(u32 DeltaTime){

}