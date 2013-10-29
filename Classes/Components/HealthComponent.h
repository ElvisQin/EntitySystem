//
//  HealthComponent.h
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#ifndef __ESDemo__HealthComponent__
#define __ESDemo__HealthComponent__

#include "cocos2d.h"
#include "Component.h"

class HealthComponent:public ECSComponent
{
public:
    float curHP;
    float maxHP;
    bool alive;
    bool needHPBar;
    
public:
    static const char* HEALTH_TYPE;
    static HealthComponent* create(float curHP,float maxHP,bool needBar=true);

protected:
    HealthComponent();
};


#endif /* defined(__ESDemo__HealthComponent__) */
