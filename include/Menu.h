#include <irrlicht/irrlicht.h>
using namespace irr;

class Menu{
private:
    scene::ICameraSceneNode* camera;
    scene::ITerrainSceneNode* terrain;
    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;
public:
    Menu(IrrlichtDevice* device);
    ~Menu();
    void Update(u32 DeltaTime);
};
