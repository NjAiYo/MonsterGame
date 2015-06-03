//
//  PauseState.h
//  MonsterGame
//
//  Created by John Running on 15/6/2.
//
//

#ifndef __MonsterGame__PauseState__
#define __MonsterGame__PauseState__

#include "State.h"
class Character;
struct Telegram;

class PauseState : public State<Character>
{
private:
    //copy ctor and assignment should be private
    PauseState(const PauseState&);
    PauseState& operator=(const PauseState&);
    
public:
    explicit PauseState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};


#endif /* defined(__MonsterGame__PauseState__) */
