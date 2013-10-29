//
//  CollisionEvent.cpp
//  EntitySystem
//
//  Created by Elvis on 10/9/13.
//
//

#include "CollisionEvent.h"

const char* CollisionEvent::COLLISION_EVENT_TYPE="CollisionEventType";

CollisionEvent::CollisionEvent(Entity* l,Entity* r)
:EventCustom(CollisionEvent::COLLISION_EVENT_TYPE)
{
    _left=l;
    _right=r;
}