//
//  GunSystem.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__GunSystem__
#define __HelloCpp__GunSystem__

#include <iostream>
#include "System.h"

class GunSystem:public ECSSystem
{
public:
    static GunSystem* create(EntityManager*);
    
    virtual void update(float dt);
};

#endif /* defined(__HelloCpp__GunSystem__) */
