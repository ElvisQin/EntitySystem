//
//  GameOverComponent.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__GameOverComponent__
#define __HelloCpp__GameOverComponent__

#include <iostream>
#include "Component.h"

/** 游戏结束的条件等相关数据 */
class GameOverComponent:public ECSComponent
{
public:
    //关卡总时间(这里假设获胜条件是totalTime时间内活着)
    float totalTime;
    float currentTime;
    Label* labelTime;
    
public:
    static const char* GAMEOVER_TYPE;
    static GameOverComponent* create(float,Label*);
    
protected:
    GameOverComponent(float,Label*);
};

#endif /* defined(__HelloCpp__GameOverComponent__) */
