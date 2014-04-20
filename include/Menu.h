#include <vector>
#include <iostream>
#include <stdio.h>
#include <irrlicht/irrlicht.h>
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
using namespace irr;

namespace LoginSteps{
	enum Steps{
		NONE,
		CHALLENGE,
		CREDENTIALS,
		DONE
	};
}

class Menu{
private:
    scene::ICameraSceneNode* camera;
    scene::ITerrainSceneNode* terrain;
    scene::ISceneNode* skybox;
    RealisticWaterSceneNode* water;
    scene::IAnimatedMeshSceneNode* tree;

    gui::IGUIEnvironment* guienv;
    gui::CGUITTFont* title_font;
    gui::CGUITTFont* default_font;

    gui::IGUIEditBox*  loginBox;
    gui::IGUIEditBox*  passwordBox;
	gui::IGUIStaticText* ping;
	int prevPing;

    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;

    MyEventReceiver eventReceiver;
    Network* net;
    LoginSteps::Steps login_step;
public:
    Menu(IrrlichtDevice* device, Network* net);
    ~Menu();
	void sendCredentials();
    void update(u32 DeltaTime, GAME_STATE*);
    void drawAll();
};
