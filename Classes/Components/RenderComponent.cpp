//
//  RenderComponent.cpp
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#include "RenderComponent.h"

const char* RenderComponent::RENDER_TYPE="RenderComponent";

RenderComponent* RenderComponent::create(Node* node)
{
    RenderComponent* com=new RenderComponent(node);
    if(com){
        return com;
    }
    
    CC_SAFE_RELEASE(com);
    return NULL;
}

RenderComponent::RenderComponent(Node* node)
:ECSComponent(RenderComponent::RENDER_TYPE)
{
    _node=node;
}
