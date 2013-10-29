//
//  MoveComponent.cpp
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#include "MoveComponent.h"

const char* MoveComponent::MOVE_TYPE="MoveComponentType";

MoveComponent* MoveComponent::cretae(Point target, float a)
{
    MoveComponent* com=new MoveComponent(target,a);
    if(com) {
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return NULL;
}

MoveComponent::MoveComponent(Point target, float a)
:ECSComponent(MoveComponent::MOVE_TYPE)
{
    moveTarget=target;
    acceleration=a;
}