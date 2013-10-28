#include "Application.h"

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, true, false, &event);
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

    menu = new Menu(smgr, driver);

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
                menu->Update(DeltaTime);
                break;
        }

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
