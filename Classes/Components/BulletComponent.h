//
//  BulletComponent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__BulletComponent__
#define __HelloCpp__BulletComponent__

#include "Component.h"

class BulletComponent:public ECSComponent
{
public:
    static const char* BULLET_TYPE;
    static BulletComponent* create();
    
private:
    BulletComponent();
};


#endif /* defined(__HelloCpp__BulletComponent__) */
