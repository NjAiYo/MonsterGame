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
#include "Character.h"

//#include "FilterSprite.h"
//#include "Gamepanel.h"

UILayer::UILayer()
:hitCount(0)
,currentLifeValue(100)
,leftTime(0)
,mostHitRecord(0)
,comboLabel(nullptr)
,blursprite(nullptr)
{
    
}

bool UILayer::initWithGameScene(GameScene *gs)
{
    if (!Layer::init()) {
        return false;
    }
//    one.pushBack(GrayFilter::create());
    //one.pushBack(GaussianVBlurFilter::create(10));
    one.pushBack(GaussianHBlurFilter::create(10));
    
    SpriteFrameCache *ccsfc = SpriteFrameCache::getInstance();
    ccsfc->addSpriteFramesWithFile("GameSceneEndLayer.plist");
    
    gameManager = GameManager::getInstance();
    player = gameManager->getPlayer();
    gameScene = gs;
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    hitCount = 0;
    mostHitRecord = 0;
    leftTime = 0;
    
    currentEnegyValue = 0;
    currentLifeValue = 100;
    
    comboLayer = Layer::create();
    addChild(comboLayer);
    
    
    //comboLabel = Label::createWithBMFont("gameSceneComboLabel.fnt", "0");
    comboLabel = Label::createWithCharMap("comboNumber.png", 130, 144, '0');
    comboLabel->setAlignment(TextHAlignment::LEFT);
    comboLayer->addChild(comboLabel);
    comboLabel->setPosition(size.width-400*scaleFactory, size.height-270*scaleFactory);
    comboLabel->setScale(scaleFactory);
    
    comboBar = Sprite::createWithSpriteFrameName("countDownFrameDi.png");
    comboBar->setPosition(size.width-400*scaleFactory,size.height-200*scaleFactory);
    comboLayer->addChild(comboBar);
    
    comboProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("countDownBar.png"));
    comboProgressBar->setType(ProgressTimer::Type::BAR);
    comboProgressBar->setMidpoint(Vec2(0,1));
    comboProgressBar->setBarChangeRate(Vec2(1, 0));
    comboProgressBar->setPercentage(100);
    comboProgressBar->setPosition(comboBar->getContentSize().width/2,comboBar->getContentSize().height/2);
    comboBar->addChild(comboProgressBar);
    
    
    Sprite *s = Sprite::createWithSpriteFrameName("countDownFrame.png");
    s->setPosition(comboBar->getContentSize().width/2,comboBar->getContentSize().height/2);
    comboBar->addChild(s);
    
    comboLayer->setPosition(600*scaleFactory,0);
    
    tipLayer = Layer::create();
    addChild(tipLayer);
    
    hudLayer = Layer::create();
    addChild(hudLayer);
    Sprite *coinSprite = Sprite::createWithSpriteFrameName("coin.png");
    hudLayer->addChild(coinSprite);
    coinSprite->setPosition(245*scaleFactory, size.height-195*scaleFactory);
    
    coinLabel = Label::createWithBMFont("gameSceneCoinLabel.fnt", "x0");
//    s = Sprite::createWithSpriteFrameName("coinX.png");
//    s->setPosition(310*scaleFactory,size.height-195);
//    hudLayer->addChild(s);
    //coinLabel = Label::createWithCharMap("coinNumber.png", 55, 45, '0');
    coinLabel->setAlignment(TextHAlignment::LEFT);
    hudLayer->addChild(coinLabel, 1);
    //coinLabel->setString(":0");
    coinLabel->setPosition(320*scaleFactory, size.height-195*scaleFactory);
    coinLabel->setScaleX(scaleFactory);
    coinLabel->setScaleY(scaleFactory*0.6);

    
    Sprite *sprite = Sprite::createWithSpriteFrameName("skillBt.png");
    Sprite *sprite1 = Sprite::createWithSpriteFrameName("skillBt.png");
    
