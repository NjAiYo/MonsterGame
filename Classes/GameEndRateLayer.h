//
//  GameEndRateLayer.h
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#ifndef __MonsterGame__GameEndRateLayer__
#define __MonsterGame__GameEndRateLayer__

#include "cocos2d.h"
#include "GameManager.h"
#include "cocos2dFilters.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameEndRateLayer : public cocos2d::Layer
{
private:
    void restartCallback(Ref* sender);
    void sureCallback(Ref* sender);
    Label *comboLabel;
    Label *lifeLabel;
    Label *timeLabel;
    Label *expLabel;
    Label *moneyLabel;
    Label *levelLabel;
    bool needEatTouch;
public:
    bool onTouchBegan(Touch* touch, Event* event);
    GameEndRateLayer();
    virtual bool init();
    void showResultWithAnimation();
    void show();
    void hide();
};


#endif /* defined(__MonsterGame__GameEndRateLayer__) */
