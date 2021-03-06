//
//  Weapon.h
//  BGT
//
//  Created by John Running on 15/3/13.
//
//

#ifndef __BGT__Weapon__
#define __BGT__Weapon__

#include "cocos2d.h"
#include "GameEntity.h"


USING_NS_CC;

class Weapon : public GameEntity
{
protected:
    float damage;
    float origDamage;
    bool isXuliDamage;
    WeaponType type;
    bool xuliing;
    double xuliTotalTime;
    double xuliTimePast;
    int durability;//耐久度
    static int  m_attackID;//玩家一次攻击的id
public:
    virtual void setDamage(float v){ damage = v; };
    virtual float getDamage(){ return damage; };
    virtual ~Weapon(){};
//    virtual bool onTouchBegan(Touch* touch, Event* event)=0;
//    virtual void onTouchMoved(Touch* touch, Event* event)=0;
//    virtual void onTouchEnded(Touch* touch, Event* event)=0;
//    virtual void onTouchCancelled(Touch *touch, Event *unused_event)=0;
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)=0;
    
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)=0;
    
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)=0;
    
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)=0;
    
    WeaponType getType() { return type; };
};

#endif /* defined(__BGT__Weapon__) */
