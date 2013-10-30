#include <vector>
#include <irrlicht/irrlicht.h>
#include "CGUITTFont.h"
#include "RealisticWaterSceneNode\RealisticWater.h"
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
    std::vector<gui::IGUIStaticText*> textList;

    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;
public:
    Menu(IrrlichtDevice* device);
    ~Menu();
    void update(u32 DeltaTime);
    void drawAll();
};
