//
//  MoveComponent.cpp
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#include "MoveComponent.h"
MoveComponent* MoveComponent::initWithMoveTarget(Point moveTarget, float maxVelocity, float maxAcceleration)
{
    mMoveTarget=moveTarget;
    mVelocity=Point::ZERO;;
    mAcceleration=Point::ZERO;;
    mMaxVelocity=maxVelocity;
    mMaxAcceleration=maxAcceleration;
    
    return this;
}