#ifndef __PET_H__
#define __PET_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Item;
class Pet:public Node
{
public:
	string name;
	int HP;
	int Power;
	int Defend;
	int Speed;
	int Kind;

	int isqiyue;//契约1为有契约0为无契约
	int iszhuangbei;//是否装备中1是，0否则

	Item *material_A;
	int num_A;
	Item *material_B;
	int num_B;
	Item *material_C;
	int num_C;

	Pet();

};
#endif