//
//  EntityManager.h
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#ifndef __ESDemo__EntityManager__
#define __ESDemo__EntityManager__

#include "Entity.h"
#include "Component.h"
#include "cocos2d.h"

/** Manage all entity ids, and it's components */
class EntityManager:public Object
{
public:
    EntityManager();
    ~EntityManager();
    
    entity_id_type generateNewEid();
    Entity* createEntity();
    void removeEntity(Entity* entity);
    
    void addComponentToEntity(ECSComponent* component,Entity* entity);

    /** an entity only can own one instane of some kind of component */
    ECSComponent* getComponentForEntity(const std::string & eId,Entity* entity);
    
    /** get all entities which contain some kind of component. */
    const std::vector<Entity*>* getAllEntitiesPosessingComponent(const std::string& cId);
    
private:
    std::vector<Entity*> _entities;
    std::map<std::string, std::map<Entity*, ECSComponent*>*> _componentsByType;
    
    //for quick find entities every frame.
    std::map<std::string, std::vector<Entity*>*> _componentEntities;
    int _lowestUnassignedEid;
};

#endif /* defined(__ESDemo__EntityManager__) */
