#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* colorLayer=CCLayerColor::create(ccc4(0,0,255,255),size.width,size.height);
    addChild(colorLayer,-1);
    
    addGhosts();
    
    scheduleUpdate();
    
    return true;
}

void HelloWorld::addGhosts()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _entityManager =new EntityManager();
    _healthSystem=new HealthSystem();
    _healthSystem->initWithEntityManager(_entityManager);
    _moveSystem=new MoveSystem();
    _moveSystem->initWithEntityManager(_entityManager);
    
    // ship
    CCSprite* shipSprite =CCSprite::create("Ghost/ship.png");
    shipSprite->setPosition(ccp(winSize.width/2, winSize.height/2+200));
    addChild(shipSprite);
    
    Entity* ship = _entityManager->createEntity();
    _entityManager->addComponentToEntity(new RenderComponent(shipSprite), ship);
    _entityManager->addComponentToEntity(new HealthComponent(200,200),ship);
    
    // unit
    CCSprite* unitSprite = CCSprite::create("Ghost/unit3.png");
    unitSprite->setPosition(ccp(0, 0));
    shipSprite->addChild(unitSprite);
    
    Entity* unit = _entityManager->createEntity();
    _entityManager->addComponentToEntity(new RenderComponent(unitSprite), unit);
    _entityManager->addComponentToEntity(new HealthComponent(200,200),unit);

    unitSprite =CCSprite::create("Ghost/unit4.png");
    unitSprite->setPosition(ccp(50, -50));
    shipSprite->addChild(unitSprite);
    
    unit = _entityManager->createEntity();
    _entityManager->addComponentToEntity(new RenderComponent(unitSprite), unit);
    _entityManager->addComponentToEntity(new HealthComponent(200,200),unit);
    _entityManager->addComponentToEntity((new MoveComponent())->initWithMoveTarget(ccp(200,200), 100, 100), unit);
}

void HelloWorld::update(float delta)
{
    _healthSystem->update(delta);
    _moveSystem->update(delta);
}

void HelloWorld::draw()
{
    _healthSystem->draw();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
