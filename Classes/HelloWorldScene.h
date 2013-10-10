#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "EntityManager.h"
#include "HealthSystem.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "MoveSystem.h"
#include "MoveComponent.h"


class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    void addGhosts();
    virtual void update(float delta);
    virtual void draw();
    
private:
    EntityManager* _entityManager;
    HealthSystem* _healthSystem;
    RenderComponent* _renderSystem;
    MoveSystem* _moveSystem;

};

#endif // __HELLOWORLD_SCENE_H__
