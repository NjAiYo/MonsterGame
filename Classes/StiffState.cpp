//
//  StiffState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "StiffState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"

void StiffState::enter(Character* agent)
{
    canMove = false;
    attacked = false;
    //agent->playAnimation(0,"stiff", true);
    //agent->getSkeletonNode()->setTimeScale(0.5);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, HurtAnimationName, false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        canMove = true;
    });
}

void StiffState::execute(Character* agent,float dt)
{
//    if (canMove && !attacked) {
//        agent->move();
//    }
    if (canMove) {
        agent->move();
    }
    if (attacked && millisecondNow() - startTime >= 200) {
        attacked = false;
    }
}

void StiffState::exit(Character* agent)
{
    agent->getSkeletonNode()->setTimeScale(1.0);
}

bool StiffState::onMessage(Character* agent, const Telegram& msg)
{
    if(msg.msg == Msg_AttackedByXuLiWeapon || msg.msg == Msg_AttackedByWeapon){
        AttackInfo info = *(AttackInfo*)msg.extraInfo;
        attacked = true;
        
        startTime = millisecondNow();
        //            spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "stiff", false);
        //            agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //                canMove = true;
        //
        //            });
        Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
        //蓄力攻击没有攻击力
        if (msg.msg == Msg_AttackedByWeapon){
            agent->takeDamage(weapon->getDamage(),Vec2(info.x,info.y));
            if (agent->getLife() <= 0) {
                agent->die();
                return false;
            }
        }
        agent->hitted();
        switch (weapon->getType()) {
            case WeaponTypeKnife:{
                //Knife *knife = (Knife*)weapon;
  
                if (msg.msg == Msg_AttackedByXuLiWeapon) {
                    if (info.direction == KnifeAttackDirectionUp) {
                        agent->flowup();
                    }else if (info.direction == KnifeAttackDirectionDown) {
                        agent->falldown();
                    }else if (info.direction == KnifeAttackDirectionRight) {
                        agent->rollback();
                    }else{
                        //agent->stiff();
                    }
                }else{
                    //agent->stiff();
                }
                
            }
                break;
            case WeaponTypePistol:
                agent->stiff();
                break;
            default:
                break;
        }
    }
    return false;
}
