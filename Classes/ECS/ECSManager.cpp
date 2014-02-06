/****************************************************************************
 Copyright (c) 2013-2014 Elvis Qin
 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "ECSManager.h"
#include <typeinfo>

USING_NS_ECS;

ECSManager::ECSManager()
{
    _entities.reserve(50);
    _lowestUnassignedEid=1;
}

ECSManager::~ECSManager()
{
    //clear data
}

entity_id_type ECSManager::generateNewEid()
{
    if (_lowestUnassignedEid < UINT32_MAX)
    {
        return _lowestUnassignedEid++;
    }
    else
    {
        for (entity_id_type i = 1; i < UINT32_MAX; ++i)
        {
            Entity* entity=Entity::createWithId(i);
            if (std::find(_entities.begin(), _entities.end(),entity)==_entities.end())
            {
                //not contain i,means i been deleted.
                delete entity;
                return i;
            }
            delete entity;
        }
    }
    
    return 0;
}

Entity* ECSManager::createEntity()
{
    entity_id_type id=generateNewEid();
    Entity* entity=Entity::createWithId(id);
    _entities.push_back(entity);
    return entity;
}

void ECSManager::addComponentToEntity(Component* component,Entity* entity)
{
    if(component==nullptr||entity==nullptr){
        return;
    }
    
    // 1. store relationship of Entity and Component
    std::map<Entity*, Component*>* entityList = nullptr;
    auto components=_componentsByType.find(component->getType());
    if (components==_componentsByType.end()){
        entityList =new std::map<Entity*, Component*>();
        _componentsByType.insert(std::make_pair(component->getType(), entityList));
    }
    else {
        entityList=components->second;
    }
    
    //an entity only can own one instane of some kind of component.
    if (entityList->find(entity)!=entityList->end()) {
        return;
    }
    entityList->insert(std::make_pair(entity, component));
    
    
    
    // 2. for fast find Entities own some Component
    std::vector<Entity*>* componentEntities;
    auto entities=_componentEntities.find(component->getType());
    if (entities==_componentEntities.end()) {
        componentEntities=new std::vector<Entity*>();
        _componentEntities.insert(std::make_pair(component->getType(), componentEntities));
    }
    else {
        componentEntities=entities->second;
    }
    componentEntities->insert(componentEntities->begin(), entity);
    
    
    
    //3. auto-attach System
    std::vector<System*>* entitySystems;
    auto systems=_entitySystems.find(entity);
    if (systems==_entitySystems.end()) {
        entitySystems=new std::vector<System*>();
        _entitySystems.insert(std::make_pair(entity, entitySystems));
    }
    else {
        entitySystems=systems->second;
    }
    
    for (auto iter=__unuseSystems.begin(); iter!=__unuseSystems.end(); iter++) {
        if (iter->second->handleType()==component->getType()) {
            entitySystems->insert(entitySystems->begin(),iter->second->clone());
            iter->second->_isFree=false;
            iter->second->_ownEntity=entity;
            iter->second->onAttached();
        }
    }
    
    std::sort(entitySystems->begin(), entitySystems->end(),sortSystem);
    
    componentsChanged(entity);
}

void ECSManager::componentsChanged(Entity* entity)
{
    auto systems=_entitySystems.find(entity);
    if (systems!=_entitySystems.end()) {
        for (auto iter=systems->second->begin(); iter!=systems->second->end(); iter++) {
            (*iter)->onComponentsChanged();
        }
    }
}

void ECSManager::removeComponentFromEntity(const std::string& componentId,Entity* entity)
{
    if (componentId.empty()||entity==nullptr) {
        return;
    }
    
    //remove from _componentEntities
    auto entities=_componentEntities.find(componentId);
    if (entities!=_componentEntities.end()){
        for (auto iter=entities->second->begin(); iter!=entities->second->end();) {
            if((*iter)==entity) {
                entities->second->erase(std::find(entities->second->begin(), entities->second->end(), entity));
                break;
            }
            else {
                iter++;
            }
        }
    }
    
    //delete all related systems
    //std::map<Entity*, std::vector<System*>*> _entitySystems;
    auto systems=_entitySystems.find(entity);
    if (systems!=_entitySystems.end()) {
        for (auto iter=systems->second->begin(); iter!=systems->second->end();) {
            if ((*iter)->handleType()==componentId) {
                (*iter)->onDeattached();
                (*iter)->_isFree=true;
                (*iter)->_ownEntity=nullptr;
                delete *iter;
                systems->second->erase(iter);
            }
            
            iter++;
        }
    }
    
    
    //delete the component
    auto components=_componentsByType.find(componentId);
    if (components!=_componentsByType.end()) {
        for (auto iter=components->second->begin(); iter!=components->second->end();iter++) {
            if (iter->first==entity) {
                //delete component of entity
                delete iter->second;
                components->second->erase(entity);
                break;
            }
        }
    }
    
    componentsChanged(entity);
}

Component* ECSManager::getComponentForEntity(const std::string& cId,Entity* entity)
{
    if (cId.empty()||entity==nullptr) {
        return nullptr;
    }
    
    auto components=_componentsByType.find(cId);
    if (components!=_componentsByType.end()) {
        std::map<Entity*, Component*>* entityDic =components->second;
        auto entities=entityDic->find(entity);
        if (entities!=entityDic->end()) {
            return entities->second;
        }
    }
    
    return nullptr;
}

void ECSManager::removeEntity(Entity* entity)
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
    
    //delete all systems attached to the entity
    //std::map<Entity*, std::vector<System*>*> _entitySystems;
    auto systems=_entitySystems.find(entity);
    if (systems!=_entitySystems.end()) {
        for (auto iter=systems->second->begin(); iter!=systems->second->end(); iter++) {
            delete *iter;
        }
    }
    _entitySystems.erase(entity);
    
    //remove from _entities
    _entities.erase(std::find(_entities.begin(), _entities.end(), entity));
    delete entity;
}

const std::vector<Entity*>* ECSManager::getAllEntitiesPosessingComponent(const std::string& cId)
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

void ECSManager::addSystem(System* system)
{
    std::string name = typeid(system).name();
    if (__unuseSystems.find(name)==__unuseSystems.end()) {
        __unuseSystems.insert(std::make_pair(name, system));
    }
}

void ECSManager::removeSystem(System* system)
{
    std::string name = typeid(system).name();
    if (__unuseSystems.find(name)==__unuseSystems.end()) {
        __unuseSystems.erase(name);
    }
}

void ECSManager::update(float dt)
{
    for (auto iter=_entitySystems.begin(); iter!=_entitySystems.end(); iter++) {
        for (auto iter1=iter->second->begin(); iter1!=iter->second->end(); iter1++) {
            if (!(*iter1)->_isFree) {
                (*iter1)->update(dt);
            }
        }
    }
}
