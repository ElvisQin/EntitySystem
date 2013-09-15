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

/**
 * Entity就是一个Id
 */
class Entity:public cocos2d::CCObject
{
public:
    Entity(int32_t entityId);
    int32_t getEntityId(){return _entityId;}
    
private:
    int32_t _entityId;
};

#endif /* defined(__ESDemo__Entity__) */
