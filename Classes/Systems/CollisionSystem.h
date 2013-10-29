//
//  CollisionSystem.h
//  HelloCpp
//
//  Created by Elvis on 10/12/13.
//
//

#ifndef __HelloCpp__CollisionSystem__
#define __HelloCpp__CollisionSystem__

#include <iostream>
#include "System.h"

/** 碰撞检测 */
class CollisionSystem : ECSSystem
{
public:
    static CollisionSystem* create(EntityManager*);
    
    virtual void update(float dt);
    
    bool collide(Node* node1,Node* node2);
};

#endif /* defined(__HelloCpp__CollisionSystem__) */
