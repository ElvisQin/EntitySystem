//
//  GameOverSystem.cpp
//  HelloCpp
//
//  Created by Elvis on 10/13/13.
//
//

#include "GameOverSystem.h"
#include "DeadEvent.h"
#include "ShipComponent.h"
#include "GameOverComponent.h"
#include "RenderComponent.h"

GameOverSystem* GameOverSystem::create(EntityManager* em)
{
    GameOverSystem* sys=new GameOverSystem();
    if (sys) {
        sys->initWithManager(em);
        return sys;
    }
    
    CC_SAFE_RELEASE(sys);
    return nullptr;
}

void GameOverSystem::configure()
{
    auto listener=EventListenerCustom::create(DeadEvent::DEAD_EVENT_TYPE, CC_CALLBACK_1(GameOverSystem::gameOver,this));
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 1);
}

void GameOverSystem::update(float dt)
{
    const std::vector<Entity*>* entities=_entityManager->getAllEntitiesPosessingComponent(GameOverComponent::GAMEOVER_TYPE);
    if(entities==nullptr) return;
    
    Entity* entity=entities->at(0);
    GameOverComponent* go=(GameOverComponent*)_entityManager->getComponentForEntity(GameOverComponent::GAMEOVER_TYPE, entity);
    RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, entity);
    if (!go||!render) {
        return;
    }
    go->labelTime->setString(String::createWithFormat("%0.f",go->totalTime-go->currentTime)->getCString());
    go->currentTime+=dt;
    
    if (go->currentTime>=go->totalTime) {//游戏结束
        showResult(true);
    }
}

GameOverSystem::GameOverSystem()
{
    
}

void GameOverSystem::gameOver(EventCustom* event)
{
    DeadEvent* deadEvent=(DeadEvent*)event;
    if (_entityManager->getComponentForEntity(ShipComponent::SHIP_TYPE, deadEvent->entity)) {
        showResult(false);
    }
}

void GameOverSystem::showResult(bool result)
{
    const std::vector<Entity*>* entities= _entityManager->getAllEntitiesPosessingComponent(GameOverComponent::GAMEOVER_TYPE);
    Entity* entity=entities->at(0);
    
    RenderComponent* render=(RenderComponent*)_entityManager->getComponentForEntity(RenderComponent::RENDER_TYPE, entity);
    GameOverComponent* go=(GameOverComponent*)_entityManager->getComponentForEntity(GameOverComponent::GAMEOVER_TYPE, entity);
    
    Label* label;
    if (result)
    {
        label=Label::createWithTTF("You Win", "fonts/Marker Felt.ttf", 100);
    }
    else{
        label=Label::createWithTTF("defeated", "fonts/Marker Felt.ttf", 100);
    }
    label->setAnchorPoint(Point(0.5, 0.5));
    label->setColor(Color3B::GREEN);
    Size size=Director::getInstance()->getWinSize();
    render->getNode()->addChild(label);
    label->setPosition(Point(size.width/2, size.height/2-200));
    
    go->labelTime->removeFromParent();
    _entityManager->removeEntity(entity);
}
