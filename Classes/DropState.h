//
//  DropState.h
//  MonsterGame
//
//  Created by John Running on 15/6/4.
//
//

#ifndef __MonsterGame__DropState__
#define __MonsterGame__DropState__

#include "State.h"
class Character;
struct Telegram;

class DropState : public State<Character>
{
private:
    //copy ctor and assignment should be private
    DropState(const DropState&);
    DropState& operator=(const DropState&);
    float dropSpeed;
    float targetX,targetY;
    float radians;
    float ay;
public:
    explicit DropState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__MonsterGame__DropState__) */
