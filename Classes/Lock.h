#ifndef __LOCK_H__
#define __LOCK_H__
#include "cocos2d.h"
USING_NS_CC;
class Lock:public Node
{
public:
	MenuItemImage *lockpic;
	std::string id;
	int MoneyKind;
	int MoneyNum;
	float scale;
	int isunLock;//0未解锁，1解锁
	int KIND;
	Lock(std::string id,int KIND);//1为宠物背包，2为人物背包
	void releaseself();
	void buttoncallback(Ref *pSender);
};
#endif
