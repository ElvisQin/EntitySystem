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
    _entities.reserve(50);
    _lowestUnassignedEid=1;
}

EntityManager::~EntityManager()
{
    //clear data
}

entity_id_type EntityManager::generateNewEid()
{
    if (_lowestUnassignedEid < UINT32_MAX) {
        return _lowestUnassignedEid++;
    }
    else {
        for (entity_id_type i = 1; i < UINT32_MAX; ++i){
            Entity* entity=Entity::createWithId(i);
            if (std::find(_entities.begin(), _entities.end(),entity)==_entities.end()) {
                //not contain i,means i been deleted.
                delete entity;
                return i;
            }
            delete entity;
        }
    }

    return 0;
}

Entity* EntityManager::createEntity()
{
    entity_id_type id=generateNewEid();
    Entity* entity=Entity::createWithId(id);
    _entities.push_back(entity);
    return entity;
}

void EntityManager::addComponentToEntity(ECSComponent* component,Entity* entity)
{
    if(component==nullptr||entity==nullptr){
        return;
    }
    
    std::map<Entity*, ECSComponent*>* entityList = nullptr;
    auto components=_componentsByType.find(component->getType());
    if (components==_componentsByType.end()) {
        entityList =new std::map<Entity*, ECSComponent*>();
        _componentsByType.insert(std::make_pair(component->getType(), entityList));
    }
    else {
        entityList=components->second;
    }
    //an entity only can own one instane of some kind of component.
    entityList->insert(std::make_pair(entity, component));
    

    std::vector<Entity*>* componentEntities;
    auto entities=_componentEntities.find(component->getType());
    if (entities==_componentEntities.end()) {
        componentEntities=new std::vector<Entity*>();
        _componentEntities.insert(std::make_pair(component->getType(), componentEntities));
    }
    else{
        componentEntities=entities->second;
    }
    
    componentEntities->insert(componentEntities->begin(), entity);
}

ECSComponent* EntityManager::getComponentForEntity(const std::string& cId,Entity* entity)
{
    if (cId.empty()||entity==nullptr) {
        return nullptr;
    }
    
    auto components=_componentsByType.find(cId);
    if (components!=_componentsByType.end()) {
        std::map<Entity*, ECSComponent*>* entityDic =components->second;
        auto entities=entityDic->find(entity);
        if (entities!=entityDic->end()) {
            return entities->second;
        }
    }
    
    return nullptr;
}

void EntityManager::removeEntity(Entity* entity)
{
    if (entity==nullptr) {
        return;
    }
    
    //delete all components
    for (auto iter=_componentsByType.begin(); iter!=_componentsByType.end();++iter) {
        for (auto itemIter=iter->second->begin(); itemIter!=iter->second->end();++itemIter) {
            if (itemIter->first==entity) {
                //delete component of entity
                delete itemIter->second;
                iter->second->erase(entity);
                break;
            }
        }
    }
    
    //remove from _componentEntities
    for (auto iter=_componentEntities.begin(); iter!=_componentEntities.end(); ++iter) {
        for (auto itemIter=iter->second->begin(); itemIter!=iter->second->end(); ++itemIter) {
            if((*itemIter)==entity) {
                iter->second->erase(std::find(iter->second->begin(), iter->second->end(), entity));
                break;
            }
        }
    }
    
    //remove from _entities
    _entities.erase(std::find(_entities.begin(), _entities.end(), entity));
    delete entity;
}

const std::vector<Entity*>* EntityManager::getAllEntitiesPosessingComponent(const std::string& cId)
{
    if (cId.empty()) {
        return nullptr;
    }
    
    auto entities=_componentEntities.find(cId);
    if (entities!=_componentEntities.end()&&entities->second->size()>0) {
        return entities->second;
    }
    
    return nullptr;
}