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

/** move an entity to a target position
 * the entity will be clear if it get to the target position.
 */
class MoveSystem:public ECSSystem
{
public:
    static MoveSystem* create(EntityManager*);

    virtual void update(float dt);
};

#endif /* defined(__EntitySystem__MoveSystem__) */
