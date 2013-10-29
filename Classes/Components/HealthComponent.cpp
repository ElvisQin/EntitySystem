//
//  HealthComponent.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "HealthComponent.h"

const char* HealthComponent::HEALTH_TYPE="HealthComponent";

HealthComponent* HealthComponent::create(float curHP,float maxHP,bool needBar)
{
    HealthComponent* com=new HealthComponent();
    if(com) {
        com->curHP=curHP;
        com->maxHP=maxHP;
        com->alive=true;
        com->needHPBar=needBar;
        
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return NULL;
}

HealthComponent::HealthComponent()
:ECSComponent(HealthComponent::HEALTH_TYPE)
{
    
}