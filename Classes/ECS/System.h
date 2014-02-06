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


#ifndef __ECS__System__
#define __ECS__System__

#include "Component.h"
#include <future>

NS_ECS_BEGIN

class ECSManager;
class Entity;

class System
{
protected:
    System();
    virtual ~System(){};
    
    /* IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     *
     * For performance,every Entity have it's own System if it needed.
     * So, just return new MySystem(),don't copy any data,Or the data must be apply all entities.
     */
    virtual System* clone() const = 0;
    
    /* Be allocateed,this method only be called once for every System
     */
    virtual void onInit(){};
    
    /* Be called every frame if it be attached to an Entity
     */
    virtual void update(float dt){}
    
    /* Be attached to an Entity */
    virtual void onAttached(){}
    virtual void onDeattached(){}
    
    /* when any component be added or removed */
    virtual void onComponentsChanged(){}
    
    virtual void startCoroutine();
    
    /* It decide this system will or not be attached to an Entity  */
    virtual std::string& handleType()=0;
    virtual int getPriority(){return 0;}
    
    /* you can find any entity,it's components, etc */
    ECSManager* _entityManager=nullptr;
    Entity* _ownEntity=nullptr;
    
private:
    bool _isFree=true;
    
    friend ECSManager;
};

NS_ECS_END

#endif /* defined(__ECS__System__) */
