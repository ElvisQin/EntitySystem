//
//  MoveSystem.cpp
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#include "MoveSystem.h"
CCPoint MoveSystem::arriveEntity(Entity* entity,MoveComponent* move,RenderComponent* render)
{
    CCPoint vector=ccpSub(move->mMoveTarget, render->getNode()->getPosition());
    float distance=ccpLength(vector);
    
    float targetRadius=5;
    float slowRadius=targetRadius+25;
    static float timeToTarget=0.1;
    
    if(distance<targetRadius)
    {
        return CCPointZero;
    }
    
    float targetSpeed;
    if (distance>slowRadius) {
        targetSpeed=move->mMaxVelocity;
    }
    else {
        targetSpeed=move->mMaxVelocity*distance/slowRadius;
    }
    
    CCPoint targetVelocity=ccpMult(ccpNormalize(vector), targetSpeed);
    CCPoint acceleration=ccpMult(ccpSub(targetVelocity,move->mVelocity), 1/timeToTarget);
    if(ccpLength(acceleration)>move->mMaxAcceleration){
        acceleration=ccpMult(ccpNormalize(acceleration), move->mMaxAcceleration);
    }
    
    return acceleration;
}

CCPoint MoveSystem::separateEntity(Entity* entity,MoveComponent* move,RenderComponent* render)
{
    CCPoint steering=CCPointZero;
    CCArray* entities=_entityManager->getAllEntitiesPosessingComponent(RenderComponentType);
    if(entities)
    {
        for (int i=0;i<entities->count(); i++)
        {
            Entity* otherEntity=(Entity*)entities->objectAtIndex(i);
            if(otherEntity->getEntityId()==entity->getEntityId()) continue;
            
            RenderComponent* otherRender=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponentType, otherEntity);
            CCPoint direction=ccpSub(render->getNode()->getPosition(), otherRender->getNode()->getPosition());
            float distance=ccpLength(direction);
            static float SEPARATE_THRESHHOLD=20;
            
            if(distance<SEPARATE_THRESHHOLD)
            {
                direction=ccpNormalize(direction);
                steering=ccpAdd(steering, ccpMult(direction, move->mMaxAcceleration));
            }
        }
    }
    
    return steering;
}

void MoveSystem::update(float dt)
{
    CCArray* entities=_entityManager->getAllEntitiesPosessingComponent(MoveComponentType);
    if(!entities)
    {
        return;
    }
    
    for (int i=0; i<entities->count(); i++)
    {
        Entity* entity=(Entity*)entities->objectAtIndex(i);
        MoveComponent* move=(MoveComponent*)_entityManager->getComponentForEntity(MoveComponentType, entity);
        RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponentType, entity);
        
        if(!move||!render) continue;
        
        CCPoint arrivePart=arriveEntity(entity, move, render);
        CCPoint separatePart=separateEntity(entity, move, render);
        CCPoint newAcceleration=ccpAdd(arrivePart, separatePart);
        
        move->mAcceleration=ccpAdd(move->mAcceleration, newAcceleration);
        if(ccpLength(move->mAcceleration)>move->mMaxAcceleration)
        {
            move->mAcceleration = ccpMult(ccpNormalize(move->mAcceleration), move->mMaxAcceleration);
        }
        
        // Update current velocity based on acceleration and dt, and clamp
        move->mVelocity = ccpAdd(move->mVelocity, ccpMult(move->mAcceleration, dt));
        if (ccpLength(move->mVelocity) > move->mMaxVelocity) {
            move->mVelocity = ccpMult(ccpNormalize(move->mVelocity), move->mMaxVelocity);
        }
        
        // Update position based on velocity
        CCPoint newPosition = ccpAdd(render->getNode()->getPosition(), ccpMult(move->mVelocity, dt));
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        newPosition.x = MAX(MIN(newPosition.x, winSize.width), 0);
        newPosition.y = MAX(MIN(newPosition.y, winSize.height), 0);
        render->getNode()->setPosition(newPosition);
    }
}
