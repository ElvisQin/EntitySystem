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

static const std::string  RenderComponentType=std::string("RenderComponent");

class RenderComponent:public Component
{
public:
    RenderComponent(CCSprite* node);
    
    virtual const std::string & getComponentType() const {return RenderComponentType;}

    CCSprite* getNode(){return mNode;}
private:
    CCSprite* mNode;
};

#endif /* defined(__ESDemo__RenderComponent__) */
