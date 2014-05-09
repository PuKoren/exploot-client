#pragma once
#include <irrlicht/irrlicht.h>
#include "config.h"

enum LAYER{
    NONE,
    FLOOR,
    PLAYER
};

class IBulletObject{
public:
    LAYER m_layer = NONE;
    virtual ~IBulletObject() {}
    virtual void collisionCallback(IBulletObject*) = 0;
};