//    //灰色滤镜
//    GLfloat filterMat[16]= {
//        0.3f,  0.3f,  0.3f,  0.0f,
//        0.59f, 0.59f, 0.59f, 0.59f,
//        0.11f, 0.11f, 0.11f, 0.0f,
//        0.0f,  0.0f,  0.0f,  1.0f,
//    };
//    //FilterSprite *s = dynamic_cast<FilterSprite*>(sprite);
//    dynamic_cast<FilteredSprite*>(sprite)->setFilterMat(filterMat);
//    dynamic_cast<FilteredSprite*>(sprite1)->setFilterMat(filterMat);
    
    sprite1->setScale(1.1);
    Size spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *skillItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::skillCallback, this));
    skillItem->setPosition(size.width-180*scaleFactory,160*scaleFactory);
    
    Menu *menu = Menu::create(skillItem,NULL);
    menu->setPosition(0,0);
    hudLayer->addChild(menu, 1);
    
    
//    scorelabel = Label::createWithBMFont("gameSceneScoreLabel.fnt", "0");
//    hudLayer->addChild(scorelabel, 1);
//    scorelabel->setPosition(size.width/2, size.height-55);
    
    playerLevelLabel = Label::createWithBMFont("gameSceneLevelLabel.fnt", "Lv.1");
    hudLayer->addChild(playerLevelLabel, 1);
    playerLevelLabel->setPosition(120*scaleFactory, size.height-170*scaleFactory);
    playerLevelLabel->setScale(scaleFactory);
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

    enegyBar = Sprite::createWithSpriteFrameName("enegyBarFrameDi.png");
    enegyBar->setPosition(size.width/2,80*scaleFactory);
    hudLayer->addChild(enegyBar);
    

    
    enegyProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("enegyBar.png"));
    enegyProgressBar->setType(ProgressTimer::Type::BAR);
    enegyProgressBar->setMidpoint(Vec2(0,1));
    enegyProgressBar->setBarChangeRate(Vec2(1, 0));
    enegyProgressBar->setPercentage(0);
    enegyProgressBar->setPosition(enegyBar->getContentSize().width/2,enegyBar->getContentSize().height/2);
    enegyBar->addChild(enegyProgressBar);
    
    enegyBarHead = Sprite::createWithSpriteFrameName("enegyBarHead.png");
    enegyBarHead->setPosition(enegyBar->getContentSize().width,enegyBar->getContentSize().height/2);
    enegyBar->addChild(enegyBarHead);
    
    s = Sprite::createWithSpriteFrameName("enegyBarFrame.png");
    s->setPosition(enegyBar->getContentSize().width/2,enegyBar->getContentSize().height/2);
    enegyBar->addChild(s);

    
    
    lifeBar = Sprite::createWithSpriteFrameName("wallLifeBarFrameDi.png");
    lifeBar->setPosition(490*scaleFactory,size.height-100*scaleFactory);
    hudLayer->addChild(lifeBar);
    

    
    lifeProgressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("wallLifeBar.png"));
    lifeProgressBar->setType(ProgressTimer::Type::BAR);
    lifeProgressBar->setMidpoint(Vec2(0,1));
    lifeProgressBar->setBarChangeRate(Vec2(1, 0));
    lifeProgressBar->setPercentage(100);
    lifeProgressBar->setPosition(lifeBar->getContentSize().width/2,lifeBar->getContentSize().height/2);
    lifeBar->addChild(lifeProgressBar);
    
    lifeBarHead = Sprite::createWithSpriteFrameName("wallLifeBarHead.png");
    lifeBarHead->setPosition(lifeBar->getContentSize().width,lifeBar->getContentSize().height/2);
    lifeBar->addChild(lifeBarHead);
    
    s = Sprite::createWithSpriteFrameName("wallLifeBarFrame.png");
    s->setPosition(lifeBar->getContentSize().width/2,lifeBar->getContentSize().height/2);
    lifeBar->addChild(s);
    
    

    
    s = Sprite::createWithSpriteFrameName("lifeIcon.png");
    s->setPosition(124*scaleFactory,size.height-100*scaleFactory);
    hudLayer->addChild(s);
    
    
    sprite = Sprite::createWithSpriteFrameName("pauseBt.png");
    sprite1 = Sprite::createWithSpriteFrameName("pauseBt.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *pauseItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::pauseCallback, this));
    pauseItem->setPosition(size.width-70*scaleFactory,size.height-70*scaleFactory);
    
    
    
    pauseMenu = Menu::create(pauseItem,NULL);
    pauseMenu->setPosition(0,0);
    addChild(pauseMenu, 1);

    
    
    // Register Touch Event
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    
//    listener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan, this);
//    listener->onTouchMoved = CC_CALLBACK_2(UILayer::onTouchMoved, this);
//    listener->onTouchEnded = CC_CALLBACK_2(UILayer::onTouchEnded, this);
//    listener->onTouchCancelled = CC_CALLBACK_2(UILayer::onTouchCancelled, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto listener = EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(UILayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(UILayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(UILayer::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(UILayer::onTouchesCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    pausedLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(pausedLayer);
    pausedLayer->setVisible(false);
    
    s = Sprite::createWithSpriteFrameName("pauseUI.png");
    pausedLayer->addChild(s);
    s->setPosition(size.width/2, size.height/2);
    
    sprite = Sprite::createWithSpriteFrameName("resumeButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("resumeButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *resumeItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::resumeCallback, this));
    resumeItem->setPosition(s->getContentSize().width/2,s->getContentSize().height/2+200*scaleFactory);
    
    sprite = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("restartButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *restartItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::restartCallback, this));
    restartItem->setPosition(s->getContentSize().width/2,s->getContentSize().height/2-50*scaleFactory);
    
    sprite = Sprite::createWithSpriteFrameName("mainButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("mainButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *mainItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(UILayer::mainCallback, this));
    mainItem->setPosition(s->getContentSize().width/2,s->getContentSize().height/2-250*scaleFactory);
    
    menu = Menu::create(resumeItem,restartItem,mainItem,NULL);
    menu->setPosition(0,0);
    //menu->alignItemsVerticallyWithPadding(10);
    s->addChild(menu, 1);
    
    
    
    winLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(winLayer);
    winLayer->setVisible(false);
    winTipBg = Sprite::createWithSpriteFrameName("winTipBg.png");
    winLayer->addChild(winTipBg);
    winTipBg->setPosition(size.width/2,size.height/2);
    
    winTip = Sprite::createWithSpriteFrameName("winTip.png");
    winLayer->addChild(winTip);
    winTip->setPosition(size.width/2,size.height/2);
    

    failedLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(failedLayer);
    failedLayer->setVisible(false);
    
    failedTipBg = Sprite::createWithSpriteFrameName("failedTipBg.png");
    failedLayer->addChild(failedTipBg);
    failedTipBg->setPosition(size.width/2,size.height/2);
    
    failedTip = Sprite::createWithSpriteFrameName("failedTip.png");
    failedLayer->addChild(failedTip);
    failedTip->setPosition(size.width/2,size.height/2);
    
    
    
    rateLayer = new GameEndRateLayer();
    rateLayer->init();
    addChild(rateLayer,2);
    rateLayer->release();
    rateLayer->setVisible(false);
    

    upgredLayer = new GameEndUpgradeLayer();
    upgredLayer->init();
    addChild(upgredLayer,2);
    upgredLayer->release();
    upgredLayer->setVisible(false);
    
    //生成icons
    for(int i = 0; i < 5; i++){
        Sprite *sprite = Sprite::createWithSpriteFrameName("shanbiLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        shanbiIconsPool.pushBack(sprite);
        
        sprite = Sprite::createWithSpriteFrameName("missLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        missIconsPool.pushBack(sprite);
        
        sprite = Sprite::createWithSpriteFrameName("yunLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        yunIconsPool.pushBack(sprite);

        
        sprite = Sprite::createWithSpriteFrameName("daodiLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        daodiIconsPool.pushBack(sprite);
        
        sprite = Sprite::createWithSpriteFrameName("fukongLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        flowIconsPool.pushBack(sprite);
        
        sprite = Sprite::createWithSpriteFrameName("gedangLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        gedangIconsPool.pushBack(sprite);

        
        sprite = Sprite::createWithSpriteFrameName("jituiLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        jiTuiIconsPool.pushBack(sprite);
        
        sprite = Sprite::createWithSpriteFrameName("mianyiLabel.png");
        tipLayer->addChild(sprite);
        sprite->setVisible(false);
        mianyiIconsPool.pushBack(sprite);
        
        Label *label = Label::createWithBMFont("gameSceneKouLifeLabel.fnt", "-0");
        //Label *label = Label::createWithCharMap("monsterNumber.png", 71, 66, '0');
        addChild(label);
        label->setVisible(false);
        damageLabels.pushBack(label);
        
        label = Label::createWithBMFont("gameSceneBaoJiLabel.fnt", "暴击\n  0  ");
        addChild(label);
        label->setVisible(false);
        baoDamageLabels.pushBack(label);
    }
    
    
    _eventDispatcher->addCustomEventListener("MonsterHitted", CC_CALLBACK_1(UILayer::monsterHittedHandler,this));
    _eventDispatcher->addCustomEventListener("MonsterShanbi", CC_CALLBACK_1(UILayer::monsterShanbiHandler,this));
    _eventDispatcher->addCustomEventListener("MonsterParry", CC_CALLBACK_1(UILayer::monsterParryHandler,this));
    _eventDispatcher->addCustomEventListener("MonsterDamaged", CC_CALLBACK_1(UILayer::monsterDamagedHandler,this));
    _eventDispatcher->addCustomEventListener("MonsterBaoDamaged", CC_CALLBACK_1(UILayer::monsterBaoDamagedHandler,this));
    
    
//    _eventDispatcher->addCustomEventListener("MonsterHitted", [=](EventCustom* event){
//        monsterHittedHandler(event);
//    });
    
    ccsfc->removeSpriteFramesFromFile("GameSceneEndLayer.plist");
    return true;
}

Label* UILayer::getDamageLabelFromPool()
{
    for (int i = 0; i < damageLabels.size(); i++) {
        Label *label = damageLabels.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    //Label *label = Label::createWithBMFont("gameSceneKouLifeLabel.fnt", "-0");
    Label *label = Label::createWithCharMap("monsterNumber.png", 130, 144, '0');
    addChild(label);
    label->setVisible(false);
    damageLabels.pushBack(label);
    return label;
}

Label* UILayer::getBaoDamageLabelFromPool()
{
    for (int i = 0; i < baoDamageLabels.size(); i++) {
        Label *label = baoDamageLabels.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Label *label = Label::createWithBMFont("gameSceneBaoJiLabel.fnt", "暴击\n  0  ");
    addChild(label);
    label->setVisible(false);
    baoDamageLabels.pushBack(label);
    return label;
}

Sprite* UILayer::getShanbiIconFromPool()
{
    for (int i = 0; i < shanbiIconsPool.size(); i++) {
        Sprite *label = shanbiIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("shanbiLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    shanbiIconsPool.pushBack(label);
    return label;
}

Sprite* UILayer::getMissIconFromPool()
{
    for (int i = 0; i < missIconsPool.size(); i++) {
        Sprite *label = missIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("missLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    missIconsPool.pushBack(label);
    return label;
}

Sprite* UILayer::getYunIconFromPool()
{
    for (int i = 0; i < yunIconsPool.size(); i++) {
        Sprite *label = yunIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("yunLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    yunIconsPool.pushBack(label);
    return label;
}

Sprite* UILayer::getDaoDiIconFromPool()
{
    for (int i = 0; i < daodiIconsPool.size(); i++) {
        Sprite *label = daodiIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("daodiLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    daodiIconsPool.pushBack(label);
    return label;
}

Sprite* UILayer::getFlowIconFromPool()
{
    for (int i = 0; i < flowIconsPool.size(); i++) {
        Sprite *label = flowIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("fukongLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    flowIconsPool.pushBack(label);
    return label;
}

Sprite* UILayer::getGeDangIconFromPool()
{
    for (int i = 0; i < gedangIconsPool.size(); i++) {
        Sprite *label = gedangIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("gedangLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    gedangIconsPool.pushBack(label);
    return label;
}

Sprite* UILayer::getJiTuiIconFromPool()
{
    for (int i = 0; i < jiTuiIconsPool.size(); i++) {
        Sprite *label = jiTuiIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("jituiLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    jiTuiIconsPool.pushBack(label);
    return label;
}

Sprite* UILayer::getMianyiIconFromPool()
{
    for (int i = 0; i < mianyiIconsPool.size(); i++) {
        Sprite *label = mianyiIconsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *label = Sprite::createWithSpriteFrameName("mianyiLabel.png");
    tipLayer->addChild(label);
    label->setVisible(false);
    mianyiIconsPool.pushBack(label);
    return label;
}

void UILayer::restartCallback(Ref* sender)
{
    //    gameScene->restartGame();
    //
    //    enegyProgressBar->setPercentage(0);
    
    Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createSceneWithLevel(0)));
}

void UILayer::monsterDamagedHandler(EventCustom* event)
{
    CustomerUserData *userData = (CustomerUserData*)event->getUserData();
    Character *monster = (Character*)userData->monster;

    Label *label = getDamageLabelFromPool();
    label->setPosition(monster->getPositionX(), monster->getFloor()+monster->getBoundingBox().size.height/2);
    label->setVisible(true);
    label->setOpacity(255);
    label->setString(String::createWithFormat("%d",(int)userData->damage)->getCString());
    
    CallFunc *func = CallFunc::create([=](){
        label->setVisible(false);
    });
    label->runAction(Sequence::create(Spawn::create(MoveBy::create(1.5, Vec2(0, 400)),FadeOut::create(1.5), NULL),func, NULL));
}

void UILayer::monsterBaoDamagedHandler(EventCustom* event)
{
    CustomerUserData *userData = (CustomerUserData*)event->getUserData();
    Character *monster = (Character*)userData->monster;
    
    Label *label = getBaoDamageLabelFromPool();
    label->setPosition(monster->getPositionX(), monster->getFloor()+monster->getBoundingBox().size.height/2);
    label->setVisible(true);
    label->setOpacity(255);
    label->setString(String::createWithFormat("%d",(int)userData->damage)->getCString());
    
    CallFunc *func = CallFunc::create([=](){
        label->setVisible(false);
    });
    label->runAction(Sequence::create(Spawn::create(MoveBy::create(1.5, Vec2(0, 400)),FadeOut::create(1.5), NULL),func, NULL));
}

void UILayer::monsterParryHandler(EventCustom* event)
{
    Character *monster = (Character*)event->getUserData();
    Sprite *label = getGeDangIconFromPool();
    label->setPosition(monster->getPositionX(), monster->getFloor()+monster->getBoundingBox().size.height/2);
    label->setVisible(true);
    label->setOpacity(255);
    
    CallFunc *func = CallFunc::create([=](){
        label->setVisible(false);
    });
    label->runAction(Sequence::create(Spawn::create(MoveBy::create(1.5, Vec2(0, 400)),FadeOut::create(1.5), NULL),func, NULL));
}

void UILayer::monsterShanbiHandler(EventCustom* event)
{
    Character *monster = (Character*)event->getUserData();
    Sprite *label = getShanbiIconFromPool();
    label->setPosition(monster->getPositionX(), monster->getFloor()+monster->getBoundingBox().size.height/2);
    label->setVisible(true);
    label->setOpacity(255);
    
    CallFunc *func = CallFunc::create([=](){
        label->setVisible(false);
    });
    label->runAction(Sequence::create(Spawn::create(MoveBy::create(1.5, Vec2(0, 400)),FadeOut::create(1.5), NULL),func, NULL));
}

void UILayer::monsterHittedHandler(EventCustom* event)
{
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
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    auto action = EaseExponentialIn::create(MoveBy::create(0.3, Vec2(600*scaleFactory,0)));
    comboLayer->runAction(action);
}

void UILayer::showComboUI()
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    auto action = EaseExponentialOut::create(MoveBy::create(0.3, Vec2(-600*scaleFactory,0)));
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
    coinLabel->setString(String::createWithFormat("x%d",0)->getCString());//player->getMoney()
    //scorelabel->setString(String::createWithFormat("%d",player->score)->getCString());
    playerLevelLabel->setString(String::createWithFormat("Lv.%d",player->level)->getCString());
}

void UILayer::skillCallback(Ref* sender)
{
    gameScene->getWorld()->launchCurrentSkill();
}

void UILayer::resumeCallback(Ref* sender){
    pausedLayer->setVisible(false);
    gameScene->resumeGame();
    pauseMenu->setVisible(true);
    if (blursprite) {
        blursprite->removeFromParentAndCleanup(true);
        blursprite = nullptr;
    }
}

void UILayer::pauseCallback(Ref* sender)
{
    if (gameScene->getState()!=GameStateGaming) {
        return;
    }
    
    Size size = Director::getInstance()->getWinSize();
    RenderTexture *tex = RenderTexture::create(int(size.width), int(size.height));
    tex->setPosition(Point(size.width/2, size.height/2));
    tex->begin();
    gameScene->visit();
    //    Director::getInstance()->getRunningScene()->visit();
    tex->end();
    if (blursprite) {
        blursprite->removeFromParentAndCleanup(true);
        blursprite = nullptr;
    }
    
    blursprite = FilteredSpriteWithOne::createWithTexture(tex->getSprite()->getTexture());
    blursprite->setFilter(GaussianHBlurFilter::create(4));
    //blursprite->setFilters(one);
    blursprite->setPosition(size.width/2, size.height/2);
    blursprite->setScaleY(-1);
    pausedLayer->addChild(blursprite,-1);
    
    pauseMenu->setVisible(false);
    pausedLayer->setVisible(true);
    gameScene->pauseGame();
}



void UILayer::mainCallback(Ref* sender)
{
    //Director::getInstance()->replaceScene(TransitionFade::create(1, Gamepanel::createScene()));
}



void UILayer::gameEnd(bool isWin)
{
    winLayer->setVisible(isWin);
    failedLayer->setVisible(!isWin);
    scheduleOnce(CC_SCHEDULE_SELECTOR(UILayer::showEndResult), 1.0);
}

void UILayer::showEndResult(float t)
{
    rateLayer->setVisible(true);
    rateLayer->showResultWithAnimation();
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
    float lifeTarget = gameScene->getWorld()->getWall()->getLife()/gameScene->getWorld()->getWall()->getTotalLife()*100;

    if (currentLifeValue > lifeTarget) {
        currentLifeValue -= 0.1;
        if (currentLifeValue < 0) {
            currentLifeValue = 0;
        }
        if (currentLifeValue <= lifeTarget) {
            currentLifeValue = lifeTarget;
        }
    }else if(currentLifeValue < lifeTarget){
        currentLifeValue += 0.1;
        if (currentLifeValue > 100) {
            currentLifeValue = 100;
        }
        if (currentLifeValue >= lifeTarget) {
            currentLifeValue = lifeTarget;
        }
    }
    float enegyTarget = gameScene->getWorld()->getEnegy();
    if (currentEnegyValue > enegyTarget) {
        currentEnegyValue -= 0.1;
        if (currentEnegyValue < 0) {
            currentEnegyValue = 0;
        }
        if (currentEnegyValue <= enegyTarget) {
            currentEnegyValue = enegyTarget;
        }
    }else if(currentEnegyValue < enegyTarget){
        currentEnegyValue += 0.1;
        if (currentEnegyValue > 100) {
            currentEnegyValue = 100;
        }
        if (currentEnegyValue >= enegyTarget) {
            currentEnegyValue = enegyTarget;
        }
    }
    
    lifeProgressBar->setPercentage(currentLifeValue);
    enegyProgressBar->setPercentage(currentEnegyValue);
    lifeBarHead->setPositionX(lifeBar->getContentSize().width * currentLifeValue/100.0f);
    enegyBarHead->setPositionX(enegyBar->getContentSize().width * currentEnegyValue/100.0f);
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

void UILayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch *touch = touches.at(0);
    if (gameScene->getState()!=GameStateGaming) {
        return;
    }
    if (!hudLayer->isVisible()) {
        return;
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
        return;
    }

}

void UILayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}

void UILayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}

void UILayer::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
    
}

//bool UILayer::onTouchBegan(Touch* touch, Event* event)
//{
//    if (gameScene->getState()!=GameStateGaming) {
//        return false;
//    }
//    if (!hudLayer->isVisible()) {
//        return false;
//    }
//    AppDelegate *app = (AppDelegate*)Application::getInstance();
//    float scaleFactory = app->scaleFactory;
//    
//    Vec2 pos = touch->getLocation();
//    Rect rect = Rect(knifeIcon->getPositionX()-200*scaleFactory/2, knifeIcon->getPositionY()-200*scaleFactory/2, 200*scaleFactory, 200*scaleFactory);
//    if (rect.containsPoint(pos)) {
//        if(gameScene->getWorld()->isUseKnife()){
//            toggleToGun();
//        }else{
//            toggleToKnife();
//        }
//        return true;
//    }
//    
//    return false;
//}
//
//void UILayer::onTouchMoved(Touch* touch, Event* event)
//{
//
//}
//
//void UILayer::onTouchEnded(Touch* touch, Event* event)
//{
//
//}
//
//void UILayer::onTouchCancelled(Touch *touch, Event *unused_event)
//{
//
//}
