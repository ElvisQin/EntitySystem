//
//  MoveComponent.h
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#ifndef __EntitySystem__MoveComponent__
#define __EntitySystem__MoveComponent__

#include "Component.h"

static const std::string MoveComponentType="MoveComponent";

class MoveComponent:public ECSComponent
{
public:
    virtual const std::string& getComponentType() const{return MoveComponentType;}
    
    MoveComponent* initWithMoveTarget(Point moveTarget,float maxVelocity,float maxAcceleration);
    
    Point mMoveTarget;
    Point mVelocity;
    Point mAcceleration;
    float mMaxVelocity;
    float mMaxAcceleration;
};

#endif /* defined(__EntitySystem__MoveComponent__) */
