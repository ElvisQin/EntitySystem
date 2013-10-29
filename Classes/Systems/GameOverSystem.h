//
//  GameOverSystem.h
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#ifndef __HelloCpp__GameOverSystem__
#define __HelloCpp__GameOverSystem__

#include <iostream>
#include "System.h"

class GameOverSystem :public ECSSystem
{
public:
    static GameOverSystem* create(EntityManager*);
    virtual void configure();
    virtual void update(float);
    void gameOver(EventCustom* event);
    
    void showResult(bool);
protected:
    GameOverSystem();
};

#endif /* defined(__HelloCpp__GameOverSystem__) */
