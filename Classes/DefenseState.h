//
//  DefenseState.h
//  MonsterGame
//
//  Created by John Running on 15/5/4.
//
//

#ifndef __MonsterGame__DefenseState__
#define __MonsterGame__DefenseState__

#include "State.h"
class Character;
struct Telegram;

class DefenseState : public State<Character>
{
private:
    
    float defenseTime;
    bool ending;
    //copy ctor and assignment should be private
    DefenseState(const DefenseState&);
    DefenseState& operator=(const DefenseState&);
    
public:
    explicit DefenseState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__MonsterGame__DefenseState__) */
