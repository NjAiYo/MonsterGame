#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__
#include "cocos2d.h"
#include "Lock.h"
USING_NS_CC;
class Item;

class ItemData:public Node
{
public :
	Vector<Item *>Allbagitemvec; 
	Vector<Lock *>baglockvec;
	static ItemData* getInstance();
    virtual bool init();
	void additem(Item *item);
	void deleteitem(const char *id);
	//获取背包所有道具
	//...
	void initrecorddata();//初始化存档中的道具数据

private :
	static ItemData *_bagsystem;
};

#endif