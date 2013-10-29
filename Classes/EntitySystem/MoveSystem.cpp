//
//  MoveSystem.cpp
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#include "MoveSystem.h"

MoveSystem* MoveSystem::create(EntityManager* manager)
{
    MoveSystem* sys=new MoveSystem();
    if(sys){
        sys->initWithManager(manager);
        return sys;
    }
    
    CC_SAFE_RELEASE(sys);
    return NULL;
}

void MoveSystem::update(float dt)
{
    const std::vector<Entity*>* entities=_entityManager->getAllEntitiesPosessingComponent(MoveComponent::MOVE_TYPE);
    if(entities==nullptr){
        return;
    }
    
    for (int i=0; i<entities->size(); i++){
        Entity* entity=entities->at(i);
        
        MoveComponent* move=(MoveComponent*)_entityManager->getComponentForEntity(MoveComponent::MOVE_TYPE, entity);
        RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, entity);
        if(render==nullptr){
            continue;
        }
        
        Node* node=render->getNode();
        Point dir=move->moveTarget-node->getPosition();
        node->setPosition(node->getPosition()+dir.normalize()*dt*100*move->acceleration);
        
        if (node->getPosition().getDistance(move->moveTarget)<5) {
            render->getNode()->removeFromParent();
            _entityManager->removeEntity(entity);
        }
    }
}
