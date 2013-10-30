#include "Menu.h"

Menu::Menu(IrrlichtDevice* device){
    smgr = device->getSceneManager();
    driver = device->getVideoDriver();

    if(!smgr || !driver)
        return;
    
    terrain = smgr->addTerrainSceneNode(
                "../resources/terrain/heightmap.jpg",
                0,                  // parent node
                -1,                 // node id
                core::vector3df(0, 0, 0),     // position
                core::vector3df(0.f, 0.f, 0.f),     // rotation
                core::vector3df(10.f, 1.f, 10.f),  // scale
                video::SColor ( 255, 255, 255, 255 ),   // vertexColor
                4,                  // maxLOD
                scene::ETPS_9,             // patchSize
                4                   // smoothFactor
                );

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
    terrain->setMaterialTexture(0, driver->getTexture("../resources/terrain/texture.jpg"));
    terrain->setMaterialTexture(1, driver->getTexture("../resources/terrain/detailmap3.jpg"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);

    skybox = smgr->addSkyBoxSceneNode(
        driver->getTexture("../resources/skyboxes/bluesky/top.jpg"),
        NULL,
        driver->getTexture("../resources/skyboxes/bluesky/left.jpg"),
        driver->getTexture("../resources/skyboxes/bluesky/right.jpg"),
        driver->getTexture("../resources/skyboxes/bluesky/front.jpg"),
        driver->getTexture("../resources/skyboxes/bluesky/back.jpg"));

    water = new RealisticWaterSceneNode(smgr, 2560, 2560, "../resources/submodules/RealisticWaterSceneNode/", core::dimension2du(2560, 2560), terrain, -1);
    water->setPosition(core::vector3df(128, 45, 128));
    water->setWindForce(2.f);
    water->setScale(core::vector3df(1.f/terrain->getScale().X, 1, 1.f/terrain->getScale().Z));
    water->setWindDirection(core::vector2df(1.f, 0.5f));
    water->setWaterColor(video::SColorf(1, 1, 1, 0.f));
    water->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

    scene::IAnimatedMesh* mesh = smgr->getMesh("../resources/models/trees/tree4-fbx.obj");
    tree = smgr->addAnimatedMeshSceneNode(mesh);
    if(tree){
        tree->setScale(core::vector3df(30.f, 30.f, 30.f));
        tree->setMaterialFlag(video::EMF_LIGHTING, false);
        tree->setMaterialType( video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        tree->setPosition(core::vector3df(2160, 20, 700));
    }

    title_font = gui::CGUITTFont::createTTFont(device->getGUIEnvironment(), 
        "../resources/fonts/BEBAS.ttf", 78);
    default_font = gui::CGUITTFont::createTTFont(device->getGUIEnvironment(), 
        "../resources/fonts/Aaargh.ttf", 16);

    guienv = device->getGUIEnvironment();
    guienv->getSkin()->setFont(default_font, gui::EGDF_DEFAULT);

    textList.push_back(guienv->addStaticText(L"v0.0.1", core::rect<irr::s32>(0,0, driver->getScreenSize().Width-5, driver->getScreenSize().Height), false, true));
    textList[textList.size()-1]->setTextAlignment(gui::EGUIA_LOWERRIGHT, gui::EGUIA_LOWERRIGHT);
    textList[textList.size()-1]->setOverrideColor(video::SColor(255, 255, 255, 255));

    textList.push_back(guienv->addStaticText(L"EXPLOOT", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3), false, true));
    textList[textList.size()-1]->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    textList[textList.size()-1]->setOverrideColor(video::SColor(255, 255, 255, 255));
    textList[textList.size()-1]->setOverrideFont(title_font);

    camera = smgr->addCameraSceneNode();
    camera->setPosition(core::vector3df(1950, 340, 2100));
    camera->setTarget(core::vector3df(166, 410, -166));
    camera->setFarValue(8000.f);
}

Menu::~Menu(){
    //clear gui env
    guienv->clear();
    title_font->drop();
    default_font->drop();

    //clear scene
    smgr->clear();
    camera->drop();
    water->drop();
    terrain->drop();
    tree->drop();
    skybox->drop();
}

void Menu::update(u32 DeltaTime){

}

void Menu::drawAll(){
    guienv->drawAll();
}