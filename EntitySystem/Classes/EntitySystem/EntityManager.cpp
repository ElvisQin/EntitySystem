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
    int32_t entityId=generateNewEid();
    
    _entities->addObject(CCString::createWithFormat("%d",entityId));
    return new Entity(entityId);
}

void EntityManager::addComponentToEntity(Component* component,Entity* entity)
{
    if(!component||!entity)
    {
        return;
    }
    
    //每个类型的Component单独存放一个字典
    CCDictionary* components=(CCDictionary*)_componentsByType->objectForKey(component->getComponentType());
    if(!components)
    {
        components=CCDictionary::create();
        _componentsByType->setObject(components, component->getComponentType());
    }
    
    //同一Component在Entity中只能有一个实例
    components->setObject(component, entity->getEntityId());
}

Component* EntityManager::getComponentForEntity(const std::string& cId,Entity* entity)
{
    CCDictionary* dicEntities=(CCDictionary*)_componentsByType->objectForKey(cId);
    if(dicEntities)
    {
        int key=entity->getEntityId();
        CCObject* value=dicEntities->objectForKey(key);
        
        return (Component*)value;
    }
    
    return NULL;
}

void EntityManager::removeEntity(Entity* entity)
{
    CCArray* keys=_componentsByType->allKeys();
    if(!keys)
    {
        return;
    }
    
    CCString* key=CCString::createWithFormat("%d",entity->getEntityId());
    for (int i=0; i<keys->count(); i++)
    {
        CCDictionary* dict=(CCDictionary*)_componentsByType->objectForKey(((CCString*)keys->objectAtIndex(i))->getCString());
        if(dict&&dict->objectForKey(key->getCString()))
        {
            dict->removeObjectForKey(key->getCString());
        }
    }
    
    _entities->removeObject(key);
}

CCArray* EntityManager::getAllEntitiesPosessingComponent(const std::string& cId)
{
    CCDictionary* components=(CCDictionary*)_componentsByType->objectForKey(cId);
    if(components)
    {
        //所有Entity的e_id_type
        CCArray* keys=components->allKeys();
        CCArray* retval=CCArray::createWithCapacity(keys->count());
        for (int i=0; i<keys->count(); i++)
        {
            retval->addObject(new Entity(((CCInteger*)keys->objectAtIndex(i))->getValue()));
        }
        
        return retval;
    }
    
    return NULL;
}