#include <irrlicht/irrlicht.h>
using namespace irr;

class Menu{
private:
    scene::ICameraSceneNode* camera;
    scene::ITerrainSceneNode* terrain;
public:
    Menu(scene::ISceneManager* smgr, video::IVideoDriver* driver);
    ~Menu();
    void Update(u32 DeltaTime);
};
