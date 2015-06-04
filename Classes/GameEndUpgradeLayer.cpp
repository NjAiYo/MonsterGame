//
//  GameEndUpgradeLayer.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#include "GameEndUpgradeLayer.h"
#include "AppDelegate.h"

GameEndUpgradeLayer::GameEndUpgradeLayer()
{
    
}

bool GameEndUpgradeLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    LayerColor *bgLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(bgLayer);
    needEatTouch = false;
    endPanelLight = Sprite::create("endPanelLight.png");
    addChild(endPanelLight);
    endPanelLight->setPosition(size.width/2,size.height/2);
    
    Sprite *upBgSp = Sprite::create("upgredBg.png");
    addChild(upBgSp);
    upBgSp->setPosition(size.width/2,size.height/2);
    
    Sprite *upLabelSp = Sprite::createWithSpriteFrameName("upgredLabel.png");
    upBgSp->addChild(upLabelSp);
    upLabelSp->setPosition(upBgSp->getContentSize().width/2,upBgSp->getContentSize().height-75*scaleFactory);
    
    upgredTip = Sprite::createWithSpriteFrameName("upgredTip.png");
    upBgSp->addChild(upgredTip);
    upgredTip->setPosition(upBgSp->getContentSize().width/2-50*scaleFactory,upBgSp->getContentSize().height-250*scaleFactory);
    Label *upLabel = Label::createWithCharMap("upgredHerolLevelLabel.png", 54, 60, '0');
    upBgSp->addChild(upLabel);
    upLabel->setString("36");
    upLabel->setPosition(upBgSp->getContentSize().width/2+335*scaleFactory,upBgSp->getContentSize().height-250*scaleFactory);
    
    Label *lifeLabel = Label::createWithSystemFont("生命: ", "Arial Black", 60);
    upBgSp->addChild(lifeLabel);
    lifeLabel->setPosition(upBgSp->getContentSize().width/2-70*scaleFactory,upBgSp->getContentSize().height/2+65*scaleFactory);
    
    Label *addLifeLabel = Label::createWithBMFont("gameSceneEndGreenLabel.fnt", "+25");
    upBgSp->addChild(addLifeLabel);
    addLifeLabel->setPosition(upBgSp->getContentSize().width/2+55*scaleFactory,upBgSp->getContentSize().height/2+65*scaleFactory);
    
    
    Sprite *sp = Sprite::createWithSpriteFrameName("endPanelCoin.png");
    upBgSp->addChild(sp);
    sp->setPosition(upBgSp->getContentSize().width/2-100*scaleFactory,335*scaleFactory);
    
    Label *moneyLabel = Label::createWithBMFont("gameSceneEndGreenLabel.fnt", "+200");
    upBgSp->addChild(moneyLabel);
    moneyLabel->setPosition(upBgSp->getContentSize().width/2+100*scaleFactory,335*scaleFactory);
    
    
    expIconSprite = Sprite::createWithSpriteFrameName("EXPLabel.png");
    upBgSp->addChild(expIconSprite);
    expIconSprite->setPosition(upBgSp->getContentSize().width/2-100*scaleFactory,235*scaleFactory);
    
    Label *expLabel = Label::createWithBMFont("gameSceneEndGreenLabel.fnt", "+800");
    upBgSp->addChild(expLabel);
    expLabel->setPosition(upBgSp->getContentSize().width/2+100*scaleFactory,235*scaleFactory);
    

    
    
    Sprite *sprite = Sprite::createWithSpriteFrameName("awardButton.png");
    Sprite *sprite1 = Sprite::createWithSpriteFrameName("awardButton.png");
    sprite1->setScale(1.1);
    Size spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *awardItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(GameEndUpgradeLayer::awardCallback, this));
    
    Menu *menu = Menu::create(awardItem,NULL);
    menu->setPosition(size.width/2,250*scaleFactory);
    addChild(menu, 1);
    
    //遮挡底下层的按钮点击事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameEndUpgradeLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    return true;
}

void GameEndUpgradeLayer::show()
{
    this->setVisible(true);
    needEatTouch = true;
}

void GameEndUpgradeLayer::hide()
{
    this->setVisible(false);
    needEatTouch = false;
}


bool GameEndUpgradeLayer::onTouchBegan(Touch* touch, Event* event)
{
    return needEatTouch;
}

void GameEndUpgradeLayer::showResultWithAnimation()
{
    
}

void GameEndUpgradeLayer::awardCallback(Ref* sender)
{
    
}

