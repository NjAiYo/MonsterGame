//
//  Player.cpp
//  Monster
//
//  Created by John Running on 15/4/29.
//
//

#include "Player.h"

Player::~Player()
{
    
}

Player::Player()
:id(0)
,level(1)
,score(0)
,money(0)
{
    
}

bool Player::init(){
    Dictionary *dict = Dictionary::create();
    dict->setObject(<#cocos2d::Ref *pObject#>, <#const std::string &key#>)


    return true;
}
