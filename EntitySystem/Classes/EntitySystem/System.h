//
//  System.h
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#ifndef __ESDemo__System__
#define __ESDemo__System__

#include "cocos2d.h"
#include "EntityManager.h"

USING_NS_CC;

class System:public CCObject
{
public:
    System();
    void initWithEntityManager(EntityManager* entityManager);
    virtual void update(float dt){};
    
protected:    
    EntityManager* mEntityManager;
};

#endif /* defined(__ESDemo__System__) */
