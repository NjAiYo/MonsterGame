#include "Pet.h"
#include "CsvUtil.h"
#include "Item.h"
#include "PetBag.h"
Pet::Pet(std::string id)
{
	const char *path="pet.csv";
	
	CsvUtil::getInstance()->loadFile(path);
	int line=CsvUtil::getInstance()->findValueInWithLine(id.c_str(),0,path);
	
	Value t1=CsvUtil::getInstance()->getValue(line,1,path);
	Value t2=CsvUtil::getInstance()->getValue(line,2,path);
	Value t3=CsvUtil::getInstance()->getValue(line,3,path);
	Value t4=CsvUtil::getInstance()->getValue(line,4,path);
	Value t5=CsvUtil::getInstance()->getValue(line,5,path);
	Value t6=CsvUtil::getInstance()->getValue(line,6,path);
	Value t7=CsvUtil::getInstance()->getValue(line,7,path);
	Value t8=CsvUtil::getInstance()->getValue(line,8,path);
	Value t9=CsvUtil::getInstance()->getValue(line,9,path);
	Value t10=CsvUtil::getInstance()->getValue(line,10,path);
	Value t11=CsvUtil::getInstance()->getValue(line,11,path);
	Value t12=CsvUtil::getInstance()->getValue(line,12,path);
	Value t13=CsvUtil::getInstance()->getValue(line,13,path);
	Value t14=CsvUtil::getInstance()->getValue(line,14,path);
	Value t15=CsvUtil::getInstance()->getValue(line,15,path);
	Value t16=CsvUtil::getInstance()->getValue(line,16,path);
	Value t17=CsvUtil::getInstance()->getValue(line,17,path);
	Value t18=CsvUtil::getInstance()->getValue(line,18,path);
	Value t19=CsvUtil::getInstance()->getValue(line,19,path);


	
	this->petid=id;
	this->petname=t1.asString();
	this->picname=t2.asString();
	this->petdescription=t3.asString();
	this->HP=t4.asInt();
	this->Power=t5.asInt();
	this->Defend=t6.asInt();
	this->Speed=t7.asInt();
	this->Kind=t8.asInt();

	this->Addproperty1_ID=t9.asString();
	this->Addproperty1=t10.asFloat();

	this->Addproperty2_ID=t11.asString();
	this->Addproperty2_ID=t12.asFloat();

	this->material_A=t13.asString();
	this->num_A=t14.asInt();

	this->material_B=t15.asString();
	this->num_B=t16.asInt();

	this->material_C=t17.asString();
	this->num_C=t18.asInt();
	
	this->petbodypic=t19.asString();

	isqiyue=0;//契约1为有契约0为无契约
	iszhuangbei=0;//是否装备中1是，0否则
	isSelect=0;
	rarerate=1;
	pic=MenuItemImage::create("","",CC_CALLBACK_1(Pet::buttoncallback, this));
	pic->setNormalImage(Sprite::create(picname));
	pic->setSelectedImage(Sprite::create(picname));
	pic->retain();
	if(rarerate==1)
	{
		kuangzi=Sprite::createWithSpriteFrameName("lan2.png");
		kuangzi->setPosition(Vec2(pic->getContentSize().width/2,pic->getContentSize().height/2));
		kuangzi->setScale(0.9);
		pic->addChild(kuangzi);
	}
	else if(rarerate==2)
	{
		kuangzi=Sprite::createWithSpriteFrameName("lan2.png");
		kuangzi->setPosition(Vec2(pic->getContentSize().width/2,pic->getContentSize().height/2));
		kuangzi->setScale(0.9);
		pic->addChild(kuangzi);
	}
	else if(rarerate==3)
	{
		kuangzi=Sprite::createWithSpriteFrameName("lan2.png");
		kuangzi->setPosition(Vec2(pic->getContentSize().width/2,pic->getContentSize().height/2));
		kuangzi->setScale(0.9);
		pic->addChild(kuangzi);
	}

}

void Pet::buttoncallback(Ref *pSender)
{
	for(int i=0;i<PetBag::getInstance()->petbagVec.size();i++)
	{
		PetBag::getInstance()->petbagVec.at(i)->isSelect=0;
		PetBag::getInstance()->petbagVec.at(i)->pic->removeChild(PetBag::getInstance()->petbagVec.at(i)->selectpic);
	}
	isSelect=1;
	selectpic=Sprite::createWithSpriteFrameName("faguang.png");
	selectpic->setPosition(Vec2(pic->getContentSize().width/2,pic->getContentSize().height/2));
	pic->addChild(selectpic,-1);
	PetBag::getInstance()->setCurrentPet(this);

	if(PetBag::getInstance()->isshuxingface==1)
	{
		PetBag::getInstance()->shuxingface();
	}
	else if(PetBag::getInstance()->isjinengface==1)
	{

	}
	else if(PetBag::getInstance()->isjinjieface==1)
	{

	}

	
}
