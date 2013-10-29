//
//  DeadEvent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__DeadEvent__
#define __HelloCpp__DeadEvent__

#include <iostream>
#include "cocos2d.h"
#include "Entity.h"

/** 
 * an entity dead at a certain position.
 */
class DeadEvent:public EventCustom
{
public:
    Entity* entity;
    const Point& deadPoint;
    
public:
    static const char* DEAD_EVENT_TYPE;
    static DeadEvent* create(Entity* e,const Point& p);
    
protected:
    DeadEvent(Entity* e,const Point& p);
};

#endif /* defined(__HelloCpp__DeadEvent__) */
