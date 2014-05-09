#include "Player.h"

Player::Player(scene::ISceneManager *p_smgr, Bullet *p_bullet, irr::IEventReceiver* p_event){
    m_smgr = p_smgr;
    m_bullet = p_bullet;
    m_event = (EventReceiver*)p_event;

    m_node = m_smgr->addCubeSceneNode(1.0f, 0, 0, core::vector3df(60.f, 40.f, 40.f));
    m_node->getMaterial(0).EmissiveColor = irr::video::SColor(255, 255, 255, 255);
    m_rbody = m_bullet->AddBox(m_node, 1.f);
    m_rbody->setLinearFactor(btVector3(1, 1, 0));
    //m_rbody->setUserPointer(this);
    m_layer = PLAYER;
}


Player::~Player(){

}

void Player::drawAll(){

}

void Player::collisionCallback(IBulletObject* p_obj){

}

void Player::update(u32 DeltaTime, GameStates::GAME_STATE &gs){

    if(m_event->IsKeyDown(KEY_SPACE)){
        m_rbody->applyCentralImpulse(btVector3(0,1,0));
    }

    if(m_event->IsKeyDown(KEY_LEFT)){
        m_rbody->applyCentralImpulse(btVector3(-1,0,0));
    }

    if(m_event->IsKeyDown(KEY_RIGHT)){
        m_rbody->applyCentralImpulse(btVector3(1,0,0));
    }

}
