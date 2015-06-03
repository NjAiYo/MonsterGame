//
//  GameEndRateLayer.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#include "GameEndRateLayer.h"
#include "AppDelegate.h"
#include "GameScene.h"

GameEndRateLayer::GameEndRateLayer()
{
    
}

bool GameEndRateLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    LayerColor *bgLayer = LayerColor::create(Color4B(0, 0, 0, 170));
    addChild(bgLayer);
    
    Sprite *rateBg = Sprite::create("endPanelBg.png");
    addChild(rateBg);
    rateBg->setPosition(size.width/2,size.height/2);
    
    Sprite *rateAvatar = Sprite::create("endPanelAvatar");
    addChild(rateAvatar);
    rateAvatar->setPosition(rateAvatar->getContentSize().width/2,size.height/2);
    
    Sprite *sp = Sprite::createWithSpriteFrameName("endPanelLabels.png");
    addChild(sp);
    sp->setPosition(1070*scaleFactory,size.height-360*scaleFactory);
    
    Label *comboLabel = Label::createWithSystemFont("215", "Arial Black", 60);
    addChild(comboLabel);
    comboLabel->setPosition(1270*scaleFactory,size.height-260*scaleFactory);
    
    Label *lifeLabel = Label::createWithSystemFont("96%", "Arial Black", 60);
    addChild(lifeLabel);
    lifeLabel->setPosition(1270*scaleFactory,size.height-360*scaleFactory);
    
    Label *timeLabel = Label::createWithSystemFont("02:38", "Arial Black", 60);
    addChild(timeLabel);
    timeLabel->setPosition(1270*scaleFactory,size.height-460*scaleFactory);
    
    //ss
    sp = Sprite::createWithSpriteFrameName("endPanelZiMuDi.png");
    addChild(sp);
    sp->setPosition(1750*scaleFactory,820*scaleFactory);
    
    sp = Sprite::createWithSpriteFrameName("rateAIcon.png");
    addChild(sp);
    sp->setPosition(1750*scaleFactory,820*scaleFactory);
    
    
    sp = Sprite::createWithSpriteFrameName("endPanelSpector.png");
    addChild(sp);
    sp->setPosition(1270*scaleFactory,size.height-460*scaleFactory);
    
    sp = Sprite::createWithSpriteFrameName("endPanelJinYanJinBiFrame.png");
    addChild(sp);
    sp->setPosition(1271*scaleFactory,625*scaleFactory);
    
    Sprite *expIconSprite = Sprite::createWithSpriteFrameName("EXPLabel.png");
    sp->addChild(expIconSprite);
    expIconSprite->setPosition(0,sp->getContentSize().height/2);
    
    Label *expLabel = Label::createWithBMFont("gameSceneJiaLifeLabel.fnt", "+800");
    sp->addChild(expLabel);
    expLabel->setPosition(sp->getContentSize().width/2,sp->getContentSize().height/2);
    
    sp = Sprite::createWithSpriteFrameName("endPanelCoin.png");
    addChild(sp);
    sp->setPosition(1750*scaleFactory,625*scaleFactory);
    Sprite *moneyIconSprite = Sprite::createWithSpriteFrameName("EXPLabel.png");
    sp->addChild(moneyIconSprite);
    moneyIconSprite->setPosition(0,sp->getContentSize().height/2);
    
    Label *moneyLabel = Label::createWithBMFont("gameSceneJiaLifeLabel.fnt", "+1000");
    sp->addChild(moneyLabel);
    moneyLabel->setPosition(sp->getContentSize().width/2,sp->getContentSize().height/2);
    
    Label *levelLabel = Label::createWithSystemFont("Lv.2", "Arial Black", 60);
    addChild(levelLabel);
    levelLabel->setPosition(1400*scaleFactory,370*scaleFactory);
    
    //经验条
    sp = Sprite::createWithSpriteFrameName("endPanelExpBarFrame.png");
    addChild(sp);
    sp->setPosition(1500*scaleFactory,370*scaleFactory);
    Sprite *expBar = Sprite::createWithSpriteFrameName("endPanelExpBar.png");
    sp->addChild(expBar);
    expBar->setPosition(0,0);
    
    
    //物品底图
    sp = Sprite::createWithSpriteFrameName("endPanelWuPinDi.png");
    addChild(sp);
    sp->setPosition(1500*scaleFactory,370*scaleFactory);
    
    //menu
    Sprite *sprite = Sprite::createWithSpriteFrameName("againButton.png");
    Sprite *sprite1 = Sprite::createWithSpriteFrameName("againButton.png");
    sprite1->setScale(1.1);
    Size spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *restartItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(GameEndRateLayer::restartCallback, this));
    
    
    sprite = Sprite::createWithSpriteFrameName("sureButton.png");
    sprite1 = Sprite::createWithSpriteFrameName("sureButton.png");
    sprite1->setScale(1.1);
    spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *nextItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(GameEndRateLayer::sureCallback, this));
    
    Menu *menu = Menu::create(restartItem,nextItem,NULL);
    menu->setPosition(size.width-680*scaleFactory,size.height/2);
    menu->alignItemsHorizontallyWithPadding(50);
    addChild(menu, 1);
    
    return true;
}

void GameEndRateLayer::showResultWithAnimation()
{
    
}

void GameEndRateLayer::sureCallback(Ref* sender)
{
    
}

void GameEndRateLayer::restartCallback(Ref* sender)
{
    //    gameScene->restartGame();
    //
    //    enegyProgressBar->setPercentage(0);
    
    Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createSceneWithLevel(0)));
}
