//
//  Entity.h
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#ifndef __ESDemo__Entity__
#define __ESDemo__Entity__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

typedef int32_t entity_id_type;

/**
 * an Entity means an ID, nothing else.
 */
class Entity:public Object
{
public:
    static Entity* createWithId(const entity_id_type& id);
    const entity_id_type& getId(){return _id;}
    bool operator==(const Entity& entity){return _id==entity._id;}
private:
    Entity();
    Entity* initWithId(const entity_id_type& id);
private:
    entity_id_type _id;
};

#endif /* defined(__ESDemo__Entity__) */
