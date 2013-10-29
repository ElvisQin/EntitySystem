//
//  HealthSystem.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "HealthSystem.h"
#include "EntityManager.h"
#include "HealthComponent.h"
#include "RenderComponent.h"
#include "SimpleAudioEngine.h"
#include "CollisionEvent.h"
#include "DeadEvent.h"

HealthSystem* HealthSystem::create(EntityManager* manager)
{
    HealthSystem* sys=new HealthSystem();
    if(sys){
        sys->initWithManager(manager);
        return sys;
    }
    
    CC_SAFE_RELEASE(sys);
    return NULL;
}

// trigger DeadEvent when HP small than 0
void HealthSystem::update(float dt)
{
    const std::vector<Entity*>* entities=_entityManager->getAllEntitiesPosessingComponent(HealthComponent::HEALTH_TYPE);
    if(entities==nullptr) {
        return;
    }
    
    for (int i=0; i<entities->size(); i++){
        Entity* entity=entities->at(i);
        
        HealthComponent* health=(HealthComponent*)_entityManager->getComponentForEntity(HealthComponent::HEALTH_TYPE, entity);
        RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, entity);
        
        if(health==nullptr||!health->alive||health->maxHP==0){
            continue;
        }
        
        if(health->curHP<=0){
            health->alive=false;
            
            if(render!=nullptr) {
                Point p=render->getNode()->convertToWorldSpace(Point::ZERO);
                DeadEvent* event=DeadEvent::create(entity,p);
                EventDispatcher::getInstance()->dispatchEvent(event);
                
                render->getNode()->setUserData(entity);
                render->getNode()->runAction(CCSequence::create(FadeOut::create(0.5),
                                                                CallFuncN::create(CC_CALLBACK_1(HealthSystem::fadeCompleted,this)),NULL));
            }
            else{
                //no need animation, remove immediately.
                _entityManager->removeEntity(entity);
            }
        }
    }
}

void HealthSystem::fadeCompleted(Node* sender)
{
    Entity* entity=(Entity*)sender->getUserData();
    _entityManager->removeEntity(entity);
    sender->removeFromParentAndCleanup(true);
}

void HealthSystem::draw()
{
    const std::vector<Entity*>* entities=_entityManager->getAllEntitiesPosessingComponent(HealthComponent::HEALTH_TYPE);
    if(entities==nullptr){
        return;
    }
    
    for (int i=0; i<entities->size(); i++){
        Entity* entity=entities->at(i);
        
        HealthComponent* health=(HealthComponent*)_entityManager->getComponentForEntity(HealthComponent::HEALTH_TYPE, entity);
        RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, entity);
        if (render==nullptr||!health->needHPBar) {
            continue;
        }
        
        Node* node=render->getNode();
        
        int sX = node->getPositionX() - node->getContentSize().width/2;
        int eX = node->getPositionX()  + node->getContentSize().width/2;
        int actualY = node->getPositionY() + node->getContentSize().height/2;
        
        static int maxColor = 200;
        static int colorBuffer = 55;
        float percentage = ((float) health->curHP) / ((float) health->maxHP);
        int actualX = ((eX-sX) * percentage) + sX;
        int amtRed = ((1.0f-percentage)*maxColor)+colorBuffer;
        int amtGreen = (percentage*maxColor)+colorBuffer;
        
        glLineWidth(2);
        DrawPrimitives::setDrawColor4B(amtRed,amtGreen,0,255);
        DrawPrimitives::drawLine(Point(sX, actualY), Point(actualX, actualY));
    }
}
