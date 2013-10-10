//
//  EntityManager.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "EntityManager.h"

EntityManager::EntityManager()
{
    _entities=CCArray::create();
    _entities->retain();
    _componentsByType=CCDictionary::create();
    _componentsByType->retain();
    _lowestUnassignedEid=1;
}

EntityManager::~EntityManager()
{
    CC_SAFE_RELEASE(_entities);
    CC_SAFE_RELEASE(_componentsByType);
}

int EntityManager::generateNewEid()
{
    if (_lowestUnassignedEid < UINT32_MAX)
    {
        return _lowestUnassignedEid++;
    }
    else
    {
        for (uint32_t i = 1; i < UINT32_MAX; ++i)
        {
            if (!_entities->containsObject(CCString::createWithFormat("%d",i)))
            {
                return i;
            }
        }

        return 0;
    }
}

Entity* EntityManager::createEntity()
{
    String* id=CCString::createWithFormat("%d",generateNewEid());
    _entities->addObject(id);
    return Entity::createWithId(id->getCString());
}

void EntityManager::addComponentToEntity(ECSComponent* component,Entity* entity)
{
    if(!component||!entity)
    {
        return;
    }
    
    //每个类型的Component单独存放一个字典
    Dictionary* components=(Dictionary*)_componentsByType->objectForKey(component->getComponentType());
    if(!components)
    {
        components=CCDictionary::create();
        _componentsByType->setObject(components, component->getComponentType());
    }
    
    //同一Component在Entity中只能有一个实例
    components->setObject(component, entity->getId());
}

Component* EntityManager::getComponentForEntity(const std::string& cId,Entity* entity)
{
    Dictionary* dicEntities=(Dictionary*)_componentsByType->objectForKey(cId);
    if(dicEntities)
    {
        std::string key=entity->getId();
        Object* value=dicEntities->objectForKey(key);
        
        return (Component*)value;
    }
    
    return NULL;
}

void EntityManager::removeEntity(Entity* entity)
{
    Array* keys=_componentsByType->allKeys();
    if(!keys)
    {
        return;
    }
    
    std::string key=entity->getId();
    for (int i=0; i<keys->count(); i++)
    {
        Dictionary* dict=(Dictionary*)_componentsByType->objectForKey(((String*)keys->objectAtIndex(i))->getCString());
        if(dict&&dict->objectForKey(key))
        {
            dict->removeObjectForKey(key);
        }
    }
    
    _entities->removeObject(CCString::create(key));
}

Array* EntityManager::getAllEntitiesPosessingComponent(const std::string& cId)
{
    Dictionary* components=(Dictionary*)_componentsByType->objectForKey(cId);
    if(components)
    {
        //所有Entity的e_id_type
        Array* keys=components->allKeys();
        Array* retval=CCArray::createWithCapacity(keys->count());
        for (int i=0; i<keys->count(); i++)
        {
            Entity* e=Entity::createWithId(((String*)keys->objectAtIndex(i))->getCString());
            
            retval->addObject(e);
        }
        
        return retval;
    }
    
    return NULL;
}