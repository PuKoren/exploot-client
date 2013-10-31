#include "Menu.h"

Menu::Menu(IrrlichtDevice* device){
    smgr = device->getSceneManager();
    driver = device->getVideoDriver();
    device->getCursorControl()->setVisible(true);
    device->setEventReceiver(&eventReceiver);

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

    water = new RealisticWaterSceneNode(smgr, 2560, 2560, "../submodules/RealisticWaterSceneNode/", core::dimension2du(2560, 2560), terrain, -1);
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
        "../resources/fonts/Cicle_Gordita.ttf", 16);

    guienv = device->getGUIEnvironment();
    guienv->getSkin()->setFont(default_font, gui::EGDF_DEFAULT);
    guienv->getSkin()->setColor(gui::EGDC_3D_FACE, video::SColor(100, 0, 0, 0));
    guienv->getSkin()->setColor(gui::EGDC_3D_SHADOW, video::SColor(180, 0, 0, 0));
    guienv->getSkin()->setColor(gui::EGDC_3D_DARK_SHADOW, video::SColor(180, 0, 0, 0));
    guienv->getSkin()->setColor(gui::EGDC_3D_HIGH_LIGHT, video::SColor(100, 0, 0, 0));
    guienv->getSkin()->setColor(gui::EGDC_3D_LIGHT, video::SColor(120, 0, 0, 0));
    guienv->getSkin()->setColor(gui::EGDC_EDITABLE, video::SColor(45, 0, 0, 0));
    guienv->getSkin()->setColor(gui::EGDC_FOCUSED_EDITABLE, video::SColor(25, 0, 0, 0));
    guienv->getSkin()->setColor(gui::EGDC_BUTTON_TEXT, video::SColor(255, 255, 255, 255));

    gui::IGUIStaticText* version = guienv->addStaticText(L"v0.0.1", core::rect<irr::s32>(0,0, driver->getScreenSize().Width-5, driver->getScreenSize().Height), false, true);
    version->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
    version->setTextAlignment(gui::EGUIA_LOWERRIGHT, gui::EGUIA_LOWERRIGHT);
    version->setOverrideColor(video::SColor(255, 255, 255, 255));

    gui::IGUIStaticText* title = guienv->addStaticText(L"EXPLOOT", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3), false, true);
    title->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
    title->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    title->setOverrideColor(video::SColor(255, 255, 255, 255));
    title->setOverrideFont(title_font);

    gui::IGUIWindow* overlay = guienv->addWindow(core::rect<irr::s32>(0, 0, LOGIN_WIDTH, LOGIN_HEIGHT), false);
    overlay->setRelativePosition(core::position2di(driver->getScreenSize().Width/2 - 350/2, driver->getScreenSize().Height/2 - 200/2));
    overlay->setAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    overlay->setDrawTitlebar(false);
    overlay->getCloseButton()->setVisible(false);
    overlay->setDraggable(false);

    loginBox = guienv->addEditBox(L"", core::rect<irr::s32>(0, 0, TEXTBOX_WIDTH, TEXTBOX_HEIGHT), true, overlay);
    passwordBox = guienv->addEditBox(L"", core::rect<irr::s32>(0, 0, TEXTBOX_WIDTH, TEXTBOX_HEIGHT), true, overlay);
    loginBox->setAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    passwordBox->setAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    loginBox->setRelativePosition(core::position2di(LOGIN_WIDTH/2 - TEXTBOX_WIDTH/2, TEXTBOX_HEIGHT));
    passwordBox->setRelativePosition(core::position2di(LOGIN_WIDTH/2 - TEXTBOX_WIDTH/2, TEXTBOX_HEIGHT*2 + 5));
    passwordBox->setPasswordBox(true);
    loginBox->setOverrideColor(video::SColor(255, 255, 255, 255));
    passwordBox->setOverrideColor(video::SColor(255, 255, 255, 255));

    gui::IGUIStaticText* loginText = guienv->addStaticText(L"Login", core::rect<irr::s32>(0, 0, 50, TEXTBOX_HEIGHT), false, true, overlay);
    loginText->setRelativePosition(core::position2di(LOGIN_WIDTH/2 - TEXTBOX_WIDTH/2 - loginText->getTextWidth() -5, TEXTBOX_HEIGHT));
    loginText->setTextAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_CENTER);
    loginText->setAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    loginText->setOverrideColor(video::SColor(255, 255, 255, 255));

    gui::IGUIStaticText* passwordText = guienv->addStaticText(L"Pass", core::rect<s32>(0, 0, 50, TEXTBOX_HEIGHT), false, true, overlay);
    passwordText->setRelativePosition(core::position2di(LOGIN_WIDTH/2 - TEXTBOX_WIDTH/2 - passwordText->getTextWidth() -5, TEXTBOX_HEIGHT*2 + 5));
    passwordText->setTextAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_CENTER);
    passwordText->setAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    passwordText->setOverrideColor(video::SColor(255, 255, 255, 255));

    gui::IGUIStaticText* noticeText = guienv->addStaticText(L"Press \"Enter\" to log in or \"Escape\" to quit.", core::rect<irr::s32>(0, 0, LOGIN_WIDTH, 25), false, true, overlay);
    noticeText->setRelativePosition(core::position2di(0, LOGIN_HEIGHT - noticeText->getTextHeight() - 10));
    noticeText->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    noticeText->setAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    noticeText->setOverrideColor(video::SColor(255, 255, 255, 255));

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
}

void Menu::update(u32 DeltaTime, GAME_STATE* gs){
    if(eventReceiver.IsKeyDown(KEY_RETURN)){
        if(wcslen(loginBox->getText()) > 0 && wcslen(passwordBox->getText()) > 0){
            Message msg;
            Message::MessageData* msgData = msg.add_message();
            msgData->set_type(Message_MessageType_CONNECT);
            Connect connectInfo;
            CConverter converter;
            connectInfo.set_nickname(converter.wchartToStr(loginBox->getText()));
            connectInfo.set_passhash(converter.wchartToStr(passwordBox->getText()));
            msgData->set_data(connectInfo.SerializeAsString());

            Network net;
            if(net.Connect()){
                net.Send((char*)msg.SerializeAsString().c_str());
            }else{
                //server connect error !
            }
            
        }else{
            //print message for user to check the input boxes content
        }
    }

    if(eventReceiver.IsKeyDown(KEY_ESCAPE)){
        *gs = MENU_EXIT;
    }
}

void Menu::drawAll(){
    guienv->drawAll();
}
