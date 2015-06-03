//
//  SkillState.h
//  MonsterGame
//
//  Created by John Running on 15/6/2.
//
//

#ifndef __MonsterGame__SkillState__
#define __MonsterGame__SkillState__

#include "State.h"
class Character;
struct Telegram;

class SkillState : public State<Character>
{
private:
    float totalDamageTaked;
    bool charging;
    float chargeTime;
    //copy ctor and assignment should be private
    SkillState(const SkillState&);
    SkillState& operator=(const SkillState&);
    
public:
    explicit SkillState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__MonsterGame__SkillState__) */
