//
//  Player.cpp
//  Monster
//
//  Created by John Running on 15/4/29.
//
//

#include "Player.h"
#include "GameConfiger.h"

Player::~Player()
{

}

Player::Player()
:_id(0)
,_level(1)
,_score(0)
,_money(0)
,_exp(0)
,_caseCapbility(20)
{
    
}

bool Player::init(){


    return true;
}


/**
 * 用户在数据库中的Id
 */
unsigned int Player::getId()
{
    return _id;
}

void Player::setId(unsigned int value)
{
    _id = value;
}

/**
 * 用户昵称
 */
std::string Player::getName()
{
    return _name;
}

void Player::setName(const char* value)
{
    _name = value;
}

/**
 * 用户等级
 */
unsigned int Player::getLevel()
{
    return _level;
}

void Player::setLevel(unsigned int value)
{
    _level = value;
}

/**
 * 用户得分
 */
unsigned int Player::getScore()
{
    return _score;
}

void Player::setScore(unsigned int value)
{
    _score = value;
}

/**
 * 用户金钱
 */
unsigned int Player::getMoney()
{
    return _money;
}

void Player::setMoney(unsigned int value)
{
    _money = value;
}


/**
 * 用户的经验
 */
unsigned int Player::getExp()
{
    return _exp;
}

void Player::setExp(unsigned int value)
{
    _exp = value;
}

/**
 * 用户幸运值
 */
unsigned int Player::getLucky()
{
    float v = PlayerBaseLucky;
   
    for (Goods* goods : _goods) {
        for (GoodsProperty property : goods->properties) {
            if (property.type == GoodsPropertiesType_JiaXingYun) {
                v += property.value;
            }
        }
    }
    if (v > LuckyUpperLimit) {
        v = LuckyUpperLimit;
    }
    return v;
}

/**
 * 用户的箱子格子数量
 */
unsigned int Player::getCaseCapbility()
{
    return _caseCapbility;
}

void Player::setCaseCapbility(unsigned int value)
{
    _caseCapbility = value;
}

/**
 * 获取用户属性json字符串
 */
std::string Player::getPlayerPropertyJSONString()
{
    std::ostringstream str;
    str << "{";
    str << "'level':";
    str << _level;
    str << ",";
    
    str << "'score':";
    str << _score;
    str << ",";
    
    str << "'money':";
    str << _money;
    str << ",";
    
    str << "'exp':";
    str << _exp;
    str << ",";
    
    str << "'caseCapbility':";
    str << _caseCapbility;
    str << ",";
    
    str << "'power':";
    str << _power;
    str << ",";
    
    str << "'diamonds':";
    str << _diamonds;
    str << "}";
    return  str.str();
}

/**
 * 获取用户物品json字符串
 */
std::string Player::getPlayerGoodsJSONString()
{
    std::ostringstream str;
    str << "{";
    for (Goods* goods : _goods) {
        str << "'goodsId':";
        str << goods->goodsId;
        str << ",";
        str << "'properties':[";
        int count = 0;
        for (GoodsProperty property : goods->properties) {
            str << "{";
            str << "'type':";
            str << property.type;
            str << ",";
            str << "'value':";
            str << property.value;
            str << "}";
            if (count < goods->properties.size()-1) {
                str << ",";
            }
            count++;
        }
        str << "]";
        str << ",";
        
        //洞和洞里的物品
        str << "'holes':[";
        count = 0;
        for (Ref *kongThing : goods->kongArray) {
            Goods *diamond = dynamic_cast<Goods*>(kongThing);
            str << "{";
            str << "'goodsId':";
            if (diamond) {
                str << diamond->goodsId;
            }else{
                str << -1;
            }
            str << "}";
            if (count < goods->properties.size()-1) {
                str << ",";
            }
            count++;
        }
        str << "]";
    }
    str << "}";
    return  str.str();
}


/**
 * 添加物品,箱子满添加失败返回-1，其他失败返回-2，成功返回1
 */
int Player::addGoods(Goods *goods)
{
    if (_goods.size() >= _caseCapbility) {
        return -1;
    }
    _goods.pushBack(goods);
    EventCustom event("PlayerInfoUpdated");
    event.setUserData(this);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    return 1;
}

/**
 * 根据物品的id获取物品
 */
Goods* Player::getGoods(unsigned int id)
{
    for (Goods* goods : _goods) {
        if (goods->id == id) {
            return goods;
        }
    }
    return nullptr;
}

/**
 * 删除物品，其他失败返回-2，成功返回1
 */
void Player::deleteGoods(Goods *goods)
{
    _goods.eraseObject(goods);
    EventCustom event("PlayerInfoUpdated");
    event.setUserData(this);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

/**
 * 根据id删除物品
 */
void Player::deleteGoodsById(unsigned int id)
{
    Goods *toBeDeleteGoods = nullptr;
    for (Goods* goods : _goods) {
        if (goods->id == id) {
            toBeDeleteGoods = goods;
        }
    }
    if (toBeDeleteGoods) {
        deleteGoods(toBeDeleteGoods);
    }
}

/**
 * 获取玩家所有物品
 */
Vector<Goods*> Player::getGoodses()
{
    return _goods;
}
