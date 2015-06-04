//
//  LieDownState.cpp
//  BGT
//
//  Created by John Running on 15/3/13.
//
//

#include "LieDownState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"

void LieDownState::enter(Character* agent)
{
    //agent->playAnimation(0,"die", true);
    //spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "laydown", true);
//    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
//
//    });
    startTime = millisecondNow();
}

void LieDownState::execute(Character* agent,float dt)
{
    if (millisecondNow() - startTime >= 1000) {
        agent->standup();
    }
}

void LieDownState::exit(Character* agent)
{
    
}

bool LieDownState::onMessage(Character* agent, const Telegram& msg)
{
    if(msg.msg == Msg_AttackedByXuLiWeapon || msg.msg == Msg_AttackedByWeapon){
        AttackInfo info = *(AttackInfo*)msg.extraInfo;
        Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
        //蓄力攻击没有攻击力
        if (msg.msg == Msg_AttackedByWeapon){
            agent->takeDamage(weapon->getDamage(),Vec2(info.x,info.y));
            if (agent->getLife() <= 0) {
                agent->die();
                return false;
            }
        }
        spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, PourHurtAnimationName, false);
        agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
            //agent->getSkeletonNode()->setAnimation(0, "laydown", true);
        });
        agent->hitted();
        switch (weapon->getType()) {
            case WeaponTypeKnife:{
                //Knife *knife = (Knife*)weapon;
                
                if (msg.msg == Msg_AttackedByXuLiWeapon) {
                    if (info.direction == KnifeAttackDirectionUp) {
                        agent->flowup();
                    }else if (info.direction == KnifeAttackDirectionDown) {
                        //agent->falldown();
                    }else{
                        //agent->stiff();
                    }
                }
                
            }
                break;
            case WeaponTypePistol:
                break;
            default:
                break;
        }
    }
    return false;
}