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

class Entity:public cocos2d::CCObject
{
public:
    //Entity就是一个Id
    Entity(const std::string& entityId);
    
    const std::string& getEntityId() const {return mEntityId;}
    
private:
    std::string mEntityId;
};

#endif /* defined(__ESDemo__Entity__) */
