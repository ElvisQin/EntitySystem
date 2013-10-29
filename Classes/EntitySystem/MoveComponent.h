//
//  MoveComponent.h
//  EntitySystem
//
//  Created by Elvis on 9/13/13.
//
//

#ifndef __EntitySystem__MoveComponent__
#define __EntitySystem__MoveComponent__

#include "Component.h"

/** 移动一个元素至指定位置 */
class MoveComponent:public ECSComponent
{
public:
    static const char* MOVE_TYPE;
    
    static MoveComponent* cretae(Point moveTarget,float acceleration=1);
    
    Point moveTarget;
    float acceleration;
    
private:
    MoveComponent(Point moveTarget,float acceleration);
};

#endif /* defined(__EntitySystem__MoveComponent__) */
