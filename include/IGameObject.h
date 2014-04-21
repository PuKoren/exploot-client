#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include <irrlicht/irrlicht.h>
#include "config.h"

class IGameObject{
public:
    virtual ~IGameObject() {};
    virtual void drawAll() = 0;
    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE& gs) = 0;
};

#endif