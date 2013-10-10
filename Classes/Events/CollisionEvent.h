//
//  CollisionEvent.h
//  EntitySystem
//
//  Created by Elvis on 10/9/13.
//
//

#ifndef __EntitySystem__CollisionEvent__
#define __EntitySystem__CollisionEvent__

#include <iostream>
#include "cocos2d.h"
#include "Entity.h"

class CollisionEvent:public Event
{
public:
    CollisionEvent(Entity& l,Entity& r);
    
    Entity* getLeft(){return _left;}
    Entity* getRight(){return _right;}
private:
    Entity* _left;
    Entity* _right;
};

#endif /* defined(__EntitySystem__CollisionEvent__) */
