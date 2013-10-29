//
//  ShipComponent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__ShipComponent__
#define __HelloCpp__ShipComponent__

#include <iostream>
#include "Component.h"

USING_NS_CC;

class ShipComponent:public ECSComponent
{
public:
    static const char* SHIP_TYPE;
    
    static ShipComponent* create();
    
    ShipComponent();
};


#endif /* defined(__HelloCpp__ShipComponent__) */
