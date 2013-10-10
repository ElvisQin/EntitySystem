//
//  System.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "System.h"
System::System()
:_entityManager(NULL)
{
    
}

void System::initWithManager(EntityManager* entityManager)
{
    _entityManager=entityManager;
}