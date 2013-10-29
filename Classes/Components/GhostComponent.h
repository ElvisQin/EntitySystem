//
//  GhostComponent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__GhostComponent__
#define __HelloCpp__GhostComponent__

#include <iostream>
#include "Component.h"

class GhostComponent : public ECSComponent
{
public:
    static const char* GHOST_TYPE;
    static GhostComponent* create();
    
protected:
    GhostComponent();
};

#endif /* defined(__HelloCpp__GhostComponent__) */
