//
//  GameEndUpgradeLayer.h
//  MonsterGame
//
//  Created by John Running on 15/6/3.
//
//

#ifndef __MonsterGame__GameEndUpgradeLayer__
#define __MonsterGame__GameEndUpgradeLayer__

#include "cocos2d.h"
#include "GameManager.h"
#include "cocos2dFilters.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameEndUpgradeLayer : public cocos2d::Layer
{
private:
    Sprite *endPanelLight;
    Sprite *upgredTip;
    Sprite *expIconSprite;
    void awardCallback(Ref* sender);
public:
    void showResultWithAnimation();
    GameEndUpgradeLayer();
    virtual bool init();
};

#endif /* defined(__MonsterGame__GameEndUpgradeLayer__) */
