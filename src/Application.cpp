#include "Application.h"

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, true, true, &event);
    device->setResizable(true);
    if (device){
        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));

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
    if (!driver->queryFeature(video::EVDF_PIXEL_SHADER_1_1) &&
        !driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1))
    {
        device->getLogger()->log("WARNING: Pixel shaders disabled "\
            "because of missing driver/hardware support.");
    }

    if (!driver->queryFeature(video::EVDF_VERTEX_SHADER_1_1) &&
        !driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1))
    {
        device->getLogger()->log("WARNING: Vertex shaders disabled "\
            "because of missing driver/hardware support.");
    }

    menu = new Menu(device);
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
        
        switch(state){
            case MENU_MAIN:
                menu->update(DeltaTime);
                break;
        }

        int fps = driver->getFPS();
        if (lastFPS != fps){
            core::stringw str = L"Exploot - Client - 0.0.1 [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }

        if(device->isWindowActive()){
            driver->beginScene(true, true, video::SColor(255,100,100,100));
            smgr->drawAll();
            switch(state){
                case MENU_MAIN:
                    menu->drawAll();
                    break;
            }
            driver->endScene();
        }
    }

    return true;
}
