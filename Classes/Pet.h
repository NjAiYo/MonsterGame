#ifndef __PET_H__
#define __PET_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Pet:public Node
{
public:
	string petid;
	string petname;
	string petdescription;
	string picname;
	string petbodypic;
	int HP;
	int Power;
	int Defend;
	int Speed;
	int Kind;
	string Addproperty1_ID;
	string Addproperty2_ID;
	float Addproperty1;
	float Addproperty2;

	int isqiyue;//��Լ1Ϊ����Լ0Ϊ����Լ
	int iszhuangbei;//�Ƿ�װ����1�ǣ�0����

	int rarerate;

	string material_A;
	int num_A;
	string material_B;
	int num_B;
	string material_C;
	int num_C;

	int isSelect;
	Sprite *selectpic,*epic,*qypic,*kuangzi;

	MenuItemImage *pic;
	Pet(std::string id);
	void buttoncallback(Ref *pSender);

};
#endif