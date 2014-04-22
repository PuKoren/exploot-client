#include <vector>
#include <iostream>
#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "config.h"
#include "md5.h"
#include "CConverter.h"
#include "CGUITTFont.h"
#include "RealisticWaterSceneNode/RealisticWater.h"
#include "Network.h"
#include "exploot-protobuf/build/Message.pb.h"
#include "exploot-protobuf/build/Connect.pb.h"
#include "exploot-protobuf/build/Connect.callback.pb.h"

namespace LoginSteps{
	enum Steps{
		NONE,
		CHALLENGE,
		CREDENTIALS,
		DONE
	};
}

class Menu: public IGameObject{
private:
	LoginSteps::Steps login_step;

    gui::IGUIEditBox*  loginBox;
    gui::IGUIEditBox*  passwordBox;
	gui::IGUIStaticText* errorText;

	scene::ISceneManager* smgr;
	irr::IrrlichtDevice* device;
    video::IVideoDriver* driver;
	gui::CGUITTFont* title_font;
	scene::ICameraSceneNode* camera;
	
	RealisticWaterSceneNode* water;

    Network* net;
    
	void sendCredentials();

public:
    Menu(IrrlichtDevice* device, Network* net);
    ~Menu();
    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE&);
    virtual void drawAll();
};
