#include <irrlicht/irrlicht.h>
#include "IGameObject.h"
#include "Bullet.h"
#include "Menu.h"
#include "CharacterScreen.h"
#include "InGame.h"
#include "Network.h"

class Application{
public:
    Application();
    ~Application();
    bool run();

private:
	void loadLevel();
	GameStates::GAME_STATE state;
	GameStates::GAME_STATE oldState;

    irr::IrrlichtDevice *device;
    scene::ISceneManager *smgr;
    video::IVideoDriver* driver;
	gui::CGUITTFont* default_font;
    EventReceiver eventReceiver;

    Bullet* bullet;
	IGameObject* scene;
    Network* net;
	
	void updateTitle();
	int lastFPS;

	void debug();
};
