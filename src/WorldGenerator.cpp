#include "WorldGenerator.h"

using namespace irr;

WorldGenerator::WorldGenerator(){
    m_smgr = NULL;
    m_drv = NULL;
    m_bullet = NULL;
}

WorldGenerator::WorldGenerator(scene::ISceneManager* p_smgr, video::IVideoDriver* p_drv, Bullet* p_bullet){
    m_smgr = p_smgr;
    m_drv = p_drv;
    m_bullet = p_bullet;
}

WorldGenerator::~WorldGenerator(){

}

void WorldGenerator::LoadLevel(short p_lvl, short p_dim){
    if(!m_drv) return;

    char buffer [50];
    sprintf(buffer, "../resources/terrain/world_%d%d.png", p_dim, p_lvl);
    irr::video::IImage* map = m_drv->createImageFromFile(buffer);

    irr::u32 decal = 32;
    for(irr::u32 zone = 0; zone < 4; zone++){
        for(irr::u32 y = 0; y < decal; y++){
            for(irr::u32 x = 0; x < map->getDimension().Width; x++){
                if(map->getPixel(x, y + (zone*decal)).getRed() == 170 && map->getPixel(x, y + (zone*decal)).getGreen() == 85){
                    irr::u32 until = x;
                    do{
                        until++;
                    }while(until < map->getDimension().Width && map->getPixel(until, y+ (zone*decal)).getRed() == 170 && map->getPixel(until, y+ (zone*decal)).getGreen() == 85);
                    float decalX = (p_lvl-1)*128 + (until-x)/2.f;
                    irr::scene::ISceneNode* node = m_smgr->addCubeSceneNode(1.f, 0, -1, core::vector3df(decalX + x, decal-y, (4-zone) * 40), core::vector3df(0.f, 0.f, 0.f), core::vector3df(until-x, 1.f, 3.f));
                    node->getMaterial(0).EmissiveColor = irr::video::SColor(255, map->getPixel(x, y + (zone*decal)).getRed(), map->getPixel(x, y + (zone*decal)).getGreen(), map->getPixel(x, y + (zone*decal)).getBlue());
                    m_bullet->AddBox(node, 0.f, true);
                    x = until-1;
                }
            }
        }
    }
}
