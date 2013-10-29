//
//  GunComponent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__GunComponent__
#define __HelloCpp__GunComponent__

#include <iostream>
#include "Component.h"

/**
 * 此数据可以使一个单位可以发射子弹
 */
class GunComponent:public ECSComponent
{
public:
    /**  射击目标类型*/
    const char* targetType;
    
    /** 射击距离*/
    float distance;
    
    /** 攻击速度*/
    float durence;
    
    float currentTime;
    
public:
    static const char* GUN_TYPE;
    static GunComponent* create(const char* tt,float dis,float d);
    
protected:
    GunComponent(const char* tt,float dis,float d);
};

#endif /* defined(__HelloCpp__GunComponent__) */
