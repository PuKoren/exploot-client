#pragma once
#include <irrlicht/irrlicht.h>
#include <string>

class WorldGenerator{
public:
    WorldGenerator();
    WorldGenerator(irr::scene::ISceneManager* p_smgr, irr::video::IVideoDriver* p_drv);
    ~WorldGenerator();

    void LoadLevel(short p_lvl, short p_dim);
private:
    irr::scene::ISceneManager* m_smgr;
    irr::video::IVideoDriver* m_drv;
};
