//
//  QTELayer.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/6.
//
//

#include "QTELayer.h"
#include "BGTWorld.h"



QTELayer::QTELayer()
:qteMonster(NULL)
,enableFight(false)
,percentage(50)
,monsterDamage(1)
,playerDamage(1)
{
    
}

bool QTELayer::initWithWorld(BGTWorld *w)
{
    if (!Node::init()) {
        return false;
    }
    enableFight = false;
    percentage = 50;
    monsterDamage = 1;
    playerDamage = 1;
    bgLayer = LayerColor::create(Color4B(0, 0, 0, 200));
    addChild(bgLayer);
    
    Size size = Director::getInstance()->getWinSize();
    
    Sprite *bg = Sprite::create("qteBg.png");
    addChild(bg);
    bg->setPosition(size.width/2, size.height/2);
    
    
    world = w;
    qteMonster = new QTEMonster();
    qteMonster->initWithQTELayerAndType(this, CharacterTypeSmallWuTouYong);
    this->addChild(qteMonster);
    qteMonster->setPosition(size.width/2, size.height/2);
    qteMonster->release();
    
    Sprite *avatarBg = Sprite::createWithSpriteFrameName("qteHeroAvatarBg.png");
    addChild(avatarBg);
    avatarBg->setPosition(230,size.height-160);
    Sprite *avatar = Sprite::createWithSpriteFrameName("heroAvatarQTE.png");
    avatarBg->addChild(avatar);
    avatar->setPosition(avatarBg->getContentSize().width/2,avatarBg->getContentSize().height/2);
    
    
    avatarBg = Sprite::createWithSpriteFrameName("qteMonsterAvatarBg.png");
    addChild(avatarBg);
    avatarBg->setPosition(size.width-230,size.height-160);
    avatar = Sprite::createWithSpriteFrameName("monster2AvatarQTE.png");
    avatarBg->addChild(avatar);
    avatar->setPosition(avatarBg->getContentSize().width/2,avatarBg->getContentSize().height/2);
    
    bar = Sprite::createWithSpriteFrameName("qteBarFrame.png");
    addChild(bar);
    bar->setPosition(size.width/2,size.height-120);
    

    progressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("qteBar.png"));
    progressBar->setType(ProgressTimer::Type::BAR);
    progressBar->setMidpoint(Vec2(0,1));
    progressBar->setBarChangeRate(Vec2(1, 0));
    progressBar->setPercentage(50);
    progressBar->setPosition(bar->getContentSize().width/2,bar->getContentSize().height/2);
    bar->addChild(progressBar);
    
    
    qteMark = Sprite::createWithSpriteFrameName("qteMark.png");
    bar->addChild(qteMark);
    qteMark->setAnchorPoint(Vec2(0.5,0.5));
    
    float rate = progressBar->getPercentage() / 100.0f;
    qteMark->setPosition(bar->getContentSize().width*rate,bar->getContentSize().height);
    
    
    streak = MotionStreak::create(0.5f, 50, 30, Color3B::WHITE, "steak.png");
    //    streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "steak.png");
    streak->setPosition(Vec2(-1000,-1000)); // …Ë÷√ÕœŒ≤streakµƒŒª÷√
    addChild(streak);
    
    
    countDownLabel = Label::createWithBMFont("gameSceneCountDownLabel.fnt", "3");
    countDownLabel->setPosition(size.width/2, size.height/2);
    addChild(countDownLabel);
    countDownLabel->setVisible(false);
    
    
    Sprite *barbg = Sprite::createWithSpriteFrameName("qteBarBg.png");
    bar->addChild(barbg);
    barbg->setPosition(bar->getContentSize().width/2,bar->getContentSize().height/2);
    return true;
}

void QTELayer::setMonsterType(CharacterType t)
{
    qteMonster->setType(t);
}

void QTELayer::countDown(float dt)
{
    if (countDownTime == 0) {
        countDownLabel->setString("GO!");
    }else if(countDownTime > 0){
        countDownLabel->setString(String::createWithFormat("%d",countDownTime)->getCString());
    }else{//-1
        startFight();
        unschedule(schedule_selector(QTELayer::countDown));
        return;
    }
    countDownTime--;
    countDownLabel->setScale(2.0);
    countDownLabel->setOpacity(200);
    countDownLabel->setVisible(true);
    countDownLabel->runAction(ScaleTo::create(1.0, 0));
}

