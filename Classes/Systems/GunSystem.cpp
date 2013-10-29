//
//  GunSystem.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "GunSystem.h"
#include "GunComponent.h"
#include "RenderComponent.h"
#include "GunEvent.h"

GunSystem* GunSystem::create(EntityManager* em)
{
    GunSystem* sys=new GunSystem();
    if (sys) {
        sys->initWithManager(em);
        return sys;
    }
    
    CC_SAFE_RELEASE(sys);
    return nullptr;
}

void GunSystem::update(float dt)
{
    const std::vector<Entity*>* entities=_entityManager->getAllEntitiesPosessingComponent(GunComponent::GUN_TYPE);
    if(entities==nullptr) return;
    int count=entities->size();

    for (int i=0; i<count; i++){
        Entity* entity=entities->at(i);
        GunComponent* gun=(GunComponent*)_entityManager->getComponentForEntity(GunComponent::GUN_TYPE, entity);
        gun->currentTime+=dt;
        
        //子弹发射间隔
        if (gun->currentTime<gun->durence) continue;
        else gun->currentTime=0;
    
        RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, entity);
        if(!render) continue;
        
        const std::vector<Entity*>* targetEntities=_entityManager->getAllEntitiesPosessingComponent(gun->targetType);
        if (targetEntities==nullptr||targetEntities->size()==0) continue;
        
        Entity* closedEntity;
        float distance=-1;
        RenderComponent* closedRender;
        
        //打随机的
        auto randIndex=rand()%targetEntities->size();

        //for (int j=0; j<targetEntities->count(); j++) {
            Entity* targetEntity=targetEntities->at(randIndex);
            RenderComponent* targetRender=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, targetEntity);
            
            if (!targetRender) {
                continue;
            }
            
            float dis=render->getNode()->getPosition().getDistance(targetRender->getNode()->getPosition());
            if (distance==-1||dis<distance) {
                distance=dis;
                closedEntity=targetEntity;
                closedRender=targetRender;
            }
        //}
        
        GunEvent* event=new GunEvent(render->getNode()->getPosition(),closedRender->getNode()->getPosition(),gun->targetType);
        EventDispatcher::getInstance()->dispatchEvent(event);
    }
}