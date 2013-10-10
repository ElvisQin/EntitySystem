//
//  HealthComponent.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "HealthComponent.h"
HealthComponent::HealthComponent(float curHP,float maxHP)
{
    mCurHP=curHP;
    mMaxHP=maxHP;
    mAlive=true;
}