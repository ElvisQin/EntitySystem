//
//  CollisionComponent.h
//  HelloCpp
//
//  Created by Elvis on 10/12/13.
//
//

#ifndef __HelloCpp__CollisionComponent__
#define __HelloCpp__CollisionComponent__

#include <iostream>
#include "Component.h"

/** 碰撞数据 */
class CollisionComponent : public ECSComponent
{
public:
    static const char* COLLISION_TYPE;
    static CollisionComponent* create();
    
protected:
    CollisionComponent();
};

#endif /* defined(__HelloCpp__CollisionComponent__) */