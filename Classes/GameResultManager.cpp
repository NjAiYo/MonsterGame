//
//  GameResultManager.cpp
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#include "GameResultManager.h"

static GameResultManager *s_SharedManager = NULL;

GameResultManager::GameResultManager()
{
    
}

GameResultManager::~GameResultManager()
{

}

bool GameResultManager::init()
{

    return true;
}

GameResultManager* GameResultManager::getInstance()
{
    if (!s_SharedManager)
    {
        s_SharedManager = new GameResultManager();
        s_SharedManager->init();
    }
    
    return s_SharedManager;
}

