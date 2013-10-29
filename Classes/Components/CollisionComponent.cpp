//
//  CollisionComponent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/12/13.
//
//

#include "CollisionComponent.h"
const char* CollisionComponent::COLLISION_TYPE="CollisionComponentType";

CollisionComponent* CollisionComponent::create()
{
    CollisionComponent* com=new CollisionComponent();
    if(com){
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return NULL;
}

CollisionComponent::CollisionComponent()
:ECSComponent(CollisionComponent::COLLISION_TYPE)
{
    
}