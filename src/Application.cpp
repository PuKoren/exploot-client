#include "Application.h"
using namespace irr;

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600), 32, false, true, true, &eventReceiver);
	oldState = state = GameStates::MENU;
    scene = NULL, net = NULL;
	
	if (device){
		device->setResizable(true);
        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));

        //network manager
        net = new Network();
        debug();

		default_font = gui::CGUITTFont::createTTFont(device->getGUIEnvironment(), "../resources/fonts/Cicle_Gordita.ttf", 16);

        gui::IGUISkin* guienv = device->getGUIEnvironment()->getSkin();
		guienv->setFont(default_font, gui::EGDF_DEFAULT);
		guienv->setColor(gui::EGDC_3D_FACE, video::SColor(100, 0, 0, 0));
		guienv->setColor(gui::EGDC_3D_SHADOW, video::SColor(180, 0, 0, 0));
		guienv->setColor(gui::EGDC_3D_DARK_SHADOW, video::SColor(180, 0, 0, 0));
		guienv->setColor(gui::EGDC_3D_HIGH_LIGHT, video::SColor(100, 0, 0, 0));
		guienv->setColor(gui::EGDC_3D_LIGHT, video::SColor(120, 0, 0, 0));
		guienv->setColor(gui::EGDC_EDITABLE, video::SColor(45, 0, 0, 0));
		guienv->setColor(gui::EGDC_FOCUSED_EDITABLE, video::SColor(25, 0, 0, 0));
		guienv->setColor(gui::EGDC_BUTTON_TEXT, video::SColor(255, 255, 255, 255));

		loadLevel();
    }
}

Application::~Application(){
	delete net;

	delete scene;
	default_font->drop();
	device->drop();
}

void Application::loadLevel(){
	if(scene) delete scene;

    device->getGUIEnvironment()->clear();
    device->getSceneManager()->clear();

	switch(state){
		case GameStates::MENU:
			scene = new Menu(device, net);
			break;
		case GameStates::CHARACTER_SELECT:
            scene = new CharacterScreen(device, net);
			break;
		case GameStates::EXIT:
			device->closeDevice();
			scene = NULL;
			break;
        case GameStates::INGAME:
            scene = new InGameScreen(device, net);
            break;
        default:
            scene = new Menu(device, net);
            break;
    }

	oldState = state;
}

void Application::debug(){
    if (!driver->queryFeature(video::EVDF_PIXEL_SHADER_1_1) && !driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1)){
        device->getLogger()->log("WARNING: Pixel shaders disabled because of missing driver/hardware support.");
    }

    if (!driver->queryFeature(video::EVDF_VERTEX_SHADER_1_1) && !driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1)){
        device->getLogger()->log("WARNING: Vertex shaders disabled because of missing driver/hardware support.");
    }
}

void Application::updateTitle(){
	int fps = driver->getFPS();
    if (lastFPS != fps){
        core::stringw str = L"Exploot - v0.0.1 [";
        str += driver->getName();
        str += "] FPS: ";
        str += fps;
		str += " | PING: ";
		str += net->getPing();

        device->setWindowCaption(str.c_str());
        lastFPS = fps;
    }
}

bool Application::run(){
    if(!device) return false;

    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;

    while(device->run() && driver){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();
        
		this->updateTitle();

        if(device->isWindowActive()){
            driver->beginScene(true, true, video::SColor(255,100,100,100));
            smgr->drawAll();
			device->getGUIEnvironment()->drawAll();
            driver->endScene();
        }

		if(scene) scene->update(DeltaTime, state);
		if(state != oldState) loadLevel();
    }

    return true;
}
