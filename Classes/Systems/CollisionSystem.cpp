//
//  CollisionSystem.cpp
//  HelloCpp
//
//  Created by Elvis on 10/12/13.
//
//

#include "CollisionSystem.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "CollisionEvent.h"
#include "HealthComponent.h"

CollisionSystem* CollisionSystem::create(EntityManager* manager)
{
    CollisionSystem* sys=new CollisionSystem();
    if(sys){
        sys->initWithManager(manager);
        return sys;
    }
    
    CC_SAFE_RELEASE(sys);
    return NULL;
}

void CollisionSystem::update(float dt)
{
    const std::vector<Entity*>* entities=_entityManager->getAllEntitiesPosessingComponent(CollisionComponent::COLLISION_TYPE);
    if(entities==nullptr){
        return;
    }
    
    int count=entities->size();
    
    //记录两个Entity之间是否已执行碰撞检测
    int haveCollision[count][count];
    
    for (int i=0; i<count; i++){
        //碰撞主体
        Entity* entity=entities->at(i);
        RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, entity);
        
        if(!render) continue;
        
        //可能与之发生碰撞的主体
        for (int j=0; j<count; j++) {
            if (haveCollision[j][i]==1||i==j) {
                continue;
            }
            Entity* collisionEntity=entities->at(j);
            RenderComponent* collisionRender=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, collisionEntity);
            
            if(!collisionRender) continue;
            
            //发生碰撞
            if (collide(render->getNode(), collisionRender->getNode())) {
                //标记已处理两个特定Entity
                haveCollision[i][j]=1;
            
                CollisionEvent* event=new CollisionEvent(entity,collisionEntity);
                EventDispatcher::getInstance()->dispatchEvent(event);
            }
        }
    }
}

bool CollisionSystem::collide(Node* node1,Node* node2)
{
    return node1->getBoundingBox().intersectsRect(node2->getBoundingBox());
}