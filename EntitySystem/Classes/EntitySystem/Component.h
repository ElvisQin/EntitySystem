//
//  Component.h
//  ESDemo
//
//  Created by Elvis on 9/11/13.
//
//

#ifndef __ESDemo__Component__
#define __ESDemo__Component__

#include "cocos2d.h"

USING_NS_CC;

/**
 * Component只包含数据，如CCNode，或者HeroInfo
 * @note Component不应该包含操作这些数据的代码，这是System的职责
 */
class Component:public CCObject
{
public:
    /** 每个Component返回固定类型 */
    virtual const std::string& getComponentType() const=0;
};

#endif /* defined(__ESDemo__Component__) */
