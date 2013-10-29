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
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "ShipComponent.h"
#include "GhostComponent.h"
#include "HitSystem.h"
#include "HitComponent.h"
#include "DeadEvent.h"
#include "GameOverSystem.h"
#include "GameOverComponent.h"
#include "GunEvent.h"
#include "GunSystem.h"
#include "GunComponent.h"
#include "BulletComponent.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    virtual bool onTouchBegin(Touch*,Event*);
    virtual void onTouchEnded(Touch*,Event*);
    
    CREATE_FUNC(HelloWorld);
private:
    void initEntitySystem();
    void addShip();
    void addGhost(const Point&);
    void addbullet(EventCustom*);
    void addHelp(const Point&);
    virtual void update(float delta);
    virtual void draw();
    
    void gameOver(EventCustom*);
    
private:
    EntityManager* _entityManager;
    HealthSystem* _healthSystem;
    RenderSystem* _renderSystem;
    MoveSystem* _moveSystem;
    CollisionSystem* _collisionSystem;
    HitSystem* _hitSystem;
    GameOverSystem* _gameOverSystem;
    GunSystem* _gunSystem;
    
    Sprite* _ship;
};

#endif // __HELLOWORLD_SCENE_H__
