//
//  GameResultManager.h
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#ifndef __MonsterGame__GameResultManager__
#define __MonsterGame__GameResultManager__

#include "cocos2d.h"

USING_NS_CC;

//管理一场战斗的结果数据

class GameResultManager : public cocos2d::Ref
{
private:
    
    GameResultManager(const GameResultManager &);
    GameResultManager& operator=(const GameResultManager &);
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    GameResultManager();
    virtual ~GameResultManager();
    virtual bool init();
    static GameResultManager* getInstance();
    
};


#endif /* defined(__MonsterGame__GameResultManager__) */
