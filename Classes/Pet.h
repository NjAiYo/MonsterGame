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

	int isqiyue;//��Լ1Ϊ����Լ0Ϊ����Լ
	int iszhuangbei;//�Ƿ�װ����1�ǣ�0����

	Item *material_A;
	int num_A;
	Item *material_B;
	int num_B;
	Item *material_C;
	int num_C;

	Pet();

};
#endif