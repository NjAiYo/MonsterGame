#ifndef __ITEMCREATOR_H__
#define __ITEMCREATOR_H__
#include "cocos2d.h"


typedef enum {
	WeaponDataType_GUN = 0,//ǹ
	WeaponDataType_KNIFE = 1,//��
	WeaponDataType_PET = 2//����
}WeaponDataType;

typedef enum {
	ArmorDataType_RING = 10,//��ָ
	WeaponDataType_NECKLACE = 11//����
}ArmorDataType;

typedef enum {
	StuffDataType_NORMAL = 20//�������
}StuffDataType;

typedef enum {
	ConsumeDataType_LIFE = 30,//Ѫ
	ConsumeDataType_ENERGY = 31,//����
	ConsumeDataType_BULLET = 32,//�ӵ�
	ConsumeDataType_MONEY = 33,//Ǯ
	ConsumeDataType_EXP = 34,//����
	ConsumeDataType_RESETSKILL = 35//����ϴ��
}ConsumeDataType;

typedef enum {
	BuffDataType_HOLE = 40,//���
	BuffDataType_GEM = 41//��ʯ
}BuffDataType;//��ǿ����װ����

typedef enum {
	BuffDataType_FULLHIT = 50,//ȫ�����
	BuffDataType_RECOVERYLIFE = 51,//����ʯ
	BuffDataType_ENERGYSHIELD = 52//��������
}SkillDataType;//���ܵ���

class Item;
class ItemCreator:public cocos2d::Node
{
public:
	static ItemCreator* getInstance();
	void createItem_normal(const char *id);//�������Զѵ��ĵ���
	void createItem_unique(int level,int kind,int rarerate);//�������ɶѵ��ĵ���
	bool ishave(const char *id);
private:
	static ItemCreator *_itemcreator;
};
#endif