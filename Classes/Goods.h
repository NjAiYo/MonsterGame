//
//  Goods.h
//  MonsterGame
//
//  Created by 南京艾游网络文化有限公司 on 15/6/1.
//
//

#ifndef __MonsterGame__Goods__
#define __MonsterGame__Goods__

#include "cocos2d.h"
#include "Utils.h"

USING_NS_CC;
class Goods:public Ref
{
public:
    /**
     *物品Id,用于数据库
     */
    unsigned int id;
    
    /**
     *物品Id,用于确定这是具体什么物品
     */
    std::string goodsId;
    
    /**
     *物品类型，物品的大分类
     */
    GoodsType type;
    
    /**
     *物品售价
     */
    unsigned int salePrice;
    
    /**
     *物品买入价
     */
    unsigned int buyPrice;

    /**
     *名称
     */
    std::string name;
    
    /**
     *说明
     */
    std::string detail;
    
    /**
     *物品cd，比如血瓶
     */
    float cd;
    
    
    /**
     *等级
     */
    unsigned int level;
    
    
    /**
     *玩家使用的最低等级要求，宝石则是对武器的最低等级要求
     */
    unsigned int minLevelToUse;
    
    /**
     *稀有度
     */
    unsigned int rarerate;
    
    
    /**
     *物品属性,
     */
    std::vector<GoodsProperty> properties;
    
    
    /**
     *物品的孔，内容是宝石,Ref对象表示空孔，宝石Goods对象表示一个宝石
     */
    Vector<Ref*> kongArray;
    Goods();
};

#endif /* defined(__MonsterGame__Goods__) */
