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
 * Every component has a "type",and it's just data,should not contain any logic.
 */
class ECSComponent:public Object
{
protected:
    ECSComponent(const std::string& type);
    
public:
    inline const std::string& getType() const{return _type;}
    
private:
    std::string _type;
};

#endif /* defined(__ESDemo__Component__) */
