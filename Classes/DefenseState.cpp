//
//  DefenseState.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/4.
//
//

#include "DefenseState.h"
#include "Character.h"
#include <SimpleAudioEngine.h>
#include "GameEntityManager.h"
#include "Weapon.h"

void DefenseState::enter(Character* agent)
{
    defenseTime = 2;
    ending = false;
    //agent->playAnimation(0,"die", true);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, DefenseAnimationName, false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        //agent->move();
    });
    float a = CCRANDOM_0_1();
    if (a < 0.5) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("cg_gd1.mp3");
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("cg_gd2.mp3");
    }
}

void DefenseState::execute(Character* agent,float dt)
{
    defenseTime -= dt;
    if (defenseTime <= 0 && !ending) {
        ending = true;
        spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, DefenseEndAnimationName, false);
        agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
            agent->move();
        });
    }
}

void DefenseState::exit(Character* agent)
{
    
}

bool DefenseState::onMessage(Character* agent, const Telegram& msg)
{
    switch (msg.msg) {
        case Msg_AttackedByWeapon:{//被玩家的武器攻击到
            //Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
            
            MonsterData *data = agent->getMonsterData();
            if (data->canQTE) {
                //qte 触发
                agent->getWorld()->enterQTEMode(agent);
            }
        }
            break;
        default:
            break;
    }
    return false;
}
