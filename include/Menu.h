#include <irrlicht/irrlicht.h>
#include "RealisticWaterSceneNode\RealisticWater.h"
using namespace irr;

class Menu{
private:
    scene::ICameraSceneNode* camera;
    scene::ITerrainSceneNode* terrain;
    scene::ISceneNode* skybox;
    RealisticWaterSceneNode* water;
    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;
public:
    Menu(IrrlichtDevice* device);
    ~Menu();
    void Update(u32 DeltaTime);
};
