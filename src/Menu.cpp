#include "Menu.h"

Menu::Menu(IrrlichtDevice* device){
    smgr = device->getSceneManager();
    driver = device->getVideoDriver();

    if(!smgr || !driver)
        return;

    camera = smgr->addCameraSceneNodeFPS(0,100.0f,1.2f);
    camera->setPosition(core::vector3df(1696.99f,82.1664f,1117.61f));
    camera->setTarget(core::vector3df(10,0,0));
    camera->setRotation(core::vector3df(7.91f, 188.f, 0.f));

    camera->setFarValue(8000.f);
    
    
    terrain = smgr->addTerrainSceneNode(
                "../resources/terrain/heightmap.jpg",
                0,                  // parent node
                -1,                 // node id
                core::vector3df(0, 0, 0),     // position
                core::vector3df(0.f, 0.f, 0.f),     // rotation
                core::vector3df(10.f, 1.f, 10.f),  // scale
                video::SColor ( 255, 255, 255, 255 ),   // vertexColor
                4,                  // maxLOD
                scene::ETPS_9,             // patchSize
                4                   // smoothFactor
                );

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
    terrain->setMaterialTexture(0, driver->getTexture("../resources/terrain/texture.jpg"));
    terrain->scaleTexture(1.0f, 20.0f);

    skybox = smgr->addSkyBoxSceneNode(
        driver->getTexture("../resources/skyboxes/bluesky/top.jpg"),
        NULL,
        driver->getTexture("../resources/skyboxes/bluesky/left.jpg"),
        driver->getTexture("../resources/skyboxes/bluesky/right.jpg"),
        driver->getTexture("../resources/skyboxes/bluesky/front.jpg"),
        driver->getTexture("../resources/skyboxes/bluesky/back.jpg"));

    water = new RealisticWaterSceneNode(smgr, 256, 256, "../resources/submodules/RealisticWaterSceneNode/", core::dimension2du(2560, 2560), terrain, -1);
    water->setPosition(core::vector3df(128, 45, 128));
    water->setWindForce(2.f);
    water->setWindDirection(core::vector2df(1.f, 0.5f));
    water->setWaterColor(video::SColorf(1, 1, 1, 0.f));

    scene::IAnimatedMesh* mesh = smgr->getMesh("../resources/models/trees/tree4-fbx.obj");
    scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    if(node){
        node->setScale(core::vector3df(30.f, 30.f, 30.f));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMaterialType( video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        node->setPosition(core::vector3df(2160, 20, 700));
    }
}

Menu::~Menu(){
    camera->remove();
    water->remove();
    terrain->remove();
    skybox->remove();
}

void Menu::Update(u32 DeltaTime){
}