//
//  System.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "System.h"
System::System()
:mEnabled(true)
,mEntityManager(NULL)
{
    
}

void System::initWithEntityManager(EntityManager *entityManager)
{
    mEntityManager=entityManager;
}