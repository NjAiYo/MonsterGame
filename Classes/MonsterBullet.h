//
//  MonsterBullet.h
//  MonsterGame
//
//  Created by John Running on 15/6/4.
//
//

#ifndef __MonsterGame__MonsterBullet__
#define __MonsterGame__MonsterBullet__

#include "cocos2d.h"
#include "Utils.h"
#include "GameEntity.h"
#include "MessageDispatcher.h"

class BGTWall;
class BGTWorld;
class MonsterBullet : public GameEntity
{
protected:
    Sprite *skin;
    MessageDispatcher *dispatcher;
    Animation *bulletAnimation;
    Animation *bulletExplosionAnimation;
    bool paused;
    
    BGTWall *wall;
    
    CharacterType characterType;
    
    //飞行的y轴
    bool flying;
    bool explosioning;
public:
    virtual bool initWithWorld(BGTWorld *world);
    MonsterBullet();
    virtual ~MonsterBullet();
    bool  handleMessage(const Telegram& msg);
    void update(float dt);
    
    bool hittestPoint(Vec2 p);
    float radius;
    float flyY;
    float speed;
    float damage;
    float baoji;
    void fly();
    void explosion();
    
    CharacterType getType();
    void setType(CharacterType t);
    
    void die();
};
#endif /* defined(__MonsterGame__MonsterBullet__) */
