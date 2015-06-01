#include "TalentPoint.h"
#include "Gamepanel.h"
#include "Hero.h"
USING_NS_CC;
TalentPoint::TalentPoint(int id,std::string talentdetail,std::string talentpicname,int needpoints,float addvalue,int uselevel)
{
	this->state=-1;
	this->id=id;
	this->talentdetail=talentdetail;
	this->talentpicname=talentpicname;
	this->needpoints=needpoints;
	this->addvalue=addvalue;
	this->uselevel=uselevel;
	this->currentpoints=this->needpoints;
	pic=MenuItemImage::create("","",CC_CALLBACK_1(TalentPoint::buttoncallback,this));
	pic->setNormalImage(Sprite::createWithSpriteFrameName(talentpicname));
	pic->setSelectedImage(Sprite::createWithSpriteFrameName(talentpicname));
	pic->setDisabledImage(Sprite::createWithSpriteFrameName("tfsddt.png"));
	pic->retain();
	if(Hero::getInstance()->level<uselevel)
		pic->setEnabled(false);

}

void TalentPoint::buttoncallback(Ref* pSender)
{
	Gamepanel::gamepanel->Layer_D->removeAllChildren();
	
	auto di=Sprite::createWithSpriteFrameName("tfxqk.png");
	Point p=Gamepanel::gamepanel->menuitem->convertToWorldSpace(pic->getPosition());
	di->setPosition(Vec2(p.x-320*Gamepanel::scaleFactory,p.y));
	di->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_D->addChild(di);

	auto lb=Label::create(talentdetail,"",50);
	lb->setPosition(Vec2(di->getContentSize().width/2,di->getContentSize().height/2));
	lb->setColor(Color3B::GREEN);
	di->addChild(lb);

	auto qd=MenuItemImage::create("","",CC_CALLBACK_1(TalentPoint::opentalent,this));
	qd->setNormalImage(Sprite::createWithSpriteFrameName("kqtf1.png"));
	qd->setSelectedImage(Sprite::createWithSpriteFrameName("kqtf1.png"));
	qd->setDisabledImage(Sprite::createWithSpriteFrameName("kqtf2.png"));
	qd->setPosition(Vec2(Vec2(di->getContentSize().width/2,di->getContentSize().height/2-200*Gamepanel::scaleFactory)));
	if(state==1||Hero::getInstance()->skillpoint<=0)
	{
		qd->setEnabled(false);
	}

	auto menu=Menu::create(qd,NULL);
	menu->setPosition(Vec2::ZERO);
	di->addChild(menu);

}

void TalentPoint::opentalent(Ref *pSender)
{
	if(state==1||Hero::getInstance()->skillpoint<=0)
		return ;
	currentpoints--;
	Hero::getInstance()->skillpoint--;
	if(needpoints==1)
	{
		if(currentpoints==0)
			state=1;
		Hero::getInstance()->tianfuface();
	}
	else
	{
		if(currentpoints==1)
		{
			state=0;
			Hero::getInstance()->tianfuface();
		}
		else if(currentpoints==0)
		{
			state=1;
			Hero::getInstance()->tianfuface();
		}
	}
}