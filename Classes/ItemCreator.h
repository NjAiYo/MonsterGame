#ifndef __ITEMCREATOR_H__
#define __ITEMCREATOR_H__
#include "cocos2d.h"


typedef enum {
	WeaponDataType_GUN = 0,//枪
	WeaponDataType_KNIFE = 1,//刀
	WeaponDataType_PET = 2//宠物
}WeaponDataType;

typedef enum {
	ArmorDataType_RING = 10,//戒指
	WeaponDataType_NECKLACE = 11//项链
}ArmorDataType;

typedef enum {
	StuffDataType_NORMAL = 20//锻造材料
}StuffDataType;

typedef enum {
	ConsumeDataType_LIFE = 30,//血
	ConsumeDataType_ENERGY = 31,//能量
	ConsumeDataType_BULLET = 32,//子弹
	ConsumeDataType_MONEY = 33,//钱
	ConsumeDataType_EXP = 34,//经验
	ConsumeDataType_RESETSKILL = 35//技能洗点
}ConsumeDataType;

typedef enum {
	BuffDataType_HOLE = 40,//打孔
	BuffDataType_GEM = 41//宝石
}BuffDataType;//增强武器装备的

typedef enum {
	BuffDataType_FULLHIT = 50,//全屏打击
	BuffDataType_RECOVERYLIFE = 51,//复活石
	BuffDataType_ENERGYSHIELD = 52//能量护盾
}SkillDataType;//技能道具

class Item;
class ItemCreator:public cocos2d::Node
{
public:
	static ItemCreator* getInstance();
	void createItem_normal(const char *id);//产生可以堆叠的道具
	void createItem_unique(int level,int kind,int rarerate);//产生不可堆叠的道具
	bool ishave(const char *id);
private:
	static ItemCreator *_itemcreator;
};
#endif