//
//  EntityFactory.h
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#ifndef __EntitySystem__EntityFactory__
#define __EntitySystem__EntityFactory__

#include "cocos2d.h"
#include "Entity.h"
#include "EntityManager.h"

USING_NS_CC;

class EntityFactory :public CCObject
{
public:
    EntityFactory*) initWithEntityManager(EntityManager* entityManager);
};

#endif /* defined(__EntitySystem__EntityFactory__) */
