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
     *物品Id
     */
    std::string id;
    
    /**
     *物品类型
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
     *稀有度
     */
    unsigned int rarerate;
    
    
    Vector<Dictionary*> properties;
    
    Goods();
};

#endif /* defined(__MonsterGame__Goods__) */
