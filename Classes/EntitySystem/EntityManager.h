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

/**
 * Entity的数据库，管理所有Entity
 */
class EntityManager:public Object
{
public:
    EntityManager();
    ~EntityManager();
    
    int generateNewEid();
    Entity* createEntity();
    void addComponentToEntity(ECSComponent* component,Entity* entity);

    /**
     * 获取某个Entity的某个类型的Component
     * @note 同一类型的Component在一个Entity中只有一个实例
     */
    Component* getComponentForEntity(const std::string & eId,Entity* entity);
    void removeEntity(Entity* entity);
    
    /** 拥有某个类型Component的所有Entity实例 */
    Array* getAllEntitiesPosessingComponent(const std::string& cId);
    
private:
    Array* _entities;
    Dictionary* _componentsByType;    //所有Component组成的字典
    int _lowestUnassignedEid;
};

#endif /* defined(__ESDemo__EntityManager__) */
