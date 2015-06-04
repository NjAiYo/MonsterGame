//
//  DropState.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/4.
//
//

#include "DropState.h"
#include "Character.h"
#include <SimpleAudioEngine.h>

void DropState::enter(Character* agent)
{
    Size size = Director::getInstance()->getWinSize();
    dropSpeed = 100;
    ay = dropSpeed;
    float value = CCRANDOM_0_1() * 100 + 200;
    targetX = size.width - value;
    targetY = agent->getFloor();
    
    float dx = targetX - agent->getPositionX();
    float dy = targetY - agent->getPositionY();
    
    radians = -atan2f(dy, dx);
    
    
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, WalkAnimationName, false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        //agent->move();
    });
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
}

void DropState::execute(Character* agent,float dt)
{
    bool hitFloor = false;
    ay += gravity * dt;
    float x = ay * cosf(radians);
    float y = ay * sinf(radians);
    
    float newY = y + agent->getPositionY();
    if (newY <= agent->getFloor()) {
        newY = agent->getFloor();
        hitFloor = true;
    }
    float newX = x + agent->getPositionY();
    if (newX < targetX) {
        newX = targetX;
    }
    agent->setPositionX(newX);
    agent->setPositionY(newY);
    if (hitFloor) {
        if (agent->getLife() <= 0) {
            agent->die();
        }else{
            agent->attack();
        }
    }
}

void DropState::exit(Character* agent)
{
    
}

bool DropState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
