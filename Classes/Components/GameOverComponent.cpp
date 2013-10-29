//
//  GameOverComponent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "GameOverComponent.h"

const char* GameOverComponent::GAMEOVER_TYPE="GameOverComponentType";

GameOverComponent* GameOverComponent::create(float tt,Label* l)
{
    GameOverComponent* com=new GameOverComponent(tt,l);
    if (com) {
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return nullptr;
}

GameOverComponent::GameOverComponent(float tt,Label* l)
:ECSComponent(GameOverComponent::GAMEOVER_TYPE)
,totalTime(tt)
,currentTime(0)
,labelTime(l)
{
    
}