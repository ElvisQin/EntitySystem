//
//  BulletComponent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "BulletComponent.h"

const char* BulletComponent::BULLET_TYPE="BulletComponentType";

BulletComponent* BulletComponent::create()
{
    BulletComponent* com=new BulletComponent();
    if (com) {
        return com;
    }
    
    return nullptr;
}

BulletComponent::BulletComponent()
:ECSComponent(BulletComponent::BULLET_TYPE)
{
    
}