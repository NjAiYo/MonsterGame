//
//  BGTWall.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTWall.h"
#include "AppDelegate.h"
#include "Character.h"
#include "GameEntityManager.h"

BGTWall::BGTWall()
:totalLife(0)
,life(0)
,died(false)
,lifeBar(NULL)
{
    
}

bool BGTWall::initWithWorld(BGTWorld *w){
    if (!GameEntity::initWithWorld(w)) {
        return false;
    }
    died = false;
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    width = fieldHeight * scaleFactory;
    
    Sprite *stone1 = Sprite::create("stone.png");
    this->addChild(stone1);
    stone1->setPosition(40*scaleFactory,205*scaleFactory);
    
    Sprite *doormask = Sprite::create("doormask.png");
    this->addChild(doormask);
    doormask->setPosition(-60*scaleFactory,250*scaleFactory);
    
    Sprite *rope = Sprite::create("rope.png");
    this->addChild(rope);
    rope->setPosition(0,0);
    
    Sprite *stone2 = Sprite::create("stone.png");
    this->addChild(stone2);
    stone2->setPosition(-60*scaleFactory,-300*scaleFactory);
    totalLife = 100;
    life = totalLife;
    
    
    for (int i = 0; i < 5; i++) {
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
    return true;
}

float BGTWall::getLife()
{
    return life;
}

float BGTWall::getTotalLife()
{
    return totalLife;
}

void BGTWall::reset()
{
    died = false;
    life = totalLife;
}

float BGTWall::getWidth()
{
    return width;
}

void BGTWall::takeDamage(float damage){
    life -= damage;
    if (life < 0) {
        life = 0;
    }
}

Label* BGTWall::getDamageLabelFromPool()
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

Label* BGTWall::getBaoDamageLabelFromPool()
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

float BGTWall::calculateDamage(float sourceDamage)
{
    return sourceDamage;
}

bool BGTWall::handleMessage(const Telegram& msg)
{
    //TODO::计算miss
    
    switch (msg.msg) {
        case Msg_WallDamaged:{
            Character *monster = (Character*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
            float damage = *(float*)msg.extraInfo;
            log("takedamage:%f",damage);
            damage = calculateDamage(damage);
            takeDamage(damage);
            Vec2 p = this->convertToNodeSpace(Vec2(0, monster->getFloor()+monster->getBoundingBox().size.height/2));
            Label *label = getDamageLabelFromPool();
            label->setPosition(50, p.y);
            label->setVisible(true);
            label->setOpacity(255);
            label->setString(String::createWithFormat("%d",(int)damage)->getCString());
            
            CallFunc *func = CallFunc::create([=](){
                label->setVisible(false);
            });
            label->runAction(Sequence::create(Spawn::create(MoveBy::create(1.5, Vec2(0, 400)),FadeOut::create(1.5), NULL),func, NULL));
        }
            break;
        case Msg_WallBaoDamaged:{
            Character *monster = (Character*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
            float damage = *(float*)msg.extraInfo;
            log("takebaodamage:%f",damage);
            damage = calculateDamage(damage);
            takeDamage(damage);
            Vec2 p = this->convertToNodeSpace(Vec2(0, monster->getFloor()+monster->getBoundingBox().size.height/2));
            //show bao shang
            Label *label = getBaoDamageLabelFromPool();
            label->setPosition(50, p.y);
            label->setVisible(true);
            label->setOpacity(255);
            label->setScale(1.0);
            label->setString(String::createWithFormat("暴击\n  %d  ",(int)damage)->getCString());
            
            CallFunc *func = CallFunc::create([=](){
                label->setVisible(false);
            });
            label->runAction(Sequence::create(Spawn::create(MoveBy::create(1.5, Vec2(0, 400)),FadeOut::create(1.5), NULL),func, NULL));
        }
            break;
            
        default:
            break;
    }
    return false;
}

bool BGTWall::hittestPoint(Vec2 p)
{
    return false;
}

void BGTWall::update(float dt){

}
