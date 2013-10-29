//
//  GhostComponent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "GhostComponent.h"
const char* GhostComponent::GHOST_TYPE="GhostComponentType";

GhostComponent* GhostComponent::create()
{
    GhostComponent* com=new GhostComponent();
    if (com) {
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return NULL;
}

GhostComponent::GhostComponent()
:ECSComponent(GhostComponent::GHOST_TYPE)
{
}