//
//  QTELayer.h
//  MonsterGame
//
//  Created by John Running on 15/5/6.
//
//

#ifndef __MonsterGame__QTELayer__
#define __MonsterGame__QTELayer__

#include "cocos2d.h"
#include "GameManager.h"
#include "QTEMonster.h"

USING_NS_CC;

class BGTWorld;

class QTELayer : public cocos2d::Node
{
private:
    LayerColor *bgLayer;
    BGTWorld *world;
    QTEMonster *qteMonster;
    MotionStreak* streak;
    Vec2 startTouchPosition;
    double currentTouchTime;
    
    Sprite *bar;
    ProgressTimer *progressBar;
    Sprite *qteMark;
    Label *countDownLabel;
    int countDownTime;
    void startFight();
    bool enableFight;
    float percentage;
    
    float monsterDamage,playerDamage;
public:
    QTELayer();
    bool initWithWorld(BGTWorld *w);
    void countDown(float dt);
    
    //qte怪物进攻
    void qteAttacked();
    //玩家打到qte怪物
    void hitQteMonster();
    
    
    
    QTEMonster* getQteMonster();

    
//    bool onTouchBegan(Touch* touch, Event* event);
//    void onTouchMoved(Touch* touch, Event* event);
//    void onTouchEnded(Touch* touch, Event* event);
//    void onTouchCancelled(Touch *touch, Event *unused_event);
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
    void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    
    void qteBegin();
    void qteEnd();
    
    void setMonsterType(CharacterType t);
};

#endif /* defined(__MonsterGame__QTELayer__) */
