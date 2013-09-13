//
//  MoveComponent.cpp
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#include "MoveComponent.h"
MoveComponent* MoveComponent::initWithMoveTarget(cocos2d::CCPoint moveTarget, float maxVelocity, float maxAcceleration)
{
    mMoveTarget=moveTarget;
    mVelocity=CCPointZero;
    mAcceleration=CCPointZero;
    mMaxVelocity=maxVelocity;
    mMaxAcceleration=maxAcceleration;
    
    return this;
}