//
//  GameConfiger.h
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#ifndef __MonsterGame__GameConfiger__
#define __MonsterGame__GameConfiger__

#include "cocos2d.h"

USING_NS_CC;

#define PlayerBaseLucky 0.1
#define LuckyUpperLimit 0.4

//管理关卡

class GameConfiger : public cocos2d::Ref
{
public:
    

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    GameConfiger();
    virtual ~GameConfiger();
    virtual bool init();
    static GameConfiger* getInstance();
    
    /**
     *玩家基础幸运值
     */
    CC_SYNTHESIZE(float, _playerBaseLucky, PlayerBaseLucky);
    
    /**
     *幸运值上限
     */
    CC_SYNTHESIZE(float, _luckyUpperLimit, LuckyUpperLimit);
};


#endif /* defined(__MonsterGame__GameConfiger__) */
