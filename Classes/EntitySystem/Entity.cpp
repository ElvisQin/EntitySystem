//
//  Entity.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "Entity.h"
Entity::Entity()
{
    
}

Entity* Entity::createWithId(const entity_id_type& id)
{
    Entity* entity=new Entity();
    if(entity){
        entity->initWithId(id);
        return entity;
    }
    
    CC_SAFE_RELEASE(entity);
    return NULL;
}

Entity* Entity::initWithId(const entity_id_type& id)
{
    _id=id;
    return this;
}