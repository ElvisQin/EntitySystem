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

void HealthSystem::update(float dt)
{
    CCArray* entities=mEntityManager->getAllEntitiesPosessingComponent(std::string("HealthComponent"));
    if(!entities)
    {
        return;
    }
    
    for (int i=0; i<entities->count(); i++)
    {
        Entity* entity=(Entity*)entities->objectAtIndex(i);
        
        HealthComponent* health=(HealthComponent*)mEntityManager->getComponentForEntity(HealthComponentType, entity);
        RenderComponent* render=(RenderComponent*)mEntityManager->getComponentForEntity(RenderComponentType, entity);
        
        if(!health->getAlive()) return;
        if(health->getMaxHP()==0) return;
        if(health->getCurHP()<0)
        {
            health->setAlive(false);
            
            if(render)
            {
                mEid=entity->getEntityId();
                render->getNode()->runAction(CCSequence::create(CCFadeOut::create(0.5),
                                                                CCCallFuncN::create(this,
                                                                                    callfuncN_selector(HealthSystem::fadeCompleted)),
                                                                NULL));
            }
            else
            {
                mEntityManager->removeEntity(entity->getEntityId());
            }
        }
    }
}

void HealthSystem::fadeCompleted(CCNode* sender)
{
    mEntityManager->removeEntity(mEid);
    sender->removeFromParentAndCleanup(true);
}

void HealthSystem::draw()
{
    CCArray* entities=mEntityManager->getAllEntitiesPosessingComponent(std::string("HealthComponent"));
    if(!entities) return;
    
    for (int i=0; i<entities->count(); i++)
    {
        Entity* entity=(Entity*)entities->objectAtIndex(i);
        HealthComponent* health=(HealthComponent*)mEntityManager->getComponentForEntity(HealthComponentType, entity);
        RenderComponent* render=(RenderComponent*)mEntityManager->getComponentForEntity(RenderComponentType, entity);
        
        if(!health||!render) return;
        
        CCSprite* node=render->getNode();
        
        int sX = node->getPositionX() - node->getContentSize().width/2;
        int eX = node->getPositionX()  + node->getContentSize().width/2;
        int actualY = node->getPositionY() + node->getContentSize().height/2;
        
        static int maxColor = 200;
        static int colorBuffer = 55;
        float percentage = ((float) health->getCurHP()) / ((float) health->getMaxHP());
        int actualX = ((eX-sX) * percentage) + sX;
        int amtRed = ((1.0f-percentage)*maxColor)+colorBuffer;
        int amtGreen = (percentage*maxColor)+colorBuffer;
        
        glLineWidth(7);
        ccDrawColor4B(amtRed,amtGreen,0,255);
        ccDrawLine(ccp(sX, actualY), ccp(actualX, actualY));
    }
}
