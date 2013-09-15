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

class System:public cocos2d::CCObject
{
public:
    System();
    void initWithEntityManager(EntityManager* entityManager);
    virtual void update(float dt){};
    
protected:    
    EntityManager* _entityManager;
};

#endif /* defined(__ESDemo__System__) */
