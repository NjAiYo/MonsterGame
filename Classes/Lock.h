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
	int isunLock;//0δ������1����
	int KIND;
	Lock(std::string id,int KIND);//1Ϊ���ﱳ����2Ϊ���ﱳ��
	void releaseself();
	void buttoncallback(Ref *pSender);
};
#endif
