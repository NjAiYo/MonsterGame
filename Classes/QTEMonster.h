//
//  QTEMonster.h
//  MonsterGame
//
//  Created by John Running on 15/5/4.
//
//

#ifndef __MonsterGame__QTEMonster__
#define __MonsterGame__QTEMonster__

#include "GameEntity.h"

#include <spine/spine-cocos2dx.h>
USING_NS_CC;
using namespace spine;

class QTELayer;

class QTEMonster : public Node
{
private:
    spine::SkeletonAnimation *skeletonNode;
    float characterScaleFactor;
    CharacterType type;

    QTELayer *layer;
    int attackNum;
public:
    QTEMonster();
    virtual ~QTEMonster();
    virtual bool initWithQTELayerAndType(QTELayer *l,CharacterType t);
    
    void die();
    void reset();
    void attack();
    void beginAttack();
    void stand();
    void setType(CharacterType d);
    CharacterType getType();
    bool hittestPoint(Vec2 p);
    
    void update(float dt);
    
    bool  handleMessage(const Telegram& msg);
};

#endif /* defined(__MonsterGame__QTEMonster__) */
