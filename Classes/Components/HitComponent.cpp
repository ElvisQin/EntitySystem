//
//  HitComponent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "HitComponent.h"

const char* HitComponent::HTT_TYPE="HitComponentType";

HitComponent* HitComponent::create(const char* t,int a)
{
    HitComponent* com=new HitComponent(t,a);
    if(com){
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return nullptr;
}

HitComponent::HitComponent(const char* t,int a)
:ECSComponent(HitComponent::HTT_TYPE)
,targetType(t)
,ATT(a)
{
    
}