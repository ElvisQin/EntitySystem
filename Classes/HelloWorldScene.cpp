#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    Size size=CCDirector::getInstance()->getVisibleSize();
    LayerColor* colorLayer=LayerColor::create(Color4B(0,0,255,255),size.width,size.height);
    addChild(colorLayer,-1);
    
    addGhosts();
    
    scheduleUpdate();
    
    return true;
}

void HelloWorld::addGhosts()
{
    Size winSize = Director::getInstance()->getWinSize();
    _entityManager =new EntityManager();
    _healthSystem=new HealthSystem();
    _healthSystem->initWithManager(_entityManager);
    _moveSystem=new MoveSystem();
    _moveSystem->initWithManager(_entityManager);
    
    // ship
    Sprite* shipSprite =Sprite::create("Ghost/ship.png");
    shipSprite->setPosition(Point(winSize.width/2, winSize.height/2+200));
    addChild(shipSprite);
    
    Entity* ship = _entityManager->createEntity();
    _entityManager->addComponentToEntity(new RenderComponent(shipSprite), ship);
    _entityManager->addComponentToEntity(new HealthComponent(200,200),ship);
    
    // unit
    Sprite* unitSprite = Sprite::create("Ghost/unit3.png");
    unitSprite->setPosition(Point(0, 0));
    shipSprite->addChild(unitSprite);
    
    Entity* unit = _entityManager->createEntity();
    _entityManager->addComponentToEntity(new RenderComponent(unitSprite), unit);
    _entityManager->addComponentToEntity(new HealthComponent(200,200),unit);
    
    unitSprite =Sprite::create("Ghost/unit4.png");
    unitSprite->setPosition(Point(50, -50));
    shipSprite->addChild(unitSprite);
    
    unit = _entityManager->createEntity();
    _entityManager->addComponentToEntity(new RenderComponent(unitSprite), unit);
    _entityManager->addComponentToEntity(new HealthComponent(200,200),unit);
    _entityManager->addComponentToEntity((new MoveComponent())->initWithMoveTarget(Point(200,200), 100, 100), unit);
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


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
