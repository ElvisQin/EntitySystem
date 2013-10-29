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

class HealthSystem:public ECSSystem
{
public:
    static HealthSystem* create(EntityManager*);
    
    void draw();
    virtual void update(float dt);
    
private:
    void fadeCompleted(Node* sender);
};

#endif /* defined(__ESDemo__HealthSystem__) */
