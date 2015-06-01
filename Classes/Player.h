//
//  Player.h
//  Monster
//
//  Created by John Running on 15/4/29.
//
//

#ifndef __Monster__Player__
#define __Monster__Player__

#include "cocos2d.h"
#include <map>

USING_NS_CC;

class Player : public cocos2d::Ref
{
private:
    unsigned int _id;
    std::string _name;
    unsigned int _level;
    unsigned int _score;
    unsigned int _money;
    unsigned int _exp;
    
    /**
     * 用户的物品
     */
    Vector<Dictionary*> _items;
    
public:
    ~Player();
    Player();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Player);
    
    /**
     * 用户在数据库中的Id
     */
    unsigned int getId();
    void setId(unsigned int value);
    
    /**
     * 用户昵称
     */
    std::string getName();
    void setName(const char* value);
    
    /**
     * 用户等级
     */
    unsigned int getLevel();
    void setLevel(unsigned int value);
    
    /**
     * 用户得分
     */
    unsigned int getScore();
    void setScore(unsigned int value);
    
    /**
     * 用户金钱
     */
    unsigned int getMoney();
    void setMoney(unsigned int value);
    
    
    /**
     * 用户的经验
     */
    unsigned int getExp();
    void setExp(unsigned int value);
    
    /**
     * 用户幸运值
     */
    unsigned int getLucky();
    void setLucky(unsigned int value);
    
    
    /**
     * 获取用户属性json字符串
     */
    std::string getPlayerPropertyJSONString();
};

#endif /* defined(__Monster__Player__) */
