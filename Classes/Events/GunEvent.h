//
//  GunEvent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__GunEvent__
#define __HelloCpp__GunEvent__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

/**
 * emit a bullet, which aim at some type of target, at a certain position.
 */
class GunEvent:public EventCustom
{
public:
    const Point& initPoint;
    const Point& targetPoint;
    const char* targetType;
    
public:
    static const char* GUN_EVENT_TYPE;
    GunEvent(const Point&,const Point&,const char*);
};

#endif /* defined(__HelloCpp__GunEvent__) */
