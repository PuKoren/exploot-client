#include <irrlicht/irrlicht.h>
#include "Bullet.h"
#include "Menu.h"
using namespace irr;

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
    Menu* menu;
};
