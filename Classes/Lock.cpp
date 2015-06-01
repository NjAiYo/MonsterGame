#include "Lock.h"
#include "CsvUtil.h"
#include "PetBag.h"
#include "Gamepanel.h"
Lock::Lock(std::string id,int KIND)
{
	this->KIND=KIND;
	if(KIND==1)
	{
		const char *path="petbagLock.csv";
		CsvUtil::getInstance()->loadFile(path);
		int line=CsvUtil::getInstance()->findValueInWithLine(id.c_str(),0,path);
		Value t1=CsvUtil::getInstance()->getValue(line,1,path);
		Value t2=CsvUtil::getInstance()->getValue(line,2,path);
		MoneyKind=t1.asInt();
		MoneyNum=t2.asInt();
		lockpic=MenuItemImage::create("","",CC_CALLBACK_1(Lock::buttoncallback, this));
		lockpic->setNormalImage(Sprite::createWithSpriteFrameName("suo1.png"));
		lockpic->setSelectedImage(Sprite::createWithSpriteFrameName("suo1.png"));
		lockpic->retain();
	}
	else if(KIND==2)
	{
		const char *path="bagLock.csv";
		CsvUtil::getInstance()->loadFile(path);
		int line=CsvUtil::getInstance()->findValueInWithLine(id.c_str(),0,path);
		Value t1=CsvUtil::getInstance()->getValue(line,1,path);
		Value t2=CsvUtil::getInstance()->getValue(line,2,path);
		MoneyKind=t1.asInt();
		MoneyNum=t2.asInt();
		lockpic=MenuItemImage::create("","",CC_CALLBACK_1(Lock::buttoncallback, this));
		lockpic->setNormalImage(Sprite::createWithSpriteFrameName("suo1.png"));
		lockpic->setSelectedImage(Sprite::createWithSpriteFrameName("suo1.png"));
		lockpic->retain();
	}
}

void Lock::releaseself()
{
	lockpic->removeFromParent();
	lockpic->release();
}

void Lock::buttoncallback(Ref *pSender)
{
	if(KIND==1)
		PetBag::getInstance()->jiesuoBag();
	else
		Gamepanel::gamepanel->jiesuoBag();
	log("%d",MoneyNum);
}