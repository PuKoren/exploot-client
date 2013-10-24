#include "Application.h"

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, true, true, &event);
    if (device){
        device->setWindowCaption(L"PukoWorld - Client - 0.1");

        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));
        device->getCursorControl()->setVisible(false);

        //bullet manager
        bullet = new Bullet();

        init();

        state = MENU_MAIN;
    }else{
      bullet = NULL;
    }
}

Application::~Application(){
    if(bullet){
        delete bullet;
    }
    if(device){
        device->drop();
    }
}

void Application::init(){
    scene::ICameraSceneNode* camera =
            smgr->addCameraSceneNodeFPS(0,100.0f,1.2f);

        camera->setPosition(core::vector3df(2700*2,255*2,2600*2));
        camera->setTarget(core::vector3df(2397*2,343*2,2700*2));
        camera->setFarValue(42000.0f);
        scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
                    "../textures/terrain/heightmap.jpg",
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

          terrain->setMaterialTexture(0,
                  driver->getTexture("../textures/terrain/texture.jpg"));

          terrain->scaleTexture(1.0f, 20.0f);
}

bool Application::run(){
    if(!device){
        return false;
    }

    int lastFPS = -1;
    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;
    while(device->run()){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();
        bullet->UpdatePhysics(DeltaTime);

        int fps = driver->getFPS();
        if (lastFPS != fps){
            core::stringw str = L"PukoWorld - Client - 0.1 [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }

        driver->beginScene(true, true, video::SColor(255,100,100,100));
        smgr->drawAll();
        driver->endScene();
    }

    return true;
}
