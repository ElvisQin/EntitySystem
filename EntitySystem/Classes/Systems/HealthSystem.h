//
//  HealthSystem.h
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#ifndef __ESDemo__HealthSystem__
#define __ESDemo__HealthSystem__

#include "System.h"

class HealthSystem:public System
{
public:
    void draw();
    virtual void update(float dt);
    
private:
    void fadeCompleted(cocos2d::CCNode* sender);
};

#endif /* defined(__ESDemo__HealthSystem__) */
