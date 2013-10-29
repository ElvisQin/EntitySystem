#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init()){
        return false;
    }

    //init ECS
    initEntitySystem();
    
    Size size=CCDirector::getInstance()->getVisibleSize();
    LayerColor* colorLayer=LayerColor::create(Color4B(255,255,255,255),size.width,size.height);
    addChild(colorLayer,-1);
    
    //船
    addShip();
    
    addHelp(Point(_ship->getPositionX()+200,_ship->getPositionY()));
    //addHelp(Point(_ship->getPositionX()-200,_ship->getPositionY()));
    //addHelp(Point(_ship->getPositionX(),_ship->getPositionY()-200));

    
    // 监听鼠标点击
    auto listener=EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegin,this);
    listener->onTouchEnded= CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, -10);
    
    //监听子弹事件
    auto listener1=EventListenerCustom::create(GunEvent::GUN_EVENT_TYPE, CC_CALLBACK_1(HelloWorld::addbullet,this));
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener1, 1);
    
    // 显式倒计时
    Label* lblTime=Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
    lblTime->setColor(Color3B::RED);
    addChild(lblTime);
    lblTime->setPosition(Point(size.width-100,size.height-100));
    
    //游戏结束
    Entity* gameOver=_entityManager->createEntity();
    _entityManager->addComponentToEntity(GameOverComponent::create(100,lblTime), gameOver);
    _entityManager->addComponentToEntity(RenderComponent::create(this), gameOver);
    
    scheduleUpdate();
    
    return true;
}

bool HelloWorld::onTouchBegin(Touch*,Event*)
{
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch,Event*)
{
    addGhost(touch->getLocation());
}

void HelloWorld::initEntitySystem()
{
    _entityManager =new EntityManager();
    _healthSystem=HealthSystem::create(_entityManager);
    _moveSystem=MoveSystem::create(_entityManager);
    _renderSystem=RenderSystem::create(_entityManager);
    _collisionSystem=CollisionSystem::create(_entityManager);
    _hitSystem=HitSystem::create(_entityManager);
    _gameOverSystem=GameOverSystem::create(_entityManager);
    _gunSystem=GunSystem::create(_entityManager);
}

void HelloWorld::addShip()
{
    //1. just id
    Entity* ship = _entityManager->createEntity();
    
    //2. render
    Size size=CCDirector::getInstance()->getVisibleSize();
    _ship =Sprite::create("Ghost/ship.png");
    _ship->setPosition(Point(size.width/2, size.height/2+200));
    addChild(_ship,0,10);
    _entityManager->addComponentToEntity(RenderComponent::create(_ship), ship);
    _entityManager->addComponentToEntity(ShipComponent::create(), ship);
    
    //3. hit
    _entityManager->addComponentToEntity(HealthComponent::create(1000,1000),ship);
    _entityManager->addComponentToEntity(CollisionComponent::create(), ship);
    _entityManager->addComponentToEntity(HitComponent::create(GhostComponent::GHOST_TYPE, 20), ship);
}

void HelloWorld::addGhost(const Point& point)
{
    Node* ship=getChildByTag(10);
    if(ship)
    {
        auto randIndex=rand()%14+1;
        String* str=String::createWithFormat("Ghost/ghost%d.png",randIndex);
        
        // unit;
        Sprite* unitSprite = Sprite::create(str->getCString());
        unitSprite->setPosition(point);
        addChild(unitSprite);
        
        Entity* unit = _entityManager->createEntity();
        _entityManager->addComponentToEntity(RenderComponent::create(unitSprite), unit);
        _entityManager->addComponentToEntity(GhostComponent::create(), unit);
        
        //2. move
        _entityManager->addComponentToEntity(HealthComponent::create(20,20),unit);
        _entityManager->addComponentToEntity(MoveComponent::cretae(ship->getPosition(),1), unit);
        
        //3. hit
        _entityManager->addComponentToEntity(CollisionComponent::create(), unit);
        _entityManager->addComponentToEntity(HitComponent::create(ShipComponent::SHIP_TYPE, 10), unit);
        
        //4. gun
        _entityManager->addComponentToEntity(GunComponent::create(ShipComponent::SHIP_TYPE, 1000, 0.2), unit);
    }
}

void HelloWorld::addbullet(EventCustom* event)
{
    GunEvent* gunEvent=(GunEvent*)event;
    
    auto randIndex=rand()%9+1;
    String* str=String::createWithFormat("Ghost/gun%d.png",randIndex);
    
    // unit;
    Sprite* gunSprite = Sprite::create(str->getCString());
    gunSprite->setPosition(gunEvent->initPoint);
    addChild(gunSprite);
    
    Entity* gun = _entityManager->createEntity();
    _entityManager->addComponentToEntity(RenderComponent::create(gunSprite), gun);                  //UI
    _entityManager->addComponentToEntity(HealthComponent::create(3,3,false),gun);                         //生命值
    _entityManager->addComponentToEntity(MoveComponent::cretae(gunEvent->targetPoint,2), gun);  //可移动
    _entityManager->addComponentToEntity(CollisionComponent::create(), gun);                        //可碰撞
    _entityManager->addComponentToEntity(HitComponent::create(gunEvent->targetType,10), gun);       //碰撞攻击伤害及目标
    _entityManager->addComponentToEntity(BulletComponent::create(), gun);                           //单位类型
}

void HelloWorld::addHelp(const Point& point)
{
    Sprite* girlSprite =Sprite::create("Ghost/fish_girl.png");
    girlSprite->setPosition(point);
    addChild(girlSprite);
    
    Entity* girl = _entityManager->createEntity();
    _entityManager->addComponentToEntity(RenderComponent::create(girlSprite), girl);      //UI
    _entityManager->addComponentToEntity(HealthComponent::create(1000,1000,false),girl);     //生命值
    _entityManager->addComponentToEntity(ShipComponent::create(), girl);             //单位类型标识
    
    //_entityManager->addComponentToEntity(CollisionComponent::create(), girl);        //碰撞监测
    _entityManager->addComponentToEntity(HitComponent::create(GhostComponent::GHOST_TYPE, 20), girl);  //碰撞攻击伤害及攻击目标
    _entityManager->addComponentToEntity(GunComponent::create(GhostComponent::GHOST_TYPE, 1000, 0.3), girl);
}

void HelloWorld::update(float delta)
{
    _moveSystem->update(delta);
    _renderSystem->update(delta);
    _collisionSystem->update(delta);
    _hitSystem->update(delta);
    _healthSystem->update(delta);
    _gameOverSystem->update(delta);
    _gunSystem->update(delta);
}

void HelloWorld::draw()
{
    _healthSystem->draw();
}

void HelloWorld::gameOver(EventCustom* event)
{
    DeadEvent* deadEvent=(DeadEvent*)event;
    if (_entityManager->getComponentForEntity(ShipComponent::SHIP_TYPE, deadEvent->entity)) {
        
    }
}