void QTELayer::qteBegin()
{
    countDownTime = 3;
    enableFight = false;
    qteMonster->stand();
    percentage = 50;
    progressBar->setPercentage(percentage);
    float rate = progressBar->getPercentage() / 100.0f;
    qteMark->setPosition(bar->getContentSize().width*rate,bar->getContentSize().height);
    schedule(schedule_selector(QTELayer::countDown), 1);
}

void QTELayer::qteEnd()
{
    countDownLabel->setVisible(false);
    enableFight = false;
}

void QTELayer::startFight()
{
    enableFight = true;
    qteMonster->beginAttack();
}

QTEMonster* QTELayer::getQteMonster()
{
    return qteMonster;
}

void QTELayer::hitQteMonster()
{
    percentage += playerDamage;

    if (percentage >= 100) {
        percentage = 100;
    }
    progressBar->setPercentage(percentage);
    float rate = progressBar->getPercentage() / 100.0f;
    qteMark->setPosition(bar->getContentSize().width*rate,bar->getContentSize().height);
    if(percentage == 100){
        //player win
        qteMonster->die();
        world->exitQTEMode(true);
        qteEnd();
    }
}

void QTELayer::qteAttacked()
{
    percentage -= monsterDamage;
    if (percentage <= 0) {
        percentage = 0;
    }
    progressBar->setPercentage(percentage);
    float rate = progressBar->getPercentage() / 100.0f;
    qteMark->setPosition(bar->getContentSize().width*rate,bar->getContentSize().height);
    if(percentage == 0){
        //player failed
        qteMonster->stand();
        world->exitQTEMode(false);
        qteEnd();
    }
}

void QTELayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    if(!enableFight) return;
    Touch *touch = touches.at(0);
    Vec2 pos = touch->getLocation();
    //this->getChildByTag(111)->setPosition(Vec2(t->getLocation().x,t->getLocation().y));
    
    //star->setPosition(pos);
    streak->setPosition(pos);
    
    streak->reset();
    startTouchPosition = pos;
    
    currentTouchTime = millisecondNow();
}

void QTELayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    if(!enableFight) return;
    Touch *touch = touches.at(0);
    Vec2 delta = touch->getDelta();
    Vec2 lastPos = touch->getPreviousLocation();
    Vec2 pos = touch->getLocation();
    
    float dx = pos.x - startTouchPosition.x;
    float dy = pos.y - startTouchPosition.y;
    float dist = sqrtf(dx*dx+dy*dy);
    
    
    streak->setPosition(pos);
    //刀的判断
    dist = pos.distanceSquared(startTouchPosition);
    
    if (dist > 50) {
        //hit test monster
        bool hit = qteMonster->hittestPoint(pos);
        if (hit) {
            hitQteMonster();
        }
    }
}

void QTELayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    if(!enableFight) return;
}

void QTELayer::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
    if(!enableFight) return;
}

//bool QTELayer::onTouchBegan(Touch* touch, Event* event)
//{
//    if(!enableFight) return false;
//    Vec2 pos = touch->getLocation();
//    //this->getChildByTag(111)->setPosition(Vec2(t->getLocation().x,t->getLocation().y));
//    
//    //star->setPosition(pos);
//    streak->setPosition(pos);
//    
//    streak->reset();
//    startTouchPosition = pos;
//    
//    currentTouchTime = millisecondNow();
//    return true;
//}
//
//void QTELayer::onTouchMoved(Touch* touch, Event* event)
//{
//    
//    if(!enableFight) return;
//    Vec2 delta = touch->getDelta();
//    Vec2 lastPos = touch->getPreviousLocation();
//    Vec2 pos = touch->getLocation();
//    
//    float dx = pos.x - startTouchPosition.x;
//    float dy = pos.y - startTouchPosition.y;
//    float dist = sqrtf(dx*dx+dy*dy);
//    
//    
//    streak->setPosition(pos);
//    //刀的判断
//    dist = pos.distanceSquared(startTouchPosition);
//    
//    if (dist > 50) {
//        //hit test monster
//        bool hit = qteMonster->hittestPoint(pos);
//        if (hit) {
//            hitQteMonster();
//        }
//    }
//}
//
//void QTELayer::onTouchEnded(Touch* touch, Event* event)
//{
//    if(!enableFight) return;
//}
//void QTELayer::onTouchCancelled(Touch *touch, Event *unused_event)
//{
//    if(!enableFight) return;
//}
