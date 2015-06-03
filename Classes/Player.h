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
#include "Goods.h"
#include <map>

USING_NS_CC;

class Player : public cocos2d::Ref
{
private:
    /**
     * 用户的属性
     */
    unsigned int _id;
    std::string _name;
    unsigned int _level;
    unsigned int _score;
    unsigned int _money;
    unsigned int _exp;
    unsigned int _caseCapbility;

    /**
     * 用户的物品
     */
    Vector<Goods*> _goods;
    
public:
    ~Player();
    Player();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Player);
    
    /**
     * 体力
     */
    CC_SYNTHESIZE(unsigned int, _power, Power);
    
    /**
     * 宝石
     */
    CC_SYNTHESIZE(unsigned int, _diamonds, Diamonds);
    
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
    
    /**
     * 用户的箱子格子数量
     */
    unsigned int getCaseCapbility();
    void setCaseCapbility(unsigned int value);
    
    /**
     * 获取用户属性json字符串
     */
    std::string getPlayerPropertyJSONString();
    
    
    /**
     * 获取用户物品json字符串
     */
    std::string getPlayerGoodsJSONString();
    
    /**
     * 添加物品,箱子满添加失败返回-1，其他失败返回-2，成功返回1
     */
    int addGoods(Goods *goods);
    
    /**
     * 根据物品的id获取物品
     */
    Goods* getGoods(unsigned int id);
    
    /**
     * 删除物品，物品不存在返回-1，其他失败返回-2，成功返回1
     */
    void deleteGoods(Goods *goods);
    
    /**
     * 根据id删除物品，物品不存在返回-1，其他失败返回-2，成功返回1
     */
    void deleteGoodsById(unsigned int id);
    
    /**
     * 获取玩家所有物品
     */
    Vector<Goods*> getGoodses();
};

#endif /* defined(__Monster__Player__) */
