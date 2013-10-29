//
//  HitSystem.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__HitSystem__
#define __HelloCpp__HitSystem__

#include <iostream>
#include "System.h"

class HitSystem: public ECSSystem
{
public:
    static HitSystem* create(EntityManager*);
    void configure();
    
    void hit(EventCustom* event);

protected:
    HitSystem();
};

#endif /* defined(__HelloCpp__HitSystem__) */
