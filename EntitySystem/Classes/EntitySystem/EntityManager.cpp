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
    mEntities=CCArray::create();
    mEntities->retain();
    mComponentsByType=CCDictionary::create();
    mComponentsByType->retain();
}

EntityManager::~EntityManager()
{
    CC_SAFE_RELEASE(mEntities);
    CC_SAFE_RELEASE(mComponentsByType);
}

Entity* EntityManager::createEntity(const std::string & entityId)
{
    mEntities->addObject(new CCString(entityId));
    return new Entity(entityId);
}

void EntityManager::addComponentToEntity(Component* component,Entity* entity)
{
    if(!component||!entity)
    {
        return;
    }
    
    //每个类型的Component单独存放一个字典
    CCDictionary* components=(CCDictionary*)mComponentsByType->objectForKey(component->getComponentType());
    if(!components)
    {
        components=CCDictionary::create();
        mComponentsByType->setObject(components, component->getComponentType());
    }
    
    //同一Component在Entity中只能有一个实例
    components->setObject(component, entity->getEntityId());
}

Component* EntityManager::getComponentForEntity(const std::string& cId,Entity* entity)
{
    CCDictionary* dicEntities=(CCDictionary*)mComponentsByType->objectForKey(cId);
    if(dicEntities)
    {
        std::string key=entity->getEntityId();
        CCObject* value=dicEntities->objectForKey(key);
        
        return (Component*)value;
    }
    
    return NULL;
}

void EntityManager::removeEntity(const std::string & eid)
{
    CCArray* keys=mComponentsByType->allKeys();
    if(!keys)
    {
        return;
    }
    
    for (int i=0; i<keys->count(); i++)
    {
        CCDictionary* dict=(CCDictionary*)mComponentsByType->objectForKey(((CCString*)keys->objectAtIndex(i))->getCString());
        if(dict&&dict->objectForKey(eid))
        {
            dict->removeObjectForKey(eid);
        }
    }
    
    mEntities->removeObject(new CCString(eid));
}

CCArray* EntityManager::getAllEntitiesPosessingComponent(const std::string& cId)
{
    CCDictionary* components=(CCDictionary*)mComponentsByType->objectForKey(cId);
    if(components)
    {
        //所有Entity的e_id_type
        CCArray* keys=components->allKeys();
        CCArray* retval=CCArray::createWithCapacity(keys->count());
        for (int i=0; i<keys->count(); i++)
        {
            CCString* key=(CCString*)keys->objectAtIndex(i);
            retval->addObject(new Entity(std::string(key->getCString())));
        }
        
        return retval;
    }
    
    return NULL;
}