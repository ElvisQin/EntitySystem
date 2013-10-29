//
//  RenderSystem.h
//  ESDemo
//
//  Created by Elvis on 9/12/13.
//
//

#ifndef __ESDemo__RenderSystem__
#define __ESDemo__RenderSystem__

#include "System.h"

class RenderSystem:public ECSSystem
{
public:
    static RenderSystem* create(EntityManager*);
};

#endif /* defined(__ESDemo__RenderSystem__) */
