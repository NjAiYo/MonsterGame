//
//  Knife.cpp
//  BGT
//
//  Created by John Running on 15/3/14.
//
//

#include "Knife.h"
#include "BGTWorld.h"
#include "MessageDispatcher.h"
#include "AppDelegate.h"
#include <SimpleAudioEngine.h>

bool Knife::initWithWorld(BGTWorld *w)
{
    if (Weapon::initWithWorld(w)) {
        lastHitCharacter = nullptr;
        streak = MotionStreak::create(0.5f, 50, 30, Color3B::WHITE, "steak.png");
        //    streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "steak.png");
        streak->setPosition(Vec2(-1000,-1000)); // …Ë÷√ÕœŒ≤streakµƒŒª÷√
        addChild(streak);
        type = WeaponTypeKnife;
        
        xuliLayer = Layer::create();
        addChild(xuliLayer);
        xuliLayer->setVisible(false);
        xuliBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("powerprobar.png"));

        xuliBar->setType(ProgressTimer::Type::RADIAL);
//        xuliBar->setMidpoint(cc.p(0,1));
//        xuliBar->setBarChangeRate(cc.p(1, 0));
        xuliBar->setPercentage(0);
        xuliLayer->addChild(xuliBar);
        xuliTotalTime = 500;//2秒
        xuliTimePast = 0;
        origDamage = 10;
        durability = 100;
        damage = origDamage;
        isXuliDamage = false;
        return true;
    }
    return false;
}

//all subclasses can communicate using messages.
bool Knife::handleMessage(const Telegram& msg)
{
    return false;
}

//all entities must implement an update function
void Knife::update(float dt)
{
    if (touchedForXuLi) {
        double currentTime = millisecondNow();
        if (currentTime >= currentTouchTime + 300) {
            //进入蓄力状态
            xuliing = true;
            xuliLayer->setVisible(true);
            xuliTimePast = 0;
            xuliBar->setPosition(startTouchPosition);
            touchedForXuLi = false;
        }
    }
    if (xuliing) {
        //isXuliDamage = true;
        xuliTimePast += dt*1000;
        double percentage = xuliTimePast / xuliTotalTime;
        if (percentage >= 1) {
            percentage = 1;
            isXuliDamage = true;
        }
        xuliBar->setPercentage(percentage*100);
        origDamage = 10;
        damage = origDamage * (1+percentage);
    }
}

//bool Knife::isXuliStateDamage()
//{
//    return isXuliDamage;
//}

bool Knife::onTouchBegan(Touch* touch, Event* event)
{
    Weapon::m_attackID++;
    CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    //log("Knife::onTouchBegan");
    Vec2 pos = touch->getLocation();
    //this->getChildByTag(111)->setPosition(Vec2(t->getLocation().x,t->getLocation().y));
    lastHitCharacter = nullptr;
    isXuliDamage = false;
    streak->setPosition(pos);
    
    streak->reset();
    startTouchPosition = pos;
    touchedForXuLi = true;
    currentTouchTime = millisecondNow();
    hitDistance = 301;
    return true;
}

void Knife::onTouchMoved(Touch* touch, Event* event)
{
    //log("Knife::onTouchMoved");
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get Sets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
    
    //CCLOG("Paddle::onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);

    Vec2 delta = touch->getDelta();
    Vec2 lastPos = touch->getPreviousLocation();
    Vec2 pos = touch->getLocation();
    
    float ddx = pos.x - lastPos.x;
    float ddy = pos.y - lastPos.y;
    float moveDistance = sqrtf(ddx*ddx+ddy*ddy);
    log("moveDistance:%f",moveDistance);
    //float moveDistance = pos.distance(lastPos);
    
    float dx = pos.x - startTouchPosition.x;
    float dy = pos.y - startTouchPosition.y;
    float dist = sqrtf(dx*dx+dy*dy);
    
    
    //    star->setPosition(star->getPosition() + delta);
    //    streak->setPosition(star->getPosition());
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    if (dist > 100*scaleFactory){
        touchedForXuLi = false;
    }
    if (xuliing){
        xuliBar->setPosition(pos);
    }
    
//    if (xuliing) {
//        float xulibarradius = 300 * scaleFactory;
//
//        if (dist > xulibarradius) {
//            //如果手指出了蓄力槽范围
//            xuliing = false;
//            xuliLayer->setVisible(false);
//        }
//    }

    
    
    streak->setPosition(pos);
    //刀的判断
//    dist = pos.distance(startTouchPosition);

    //if (dist > 50) {
        dx = pos.x - lastPos.x;
        dy = pos.y - lastPos.y;
        float angle2 = atan2f(dy, dx)*180/M_PI;
        //log("angle1:%f,angle2:%f",angle1,angle2);
        
        KnifeAttackDirection direction;
        
        if(angle2 <= 135 && angle2 >= 45){
            //往上划
            direction = KnifeAttackDirectionUp;
        }else if(angle2 <= -45 && angle2 >= -135){
            //往下划
            direction = KnifeAttackDirectionDown;
        }else if (angle2 <= 45 && angle2 >= -45) {
            //往右划
            direction = KnifeAttackDirectionRight;
        }else{
            //往左划
            direction = KnifeAttackDirectionLeft;
        }
        
        //hit test monster
        for (Character *agent : world->getMonsters()) {
            if (!agent->isVisible() || agent->isDieState()) {
                continue;
            }
            bool hit = agent->hittestPoint(pos);
            if (hit) {
                log("hit:%d",agent->getID());
                //startTouchPosition = pos;
                if (agent != lastHitCharacter) {
                    hitDistance = 301;
                }else{
                    hitDistance+=moveDistance;
                }
                
                lastHitCharacter = agent;
                if (hitDistance > 300) {
                    hitDistance = 0;
                    log("damage hit:%d,%f",agent->getID(),moveDistance);
                    if (isXuliDamage) {
                        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                                          getID(),           //sender ID
                                                                          agent->getID(),           //receiver ID
                                                                          Msg_AttackedByXuLiWeapon,        //msg
                                                                          &direction);
                    }else{
                        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                                          getID(),           //sender ID
                                                                          agent->getID(),           //receiver ID
                                                                          Msg_AttackedByWeapon,        //msg
                                                                          &direction);
                    }
                    
                    if (xuliing) {
                        xuliing = false;
                        xuliLayer->setVisible(false);
                    }
                    isXuliDamage = false;
                    
                }
                return;
            }
        }
    //}
    //如果没有碰到任何怪
    lastHitCharacter = nullptr;
    hitDistance = 301;
    log("not hit");
}

void Knife::onTouchEnded(Touch* touch, Event* event)
{
    Vec2 delta = touch->getDelta();
    touchedForXuLi = false;
    xuliing = false;
    xuliLayer->setVisible(false);
    damage = origDamage;
    isXuliDamage = false;
    //    star->setPosition(star->getPosition() + delta);
    //    streak->setPosition(star->getPosition());
    
    Vec2 pos = touch->getLocation();
    streak->setPosition(pos);
    
    float dx = pos.x - startTouchPosition.x;
    float dy = pos.y - startTouchPosition.y;
    float dist = sqrtf(dx*dx+dy*dy);
    if(dist > 100){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
    }
}

void Knife::onTouchCancelled(Touch *touch, Event *unused_event)
{
    touchedForXuLi = false;
    xuliing = false;
    xuliLayer->setVisible(false);
    damage = origDamage;
    isXuliDamage = false;
    
    Vec2 pos = touch->getLocation();
}

bool Knife::hittestPoint(Vec2 p)
{
    return false;
}
