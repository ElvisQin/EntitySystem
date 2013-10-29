//
//  HitComponent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__HitComponent__
#define __HelloCpp__HitComponent__

#include <iostream>
#include "Component.h"

class HitComponent:public ECSComponent
{
public:
    const char* targetType;
    int ATT;
    
public:
    static const char* HTT_TYPE;
    static HitComponent* create(const char*,int);
    
protected:
    HitComponent(const char*,int);
};

#endif /* defined(__HelloCpp__HitComponent__) */
