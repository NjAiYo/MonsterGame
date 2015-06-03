//
//  GameConfiger.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#include "GameConfiger.h"

static GameConfiger *s_SharedManager = NULL;

GameConfiger::GameConfiger()
{
    
}

GameConfiger::~GameConfiger()
{
    
}

bool GameConfiger::init()
{
    return true;
}

GameConfiger* GameConfiger::getInstance()
{
    if (!s_SharedManager)
    {
        s_SharedManager = new GameConfiger();
        s_SharedManager->init();
    }
    
    return s_SharedManager;
}

#pragma mark 配置属性



