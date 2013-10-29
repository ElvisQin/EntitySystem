//
//  System.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "System.h"
ECSSystem::ECSSystem()
:_entityManager(NULL)
{
    
}

void ECSSystem::initWithManager(EntityManager* entityManager)
{
    _entityManager=entityManager;
    
    //configure event
    configure();
}