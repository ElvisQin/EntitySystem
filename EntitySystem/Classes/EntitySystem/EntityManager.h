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
 * @note 由于不在CCScene中，System不了解其他任何CCNode，所以通过这里来获取任何CCNode
 *       (在Unity3d中，每个GameObject具有全局名称，所以不需要对Entity的数据库)
 */
class EntityManager:public CCObject
{
public:
    EntityManager();
    ~EntityManager();
    
    Entity* createEntity(const std::string & entityId);
    void addComponentToEntity(Component* component,Entity* entity);

    /**
     * 获取某个Entity的某个类型的Component
     * @note 同一类型的Component在一个Entity中只有一个实例
     */
    Component* getComponentForEntity(const std::string & eId,Entity* entity);
    void removeEntity(const std::string & eid);
    
    /**
     * 拥有某个类型Component的所有Entity实例
     */
    CCArray* getAllEntitiesPosessingComponent(const std::string& cId);
    
private:
    CCArray* mEntities;
    CCDictionary* mComponentsByType;    //所有Component组成的字典
};

#endif /* defined(__ESDemo__EntityManager__) */
