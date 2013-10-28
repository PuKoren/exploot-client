#include <irrlicht/irrlicht.h>
#include "EventReceiver.h"
#include "Bullet.h"
#include "Menu.h"
using namespace irr;

enum GAME_STATE{
    MENU_MAIN,
    MENU_LOGIN,
    INGAME_PLAY,
    INGAME_EXIT
};

class Application{
public:
    Application();
    ~Application();
    bool run();

private:
    GAME_STATE state;
    void init();
    IrrlichtDevice *device;
    scene::ISceneManager *smgr;
    video::IVideoDriver* driver;
    gui::IGUIEnvironment* guienv;
    Bullet* bullet;
    MyEventReceiver event;
    Menu* menu;
};
