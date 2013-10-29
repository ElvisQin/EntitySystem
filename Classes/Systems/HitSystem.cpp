//
//  HitSystem.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "HitSystem.h"
#include "CollisionEvent.h"
#include "HitComponent.h"
#include "HealthComponent.h"

HitSystem* HitSystem::create(EntityManager* em)
{
    HitSystem* sys=new HitSystem();
    if (sys) {
        sys->initWithManager(em);
        return sys;
    }
    
    CC_SAFE_RELEASE(sys);
    return nullptr;
}

HitSystem::HitSystem()
{
    
}

//对碰撞事件做攻击计算
void HitSystem::configure()
{
    auto listener=EventListenerCustom::create(CollisionEvent::COLLISION_EVENT_TYPE, CC_CALLBACK_1(HitSystem::hit,this));
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 1);
}

void HitSystem::hit(EventCustom* event)
{
    CollisionEvent* colEvent=(CollisionEvent*)event;
    HitComponent* leftHit=(HitComponent*)_entityManager->getComponentForEntity(HitComponent::HTT_TYPE, colEvent->getLeft());
    HitComponent* rightHit=(HitComponent*)_entityManager->getComponentForEntity(HitComponent::HTT_TYPE, colEvent->getRight());
    
    HealthComponent* leftHealth=(HealthComponent*)_entityManager->getComponentForEntity(HealthComponent::HEALTH_TYPE, colEvent->getLeft());
    HealthComponent* rightHealth=(HealthComponent*)_entityManager->getComponentForEntity(HealthComponent::HEALTH_TYPE, colEvent->getRight());
    
    if (!leftHit||!rightHit||!leftHealth||!rightHealth) {
        return;
    }
    
    if (leftHealth->curHP<=0||rightHealth->curHP<=0) {
        return;
    }
    
    if(_entityManager->getComponentForEntity(rightHit->targetType, colEvent->getLeft())||
       _entityManager->getComponentForEntity(leftHit->targetType, colEvent->getRight()))
    {
        leftHealth->curHP-=rightHit->ATT;
        rightHealth->curHP-=leftHit->ATT;
    }
}
