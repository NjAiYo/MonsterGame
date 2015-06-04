//
//  SkillState.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/2.
//
//

#include "SkillState.h"
#include "Character.h"
#include <SimpleAudioEngine.h>
#include "GameEntityManager.h"
#include "Weapon.h"
#include "MessageDispatcher.h"
#include "BGTWall.h"

void SkillState::enter(Character* agent)
{
    chargeTime = 2;
    totalDamageTaked = 0;
    charging = true;
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, ChargeAnimationName, false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        
    });
//    float a = CCRANDOM_0_1();
//    if (a < 0.5) {
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("cg_gd1.mp3");
//    }else{
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("cg_gd2.mp3");
//    }
}

void SkillState::execute(Character* agent,float dt)
{
    chargeTime -= dt;
    if (chargeTime <= 0 && charging) {
        charging = false;
        spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, ChargeEndAnimationName, false);
        agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
            EventCustom event("monsterSkilled");
            event.setUserData(agent);
            agent->getEventDispatcher()->dispatchEvent(&event);
            spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, SkillAnimationName, false);
            agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
                float damage = agent->getDamage()*5;
                BGTWall *wall = agent->getWorld()->getWall();
                MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                                  agent->getID(),           //sender ID
                                                                  wall->getID(),           //receiver ID
                                                                  Msg_WallDamaged,        //msg
                                                                  &damage);
                agent->move();
            });
        });
    }
}

void SkillState::exit(Character* agent)
{
    
}

bool SkillState::onMessage(Character* agent, const Telegram& msg)
{
    if(msg.msg == Msg_AttackedByXuLiWeapon || msg.msg == Msg_AttackedByWeapon){
        Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
        
        MonsterData *data = agent->getMonsterData();
        if (data->shanbi > 0) {
            float value = CCRANDOM_0_1();
            if (value <= data->shanbi) {
                //闪避
                agent->shanbi();
                return false;
            }
        }
        if (data->gedang > 0) {
            float value = CCRANDOM_0_1();
            if (value <= data->gedang) {
                //格挡
                agent->parry();
                return false;
            }
        }
        
        //进入防御状态
        if (agent->canDefense() && agent->getLife() < agent->getTotalLife()*0.5) {
            agent->defense();
            return false;
        }
        AttackInfo info = *(AttackInfo*)msg.extraInfo;
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
                        agent->stiff();
                    }
                }else{
                    agent->stiff();
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