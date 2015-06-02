//
//  AttackState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "AttackState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"
#include "MessageDispatcher.h"
#include "BGTWall.h"

void AttackState::attack(Character* agent)
{
    attacking = true;
    attackNum++;
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, AttackAnimationName, false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        BGTWall *wall = agent->getWorld()->getWall();
        float damage = agent->getDamage();
        MonsterData *data = agent->getMonsterData();
        MessageType t = Msg_WallDamaged;
        if (data->baoji > 0) {
            float value = CCRANDOM_0_1();
            if (value <= data->baoji) {
                //暴击
                t = Msg_WallBaoDamaged;
                damage *= 2;
            }
        }
        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                          agent->getID(),           //sender ID
                                                          wall->getID(),           //receiver ID
                                                          t,        //msg
                                                          &damage);
        attacking = false;

    });
}

void AttackState::bigAttack(Character* agent)
{
    attacking = true;
    attackNum++;
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, Attack2AnimationName, false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        
        BGTWall *wall = agent->getWorld()->getWall();
        float damage = agent->getDamage()*1.0;
        MonsterData *data = agent->getMonsterData();
        MessageType t = Msg_WallDamaged;
        if (data->baoji > 0) {
            float value = CCRANDOM_0_1();
            if (value <= data->baoji) {
                //暴击
                t = Msg_WallBaoDamaged;
                damage *= 2;
            }
        }
        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                          agent->getID(),           //sender ID
                                                          wall->getID(),           //receiver ID
                                                          t,        //msg
                                                          &damage);
        attacking = false;
    });
}

void AttackState::enter(Character* agent)
{
//    agent->getSkeletonNode()->setTimeScale(1.0);
//    agent->getSkeletonNode()->setToSetupPose();
//    agent->getSkeletonNode()->setBonesToSetupPose();
//    agent->getSkeletonNode()->setSlotsToSetupPose();
    attacking = true;
    attackNum = 1;
    if (attackNum % 3 == 0) {
        bigAttack(agent);
    }else{
        attack(agent);
    }
    
//    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "attack", true);
//    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
//        //log("attack complete!");
//        BGTWall *wall = agent->getWorld()->getWall();
//        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
//                                    agent->getID(),           //sender ID
//                                    wall->getID(),           //receiver ID
//                                    Msg_WallDamaged,        //msg
//                                    NULL);
//    });
}

void AttackState::execute(Character* agent,float dt)
{
    if(!attacking){
        if (attackNum % 3 == 0) {
            bigAttack(agent);
        }else{
            attack(agent);
        }
    }
}

void AttackState::exit(Character* agent)
{
    
}

bool AttackState::onMessage(Character* agent, const Telegram& msg)
{
    if(msg.msg == Msg_AttackedByXuLiWeapon || msg.msg == Msg_AttackedByWeapon){
        Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
        MonsterData *data = agent->getMonsterData();
        //刀打空中怪物，枪打地上怪物可能触发闪避
        if ((data->shanbi > 0 && weapon->getType() == WeaponTypeKnife && agent->isCanFly()) || (data->shanbi > 0 && weapon->getType() == WeaponTypePistol && !agent->isCanFly())) {
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
        
        //蓄力攻击没有攻击力
        if (msg.msg == Msg_AttackedByWeapon){
            agent->takeDamage(weapon->getDamage());
            if (agent->getLife() <= 0) {
                agent->die();
                return false;
            }
        }
        switch (weapon->getType()) {
                agent->hitted();
            case WeaponTypeKnife:{
                //Knife *knife = (Knife*)weapon;
                
                KnifeAttackDirection direction = *(KnifeAttackDirection*)msg.extraInfo;
                if (msg.msg == Msg_AttackedByXuLiWeapon) {
                    if (direction == KnifeAttackDirectionUp) {
                        agent->flowup();
                    }else if (direction == KnifeAttackDirectionDown) {
                        agent->falldown();
                    }else if (direction == KnifeAttackDirectionRight) {
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
