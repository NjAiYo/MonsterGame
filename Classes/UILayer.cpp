//
//  UILayer.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "UILayer.h"
#include "AppDelegate.h"
#include "BGTWorld.h"
#include "GameScene.h"
#include "BGTWall.h"

UILayer::UILayer()
{
    
}

bool UILayer::initWithGameScene(GameScene *gs)
{
    if (!Layer::init()) {
        return false;
    }
    gameManager = GameManager::getInstance();
    player = gameManager->getPlayer();
    gameScene = gs;
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    
    
    
    hudLayer = Layer::create();
    addChild(hudLayer);
    Sprite *coinSprite = Sprite::createWithSpriteFrameName("coin.png");
    hudLayer->addChild(coinSprite);
    coinSprite->setPosition(130, size.height-195);
    
    coinLabel = Label::createWithBMFont("gameSceneCoinLabel.fnt", "x 0");
    hudLayer->addChild(coinLabel, 1);
    coinLabel->setPosition(150, size.height-195);
    coinLabel->setScale(scaleFactory);
    

    
    Sprite *sprite = Sprite::createWithSpriteFrameName("skillBt.png");
    Sprite *sprite1 = Sprite::createWithSpriteFrameName("skillBt.png");
    sprite1->setScale(1.1);
    Size spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *skillItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::skillCallback, this));
    skillItem->setPosition(size.width-180*scaleFactory,160*scaleFactory);
    
    Menu *menu = Menu::create(skillItem,NULL);
    menu->setPosition(0,0);
    hudLayer->addChild(menu, 1);
    
    
    scorelabel = Label::createWithBMFont("gameSceneScoreLabel.fnt", "0");
    hudLayer->addChild(scorelabel, 1);
    scorelabel->setPosition(size.width/2, size.height-55);
    
    playerLevelLabel = Label::createWithBMFont("gameSceneLevelLabel.fnt", "1");
    hudLayer->addChild(playerLevelLabel, 1);
    playerLevelLabel->setPosition(112, size.height-80);
    
    backIconPosition = Vec2(300*scaleFactory, 120*scaleFactory);
    
    frontIconPosition = Vec2(180*scaleFactory, 160*scaleFactory);
    
    frontScale = 1.0;
    backScale = 0.8;
    frontTint = Color3B(255, 255, 255);
    backTint = Color3B(125, 125, 125);
    
    gunIcon = Sprite::createWithSpriteFrameName("gunBt.png");
    hudLayer->addChild(gunIcon);
    gunIcon->setPosition(backIconPosition);
    gunIcon->setColor(backTint);
    gunIcon->setScale(backScale);
    
    
    
    knifeIcon = Sprite::createWithSpriteFrameName("knifeBt.png");
    hudLayer->addChild(knifeIcon);
    knifeIcon->setPosition(frontIconPosition);
    knifeIcon->setColor(frontTint);
    knifeIcon->setScale(frontScale);

    enegyBar = Sprite::createWithSpriteFrameName("enegyBarFrame.png");
    enegyBar->setPosition(size.width/2,80);
    hudLayer->addChild(enegyBar);

    
    enegyProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("enegyBar.png"));
    enegyProgressBar->setType(ProgressTimer::Type::BAR);
    enegyProgressBar->setMidpoint(Vec2(0,1));
    enegyProgressBar->setBarChangeRate(Vec2(1, 0));
    enegyProgressBar->setPercentage(0);
    enegyProgressBar->setPosition(enegyBar->getContentSize().width/2,enegyBar->getContentSize().height/2);
    enegyBar->addChild(enegyProgressBar);
    
    
    
    lifeBar = Sprite::createWithSpriteFrameName("wallLifeBarFrame.png");
    lifeBar->setPosition(160,size.height-100);
    hudLayer->addChild(lifeBar);
    
    lifeProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("wallLifeBar.png"));
    lifeProgressBar->setType(ProgressTimer::Type::BAR);
    lifeProgressBar->setMidpoint(Vec2(0,1));
    lifeProgressBar->setBarChangeRate(Vec2(1, 0));
    lifeProgressBar->setPercentage(100);
    lifeProgressBar->setPosition(lifeBar->getContentSize().width/2,lifeBar->getContentSize().height/2);
    lifeBar->addChild(lifeProgressBar);
    
    
    
    sprite = Sprite::createWithSpriteFrameName("pauseBt.png");
    sprite1 = Sprite::createWithSpriteFrameName("pauseBt.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *pauseItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::pauseCallback, this));
    pauseItem->setPosition(size.width-70,size.height-50);
    
    
    
    Menu *pauseMenu = Menu::create(pauseItem,NULL);
    pauseMenu->setPosition(0,0);
    addChild(pauseMenu, 1);

    
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(UILayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(UILayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(UILayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    pausedLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(pausedLayer);
    pausedLayer->setVisible(false);
    sprite = Sprite::createWithSpriteFrameName("resumeButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("resumeButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *resumeItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::resumeCallback, this));
    resumeItem->setPosition(size.width/2,size.height/2);
    
    menu = Menu::create(resumeItem,NULL);
    menu->setPosition(0,0);
    pausedLayer->addChild(menu, 1);
    
    
    
    winLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(winLayer);
    winLayer->setVisible(false);
    Label *label = Label::create("赢了！", "Arial", 150*scaleFactory);
    label->setColor(Color3B(255,255,255));
    winLayer->addChild(label);
    label->setPosition(size.width/2,size.height-200);
    
    sprite = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *restartItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::restartCallback, this));
    
    
    sprite = Sprite::createWithSpriteFrameName("nextLevelButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("nextLevelButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *nextItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::nextLevelCallback, this));
    
    menu = Menu::create(restartItem,nextItem,NULL);
    menu->setPosition(size.width/2,size.height/2);
    menu->alignItemsHorizontallyWithPadding(50);
    winLayer->addChild(menu, 1);

    
    failedLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(failedLayer);
    failedLayer->setVisible(false);
    label = Label::create("输了！", "Arial", 150*scaleFactory);
    label->setColor(Color3B(255,255,255));
    failedLayer->addChild(label);
    label->setPosition(size.width/2,size.height-200);
    
    sprite = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    restartItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::restartCallback, this));
    
    menu = Menu::create(restartItem,NULL);
    menu->setPosition(size.width/2,size.height/2);
    failedLayer->addChild(menu, 1);
    
    return true;
}

