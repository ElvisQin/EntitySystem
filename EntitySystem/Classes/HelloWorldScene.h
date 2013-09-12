#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "EntityManager.h"
#include "HealthSystem.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "HealthComponent.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

private:
    void addGhosts();

virtual void update(float delta);
virtual void draw();

private:
    EntityManager* mEntityManager;
    HealthSystem* mHealthSystem;
RenderComponent* mRenderSystem;
    Entity* mShip;
};

#endif // __HELLOWORLD_SCENE_H__
