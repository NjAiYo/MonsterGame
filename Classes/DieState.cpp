//
//  DieState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "DieState.h"
#include "Character.h"
#include <SimpleAudioEngine.h>

void DieState::enter(Character* agent)
{
    deadTime = 0;
    //agent->playAnimation(0,"die", true);
    float r = CCRANDOM_0_1();
    const char* name;
    if (r < 0.5) {
        name = Die2AnimationName;
    }else{
        name = DieAnimationName;
    }
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, name, false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        //agent->move();
    });
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
    EventCustom event("MonsterDied");
    event.setUserData(agent);
    agent->getEventDispatcher()->dispatchEvent(&event);
}

void DieState::execute(Character* agent,float dt)
{
    deadTime += dt;
    if (deadTime >= 2.5) {
        agent->setVisible(false);
        //agent->runAction(FadeOut::create(1.0));
    }
}

void DieState::exit(Character* agent)
{
    
}

bool DieState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
