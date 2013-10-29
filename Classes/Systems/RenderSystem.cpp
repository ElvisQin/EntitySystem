//
//  RenderSystem.cpp
//  ESDemo
//
//  Created by Elvis on 9/12/13.
//
//

#include "RenderSystem.h"
RenderSystem* RenderSystem::create(EntityManager* manager)
{
    RenderSystem* sys=new RenderSystem();
    if(sys){
        sys->initWithManager(manager);
         return sys;
    }
    
    CC_SAFE_RELEASE(sys);
    return NULL;
}