#include <vector>
#include <iostream>
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
using namespace irr;

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

    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;

    MyEventReceiver eventReceiver;
    Network* net;
    bool logginPending;
public:
    Menu(IrrlichtDevice* device, Network* net);
    ~Menu();
    void update(u32 DeltaTime, GAME_STATE*);
    void drawAll();
};
