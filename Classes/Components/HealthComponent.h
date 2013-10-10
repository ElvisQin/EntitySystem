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

static const std::string HealthComponentType=std::string("HealthComponent");

class HealthComponent:public ECSComponent
{
public:
    HealthComponent(float curHP,float maxHP);
    
    virtual const std::string& getComponentType()
        const {return HealthComponentType;};

    float getCurHP(){return mCurHP;}
    float getMaxHP(){return mMaxHP;}
    bool getAlive(){return mAlive;}
    void setAlive(bool alive){mAlive=alive;}

private:
    float mCurHP;
    float mMaxHP;
    bool mAlive;
};


#endif /* defined(__ESDemo__HealthComponent__) */
