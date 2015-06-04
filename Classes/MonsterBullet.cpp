//
//  MonsterBullet.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/4.
//
//

#include "MonsterBullet.h"
#include "AppDelegate.h"
#include "BGTWall.h"
#include "BGTWorld.h"

bool MonsterBullet::initWithWorld(BGTWorld *w)
{
    if (!GameEntity::initWithWorld(w)) {
        return false;
    }
    
    skin = Sprite::create();
    addChild(skin);
    radius = 100;
    speed = 100;
    damage = 1;
    baoji = 0;
    explosioning = false;
    flying = false;
    wall = w->getWall();
    return true;
}

CharacterType MonsterBullet::getType()
{
    return characterType;
}

void MonsterBullet::setType(CharacterType t)
{
    skin->stopAllActions();
    explosioning = false;
    characterType = t;
    bulletAnimation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("m%dbullet",t)->getCString());
    bulletExplosionAnimation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("m%dbullet_explosion",t)->getCString());
}

void MonsterBullet::fly()
{
    flying = true;
    this->setVisible(true);
    bulletAnimation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("m%dbullet",characterType)->getCString());
    skin->runAction(RepeatForever::create(Animate::create(bulletAnimation)));
}

void MonsterBullet::die()
{
    flying = false;
    explosioning = true;
    skin->stopAllActions();
    CallFunc *func = CallFunc::create([=](){
        this->setVisible(false);
        explosioning = false;
    });
    skin->runAction(Sequence::create(Animate::create(bulletExplosionAnimation),func, NULL));
}

void MonsterBullet::explosion()
{
    flying = false;
    explosioning = true;
    skin->stopAllActions();
    CallFunc *func = CallFunc::create([=](){
        this->setVisible(false);
        explosioning = false;
    });
    bulletExplosionAnimation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("m%dbullet_explosion",characterType)->getCString());
    skin->runAction(Sequence::create(Animate::create(bulletExplosionAnimation),func, NULL));
    BGTWall *wall = getWorld()->getWall();


    MessageType t = Msg_WallDamaged;
    if (baoji > 0) {
        float value = CCRANDOM_0_1();
        if (value <= baoji) {
            //暴击
            t = Msg_WallBaoDamaged;
            damage *= 2;
        }
    }
    int id = getID();
    MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                      id,           //sender ID
                                                      wall->getID(),           //receiver ID
                                                      t,        //msg
                                                      &damage);
}

MonsterBullet::MonsterBullet()
{
    
}

MonsterBullet::~MonsterBullet()
{
    
}

bool MonsterBullet::handleMessage(const Telegram& msg)
{
    return true;
}

void MonsterBullet::update(float dt)
{
    if (flying) {
        AppDelegate *app = (AppDelegate*)Application::getInstance();
        float scaleFactory = app->scaleFactory;
        float newX = getPositionX();
        newX-=speed*scaleFactory*dt;
        setPositionX(newX);
        wall = getWorld()->getWall();
        Vec2 a = wall->topPosition;
        Vec2 b = getPosition();
        //hit test wall
        bool hit = intersectCircleLine(getPosition(), 10, wall->topPosition, wall->bottomPosition);
        if (hit) {
            explosion();
        }
    }
}

bool MonsterBullet::hittestPoint(Vec2 p)
{
    //Vec2 pos = this->convertToNodeSpace(p);
    float dx = p.x - this->getPositionX();
    float dy = p.y - this->getPositionY();
    float dist = sqrtf(dx*dx+dy*dy);
    return dist <= radius;
}
