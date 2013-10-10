//
//  CollisionEvent.cpp
//  EntitySystem
//
//  Created by Elvis on 10/9/13.
//
//

#include "CollisionEvent.h"
CollisionEvent::CollisionEvent(Entity& l,Entity& r)
{
    _left=&l;
    _right=&r;
}