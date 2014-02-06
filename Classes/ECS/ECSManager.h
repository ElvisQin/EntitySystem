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


#ifndef __ECS__EntityManager__
#define __ECS__EntityManager__

#include "ECSMacros.h"
#include "Entity.h"
#include "System.h"

NS_ECS_BEGIN

/** Manage all entities, and it's components, and System auto-attaching */
class ECSManager
{
public:
    /* There should be spport multiple ECSManager instance in a game */
    ECSManager();
    ~ECSManager();
    
    /* The only way to create an Entity */
    Entity* createEntity();
    void removeEntity(Entity* entity);
    
    //Component
    void addComponentToEntity(Component* component,Entity* entity);
    void removeComponentFromEntity(const std::string& componentId, Entity*);
    Component* getComponentForEntity(const std::string & eId,Entity* entity);
    const std::vector<Entity*>* getAllEntitiesPosessingComponent(const std::string& cId);
    
    //System
    void addSystem(System*);
    void removeSystem(System*);
    
    void update(float dt);
    
private:
    static bool sortSystem(System* s1,System* s2){return s1->getPriority()<s2->getPriority();}
    void componentsChanged(Entity* entity);
    
    entity_id_type generateNewEid();
    
    std::vector<Entity*> _entities;
    std::map<std::string, std::map<Entity*, Component*>*> _componentsByType;
    
    //for quick find entities which own the type of Component.
    std::map<std::string, std::vector<Entity*>*> _componentEntities;
    int _lowestUnassignedEid;
    
    std::map<Entity*, std::vector<System*>*> _entitySystems;
    
    /* This System instance will not to be used at any time(it's always free!)
     * This because C++ does't support reflection, So we can't init a system instance accord to a string, but we need system be auto-attach to an Entity
     * So we store a unused system instance for every System, and clone a new instance from it when needed.
     * This cause more memery but .... :)
     *
     * you must add all System before add any Component to an Entity. you need add System dynamically ?
     */
    std::map<std::string, System*> __unuseSystems;
};

NS_ECS_END

#endif /* defined(__ECS__EntityManager__) */
