/****************************************************************************
 Copyright (c) 2013-2014 Elvis Qin
 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __ECS__Entity__
#define __ECS__Entity__

#include <iostream>
#include "ECSMacros.h"

NS_ECS_BEGIN

class ECSManager;

typedef int32_t entity_id_type;

/**
 * An Entity means an ID, nothing else.
 */
class Entity
{
public:
    const entity_id_type& getId(){return _id;}

    bool operator==(const Entity& entity){return _id==entity._id;}
    
private:
    static Entity* createWithId(const entity_id_type& id);
    
    Entity();
    Entity* initWithId(const entity_id_type& id);

    entity_id_type _id;
    friend ECSManager;
};

NS_ECS_END

#endif /* defined(__ECS__Entity__) */
