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
    mEntityManager =new EntityManager();
    mHealthSystem=new HealthSystem();
    //mRenderSystem=new RenderComponent();
    mHealthSystem->initWithEntityManager(mEntityManager);
    
    
    // ship
    CCSprite* shipSprite =CCSprite::create("Ghost/ship.png");
    shipSprite->setPosition(ccp(winSize.width/2, winSize.height/2+200));
    addChild(shipSprite);
    
    mShip = mEntityManager->createEntity(std::string("ship"));
    mEntityManager->addComponentToEntity(new RenderComponent(shipSprite), mShip);
    mEntityManager->addComponentToEntity(new HealthComponent(200,200),mShip);
    
    
    // unit
    CCSprite* unitSprite = CCSprite::create("Ghost/unit3.png");
    unitSprite->setPosition(ccp(0, 0));
    shipSprite->addChild(unitSprite);
    
    Entity* unit = mEntityManager->createEntity(std::string("unit3"));
    mEntityManager->addComponentToEntity(new RenderComponent(unitSprite), unit);
    mEntityManager->addComponentToEntity(new HealthComponent(200,200),unit);

    unitSprite =CCSprite::create("Ghost/unit4.png");
    unitSprite->setPosition(ccp(50, -50));
    shipSprite->addChild(unitSprite);
    
    unit = mEntityManager->createEntity(std::string("Ghost/unit4"));
    mEntityManager->addComponentToEntity(new RenderComponent(unitSprite), unit);
    mEntityManager->addComponentToEntity(new HealthComponent(200,200),unit);
}


void HelloWorld::update(float delta)
{
    //mRenderSystem->update(delta);
    mHealthSystem->update(delta);
}

void HelloWorld::draw()
{
    mHealthSystem->draw();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
