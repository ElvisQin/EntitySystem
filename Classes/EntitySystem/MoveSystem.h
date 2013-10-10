//
//  MoveSystem.h
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#ifndef __EntitySystem__MoveSystem__
#define __EntitySystem__MoveSystem__

#include "System.h"
#include "MoveComponent.h"
#include "EntityManager.h"
#include "RenderComponent.h"

USING_NS_CC;

class MoveSystem:public System
{
public:
    CCPoint arriveEntity(Entity* entity,MoveComponent* move,RenderComponent* render);
    CCPoint separateEntity(Entity* entity,MoveComponent* move,RenderComponent* render);
    
    virtual void update(float dt);
};

#endif /* defined(__EntitySystem__MoveSystem__) */
