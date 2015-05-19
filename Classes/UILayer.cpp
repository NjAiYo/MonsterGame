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
#include "FilterSprite.h"

UILayer::UILayer()
:hitCount(0)
,leftTime(0)
,mostHitRecord(0)
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
    
    hitCount = 0;
    mostHitRecord = 0;
    leftTime = 0;
    
    comboLayer = Layer::create();
    addChild(comboLayer);
    
    
    comboLabel = Label::createWithBMFont("gameSceneComboLabel.fnt", "0");
    comboLayer->addChild(comboLabel);
    comboLabel->setPosition(size.width-400, size.height-270);
    comboLabel->setScale(scaleFactory);
    
    comboBar = Sprite::createWithSpriteFrameName("wallLifeBarFrame.png");
    comboBar->setPosition(size.width-400,size.height-200);
    comboLayer->addChild(comboBar);
    
    comboProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("wallLifeBar.png"));
    comboProgressBar->setType(ProgressTimer::Type::BAR);
    comboProgressBar->setMidpoint(Vec2(0,1));
    comboProgressBar->setBarChangeRate(Vec2(1, 0));
    comboProgressBar->setPercentage(100);
    comboProgressBar->setPosition(comboBar->getContentSize().width/2,comboBar->getContentSize().height/2);
    comboBar->addChild(comboProgressBar);
    
    comboLayer->setPosition(600,0);
    
    hudLayer = Layer::create();
    addChild(hudLayer);
    Sprite *coinSprite = Sprite::createWithSpriteFrameName("coin.png");
    hudLayer->addChild(coinSprite);
    coinSprite->setPosition(130, size.height-195);
    
    coinLabel = Label::createWithBMFont("gameSceneCoinLabel.fnt", "x 0");
    hudLayer->addChild(coinLabel, 1);
    coinLabel->setPosition(150, size.height-195);
    coinLabel->setScale(scaleFactory);
    

    
    Sprite *sprite = FilterSprite::createWithSpriteFrameName("skillBt.png");
    Sprite *sprite1 = FilterSprite::createWithSpriteFrameName("skillBt.png");
    
    //灰色滤镜
    GLfloat  filterMat[16]= {
        0.3f,  0.3f,  0.3f,  0.0f,
        0.59f, 0.59f, 0.59f, 0.59f,
        0.11f, 0.11f, 0.11f, 0.0f,
        0.0f,  0.0f,  0.0f,  1.0f,
    };
    //FilterSprite *s = dynamic_cast<FilterSprite*>(sprite);
    dynamic_cast<FilterSprite*>(sprite)->setFilterMat(filterMat);
    dynamic_cast<FilterSprite*>(sprite1)->setFilterMat(filterMat);
    
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
    
    _eventDispatcher->addCustomEventListener("MonsterHitted", CC_CALLBACK_1(UILayer::monsterHittedHandler,this));
    _eventDispatcher->addCustomEventListener("MonsterShanbi", CC_CALLBACK_1(UILayer::monsterShanbiHandler,this));
//    _eventDispatcher->addCustomEventListener("MonsterHitted", [=](EventCustom* event){
//        monsterHittedHandler(event);
//    });
    return true;
}

void UILayer::monsterShanbiHandler(EventCustom* event)
{

}

void UILayer::monsterHittedHandler(EventCustom* event)
{
    log("monster hit");
    if (hitCount == 0 || leftTime > 0) {
        leftTime = COMBO_HIT_DURATION;
        hitCount++;
        mostHitRecord = MAX(mostHitRecord, hitCount);
    }
    if (hitCount == 2) {
        //show combo ui
        showComboUI();
    }else if(hitCount > 1){
        //update combo number
    }
    comboLabel->setString(String::createWithFormat("%d",hitCount)->getCString());
}

void UILayer::hideComboUI()
{
    auto action = EaseExponentialIn::create(MoveBy::create(0.3, Vec2(600,0)));
    comboLayer->runAction(action);
}

void UILayer::showComboUI()
{
    log("showComboUI");
    auto action = EaseExponentialOut::create(MoveBy::create(0.3, Vec2(-600,0)));
    comboLayer->runAction(action);
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
    if (leftTime > 0) {
        leftTime -= dt;
        if (leftTime <= 0) {
            leftTime = 0;
            hitCount = 0;
            if (comboLayer->getPositionX() <= 0) {
                hideComboUI();
            }
        }
        comboProgressBar->setPercentage((leftTime/COMBO_HIT_DURATION)*100);
    }
    

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
