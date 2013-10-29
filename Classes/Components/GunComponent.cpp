//
//  GunComponent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "GunComponent.h"

const char* GunComponent::GUN_TYPE="GunComponentType";

GunComponent* GunComponent::create(const char* tt,float dis,float d)
{
    GunComponent* com=new GunComponent(tt,dis,d);
    if (com) {
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return nullptr;
}

GunComponent::GunComponent(const char* tt,float dis,float d)
:ECSComponent(GunComponent::GUN_TYPE)
,targetType(tt)
,distance(dis)
,durence(d)
{
    
}