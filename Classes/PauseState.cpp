//
//  PauseState.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/2.
//
//

#include "PauseState.h"

#include "Character.h"
#include <SimpleAudioEngine.h>
#include "GameEntityManager.h"
#include "Weapon.h"
#include "MessageDispatcher.h"
#include "BGTWall.h"

void PauseState::enter(Character* agent)
{
    agent->pause();
}

void SkillState::execute(Character* agent,float dt)
{
    
}

void SkillState::exit(Character* agent)
{
    agent->resume();
}

bool SkillState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
