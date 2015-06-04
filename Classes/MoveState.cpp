//
//  MoveState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "MoveState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"
#include "Utils.h"
#include "BGTWall.h"
#include "AppDelegate.h"

void MoveState::enter(Character* agent)
{
    if (agent->getType() < 3) {
        agent->getSkeletonNode()->setTimeScale(1.5);
    }else{
        agent->getSkeletonNode()->setTimeScale(1.0);
    }
    agent->getSkeletonNode()->setToSetupPose();
    agent->getSkeletonNode()->setBonesToSetupPose();
    agent->getSkeletonNode()->setSlotsToSetupPose();
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, WalkAnimationName, true);
    agent->getSkeletonNode()->setTrackStartListener(entry, [] (int trackIndex) {
        //log("move start!");
    });
}

void MoveState::execute(Character* agent,float dt)
{
    //检测是否可以攻击门了
    BGTWall *wall = agent->getWorld()->getWall();
    bool canAttack = intersectCircleLine(agent->getPosition(), agent->getAttackRange(), wall->topPosition, wall->bottomPosition);
    
    if (canAttack) {
        agent->attack();
    }else if(agent->canSkill()){
        agent->skill();
    }else{
        float newX = agent->getPositionX();
        if (agent->getDirection() == CharacterDirectionLeft) {
            newX-=agent->getMoveSpeed()*dt;
        }else{
            newX+=agent->getMoveSpeed()*dt;
        }
        
        agent->setPositionX(newX);
    }
}

void MoveState::exit(Character* agent)
{
    agent->getSkeletonNode()->setTimeScale(1.0);
}

bool MoveState::onMessage(Character* agent, const Telegram& msg)
{
    //agent->flowup();
    if(msg.msg == Msg_AttackedByXuLiWeapon || msg.msg == Msg_AttackedByWeapon){
        Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
        
        MonsterData *data = agent->getMonsterData();
        //刀打空中怪物，枪打地上怪物可能触发闪避
        if ((data->shanbi > 0 && weapon->getType() == WeaponTypeKnife && agent->isflyer()) || (data->shanbi > 0 && weapon->getType() == WeaponTypePistol && !agent->isflyer())) {
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
//                agent->flowup();
//                return false;
                
                
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