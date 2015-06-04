//
//  PauseLayer.h
//  MonsterGame
//
//  Created by John Running on 15/6/4.
//
//

#ifndef __MonsterGame__PauseLayer__
#define __MonsterGame__PauseLayer__

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class PauseLayer : public cocos2d::Layer
{
private:
    void restartCallback(Ref* sender);
    void mainCallback(Ref* sender);
    void resumeCallback(Ref* sender);
    bool needEatTouch;
public:
    bool onTouchBegan(Touch* touch, Event* event);
    PauseLayer();
    virtual bool init();
    void showResultWithAnimation();
    
    void show();
    void hide();
};


#endif /* defined(__MonsterGame__PauseLayer__) */
