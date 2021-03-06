//
//  Pistol.cpp
//  BGT
//
//  Created by John Running on 15/3/14.
//
//

#include "Pistol.h"
#include <SimpleAudioEngine.h>
#include "BGTWorld.h"
#include "Character.h"
#include "MessageDispatcher.h"
#include "AppDelegate.h"

bool Pistol::initWithWorld(BGTWorld *w)
{
    if (Weapon::initWithWorld(w)) {
        type = WeaponTypePistol;
        durability = 100;
        shotInteval = 250;
        canShot = true;
        xuliTotalTime = 500;//2秒
        xuliTimePast = 0;
        origDamage = 10;
        damage = origDamage;
        isXuliDamage = false;
        hitRectNode = DrawNode::create();
        addChild(hitRectNode,100000);
        return true;
    }
    return false;
}

//all subclasses can communicate using messages.
bool Pistol::handleMessage(const Telegram& msg)
{
    return false;
}

//all entities must implement an update function
void Pistol::update(float dt)
{
    if (!canShot) {
        if (millisecondNow() - lastShotTime >= shotInteval) {
            canShot = true;
        }
    }
}

bool Pistol::hittestPoint(Vec2 p)
{
    return false;
}

void Pistol::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch *touch = touches.at(0);
    Weapon::m_attackID++;
    //log("Pistol::onTouchBegan");
    //    if (!canShot) {
    //        return true;
    //    }
    lastShotTime = millisecondNow();
    Vec2 pos = touch->getLocation();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jq.mp3");
    canShot = false;
    //    for (Character *agent : world->getMonsters()) {
    //        log("agent->z:%d",agent->getLocalZOrder());
    //    }
    //hit test monster
    for (Character *agent : world->getMonsters()) {
        if (!agent->isVisible() || agent->isDieState()) {
            continue;
        }
        bool hit = agent->hittestPoint(pos);
        Vec2 dp = agent->convertToNodeSpace(pos);
        AttackInfo info;
        info.x = dp.x;
        info.y = dp.y;
        
        if (hit) {
            MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                              getID(),           //sender ID
                                                              agent->getID(),           //receiver ID
                                                              Msg_AttackedByWeapon,        //msg
                                                              &info);
            break;
        }
    }
}

void Pistol::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (!canShot) {
        return;
    }
    //    lastShotTime = millisecondNow();
    //    Vec2 pos = touch->getLocation();
    //    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jq.mp3");
    //    canShot = false;
    //
    //    //hit test monster
    //    for (Character *agent : world->getMonsters()) {
    //        if (!agent->isVisible()) {
    //            continue;
    //        }
    //        Rect rect = agent->getRect();
    //        bool hit = false;
    //        if (pos.x < rect.origin.x || pos.y < rect.origin.y || pos.x > rect.origin.x+rect.size.width || pos.y > rect.origin.y+rect.size.height) {
    //            hit = false;
    //        }else{
    //            hit = true;
    //        }
    //        if (hit) {
    //            MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
    //                                                              getID(),           //sender ID
    //                                                              agent->getID(),           //receiver ID
    //                                                              Msg_AttackedByWeapon,        //msg
    //                                                              NULL);
    //        }
    //    }
}

void Pistol::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}

void Pistol::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
    
}

//bool Pistol::onTouchBegan(Touch* touch, Event* event)
//{
//    Weapon::m_attackID++;
//    //log("Pistol::onTouchBegan");
////    if (!canShot) {
////        return true;
////    }
//    lastShotTime = millisecondNow();
//    Vec2 pos = touch->getLocation();
//    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jq.mp3");
//    canShot = false;
////    for (Character *agent : world->getMonsters()) {
////        log("agent->z:%d",agent->getLocalZOrder());
////    }
//    //hit test monster
//    for (Character *agent : world->getMonsters()) {
//        if (!agent->isVisible() || agent->isDieState()) {
//            continue;
//        }
//        bool hit = agent->hittestPoint(pos);
//        
//        if (hit) {
//            MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
//                                                              getID(),           //sender ID
//                                                              agent->getID(),           //receiver ID
//                                                              Msg_AttackedByWeapon,        //msg
//                                                              NULL);
//            break;
//        }
//        
//    }
//    return true;
//}
//
//void Pistol::onTouchMoved(Touch* touch, Event* event)
//{
//    if (!canShot) {
//        return;
//    }
////    lastShotTime = millisecondNow();
////    Vec2 pos = touch->getLocation();
////    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jq.mp3");
////    canShot = false;
////    
////    //hit test monster
////    for (Character *agent : world->getMonsters()) {
////        if (!agent->isVisible()) {
////            continue;
////        }
////        Rect rect = agent->getRect();
////        bool hit = false;
////        if (pos.x < rect.origin.x || pos.y < rect.origin.y || pos.x > rect.origin.x+rect.size.width || pos.y > rect.origin.y+rect.size.height) {
////            hit = false;
////        }else{
////            hit = true;
////        }
////        if (hit) {
////            MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
////                                                              getID(),           //sender ID
////                                                              agent->getID(),           //receiver ID
////                                                              Msg_AttackedByWeapon,        //msg
////                                                              NULL);
////        }
////    }
//}
//
//void Pistol::onTouchEnded(Touch* touch, Event* event)
//{
//    
//}
//
//void Pistol::onTouchCancelled(Touch *touch, Event *unused_event)
//{
//    
//}