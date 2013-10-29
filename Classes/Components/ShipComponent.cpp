//
//  ShipComponent.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "ShipComponent.h"
const char* ShipComponent::SHIP_TYPE="ShipComponent";

ShipComponent* ShipComponent::create()
{
    ShipComponent* com=new ShipComponent();
    if(com){
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return NULL;
}

ShipComponent::ShipComponent()
:ECSComponent(ShipComponent::SHIP_TYPE)
{
    
}
