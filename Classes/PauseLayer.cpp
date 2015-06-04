//
//  PauseLayer.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/4.
//
//

#include "PauseLayer.h"
#include "AppDelegate.h"
#include "GameScene.h"

PauseLayer::PauseLayer()
{
    
}

bool PauseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    LayerColor *bgLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(bgLayer,1);
    
    needEatTouch = false;
    //遮挡底下层的按钮点击事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    Sprite *s = Sprite::createWithSpriteFrameName("pauseUI.png");
    addChild(s,2);
    s->setPosition(size.width/2, size.height/2);
    
    Sprite *sprite = Sprite::createWithSpriteFrameName("resumeButton.png");
    Sprite *sprite1 = Sprite::createWithSpriteFrameName("resumeButton.png");
    sprite1->setScale(1.1);
    Size spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *resumeItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(PauseLayer::resumeCallback, this));
    resumeItem->setPosition(s->getContentSize().width/2,s->getContentSize().height/2+200*scaleFactory);
    
    sprite = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *restartItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(PauseLayer::restartCallback, this));
    restartItem->setPosition(s->getContentSize().width/2,s->getContentSize().height/2-50*scaleFactory);
    
    sprite = Sprite::createWithSpriteFrameName("mainButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("mainButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *mainItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(PauseLayer::mainCallback, this));
    mainItem->setPosition(s->getContentSize().width/2,s->getContentSize().height/2-250*scaleFactory);
    
    Menu *menu = Menu::create(resumeItem,restartItem,mainItem,NULL);
    menu->setPosition(0,0);
    //menu->alignItemsVerticallyWithPadding(10);
    s->addChild(menu, 1);
    return true;
}

void PauseLayer::show()
{
    this->setVisible(true);
    needEatTouch = true;
}

void PauseLayer::hide()
{
    this->setVisible(false);
    needEatTouch = false;
}

bool PauseLayer::onTouchBegan(Touch* touch, Event* event)
{
    return needEatTouch;
}

void PauseLayer::showResultWithAnimation()
{
    
}

void PauseLayer::mainCallback(Ref* sender)
{
    
}


void PauseLayer::resumeCallback(Ref* sender){
    this->hide();
    
    EventCustom event("PauseLayerResume");
    event.setUserData(this);
    _eventDispatcher->dispatchEvent(&event);
}

void PauseLayer::restartCallback(Ref* sender)
{
    //    gameScene->restartGame();
    //
    //    enegyProgressBar->setPercentage(0);
    
    Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createSceneWithLevel(0)));
}
