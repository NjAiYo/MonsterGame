#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__
#include "cocos2d.h"
USING_NS_CC;
class Item;
class ItemData:public Node
{
public :
	Vector<Item *>Allbagitemvec; 
	static ItemData* getInstance();
	void additem(Item *item);
	void deleteitem(const char *id);
	//��ȡ�������е���
	//...
	void initrecorddata();//��ʼ���浵�еĵ�������

private :
	static ItemData *_bagsystem;
};

#endif