void UILayer::hideHUD()
{
    hudLayer->setVisible(false);
}

void UILayer::showHUD()
{
    hudLayer->setVisible(true);
}

void UILayer::gameStart()
{
    coinLabel->setString(String::createWithFormat("%d",player->money)->getCString());
    scorelabel->setString(String::createWithFormat("%d",player->score)->getCString());
    playerLevelLabel->setString(String::createWithFormat("%d",player->level)->getCString());
}

void UILayer::skillCallback(Ref* sender)
{
    gameScene->getWorld()->launchCurrentSkill();
}

void UILayer::resumeCallback(Ref* sender){
    pausedLayer->setVisible(false);
    gameScene->resumeGame();
}

void UILayer::pauseCallback(Ref* sender)
{
    if (gameScene->getState()!=GameStateGaming) {
        return;
    }
    pausedLayer->setVisible(true);
    gameScene->pauseGame();
}

void UILayer::nextLevelCallback(Ref* sender)
{
    gameScene->nextLevel();
}

void UILayer::restartCallback(Ref* sender)
{
//    gameScene->restartGame();
//    
//    enegyProgressBar->setPercentage(0);
    
    Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createSceneWithLevel(0)));
}

void UILayer::gameEnd(bool isWin)
{
    winLayer->setVisible(isWin);
    failedLayer->setVisible(!isWin);
}

void UILayer::update(float dt)
{
    lifeProgressBar->setPercentage(gameScene->getWorld()->getWall()->getLife()/gameScene->getWorld()->getWall()->getTotalLife()*100);
    enegyProgressBar->setPercentage(gameScene->getWorld()->getEnegy());
}

void UILayer::toggleToKnife(){
    knifeIcon->runAction(Spawn::create(MoveTo::create(0.2, frontIconPosition),ScaleTo::create(0.2, frontScale),TintTo::create(0.2, frontTint), NULL));
    gunIcon->runAction(Spawn::create(MoveTo::create(0.2, backIconPosition),ScaleTo::create(0.2, backScale),TintTo::create(0.2, backTint), NULL));
    gameScene->getWorld()->toggleToKnife();
    knifeIcon->setLocalZOrder(10);
    gunIcon->setLocalZOrder(9);
}

void UILayer::toggleToGun(){
    gunIcon->runAction(Spawn::create(MoveTo::create(0.2, frontIconPosition),ScaleTo::create(0.2, frontScale),TintTo::create(0.2, frontTint), NULL));
    knifeIcon->runAction(Spawn::create(MoveTo::create(0.2, backIconPosition),ScaleTo::create(0.2, backScale),TintTo::create(0.2, backTint), NULL));
    gameScene->getWorld()->toggleToGun();
    knifeIcon->setLocalZOrder(9);
    gunIcon->setLocalZOrder(10);
}

bool UILayer::onTouchBegan(Touch* touch, Event* event)
{
    if (gameScene->getState()!=GameStateGaming) {
        return false;
    }
    if (!hudLayer->isVisible()) {
        return false;
    }
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    Vec2 pos = touch->getLocation();
    Rect rect = Rect(knifeIcon->getPositionX()-200*scaleFactory/2, knifeIcon->getPositionY()-200*scaleFactory/2, 200*scaleFactory, 200*scaleFactory);
    if (rect.containsPoint(pos)) {
        if(gameScene->getWorld()->isUseKnife()){
            toggleToGun();
        }else{
            toggleToKnife();
        }
        return true;
    }
    
    return false;
}

void UILayer::onTouchMoved(Touch* touch, Event* event)
{

}

void UILayer::onTouchEnded(Touch* touch, Event* event)
{

}

void UILayer::onTouchCancelled(Touch *touch, Event *unused_event)
{

}
