//
//  RenderComponent.h
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#ifndef __ESDemo__RenderComponent__
#define __ESDemo__RenderComponent__

#include "cocos2d.h"
#include "Component.h"

USING_NS_CC;

class RenderComponent:public ECSComponent
{
public:
    static const char* RENDER_TYPE;
    
    static RenderComponent* create(Node*);
    
    Node* getNode(){return _node;}
    
private:
    RenderComponent(Node* node);

private:
    Node* _node;
};

#endif /* defined(__ESDemo__RenderComponent__) */
