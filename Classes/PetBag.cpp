#include "PetBag.h"
#include "Gamepanel.h"
#include "Pet.h"
#include "Lock.h"
#include "Hero.h"
#include "GamepanelHeader.h"

PetBag *PetBag::petbag=nullptr;
PetBag *PetBag::getInstance()
{
	if(petbag==nullptr)
	{
		petbag=new PetBag();
        if(petbag&&petbag->init())
        {
            petbag->autorelease();
            petbag->retain();
        }
        else
        {
            CC_SAFE_DELETE(petbag);
            petbag=nullptr;
        }
	}
	return petbag;
}

bool PetBag::init()
{
    return true;
}

void PetBag::initPetBagData()
{
	isshuxingface=1;
	isjinengface=0;
	isjinjieface=0;
	petBagcapacitance=6;
	char temp[5];
	for(int i=6;i<45;i++)//i=6为vec中的第1个
	{
		sprintf(temp,"%d",i+1);//i+1=7为文件中的第1个
		Lock *lk=new Lock(temp,1);
		petbaglockvec.pushBack(lk);//vec中的依旧从0开始上述用于创建，谨防混淆。
	}


	addPet("cw1");
	addPet("cw1");
}

void PetBag::initPetFace()
{
	if(Gamepanel::LayerSwitch_A==0)
	{
		Gamepanel::LayerSwitch_A=1;
		Gamepanel::gamepanel->Layer_A=Node::create();
		Gamepanel::gamepanel->addChild(Gamepanel::gamepanel->Layer_A);

		if(Gamepanel::LayerSwitch_B==0)
		{
			Gamepanel::LayerSwitch_B=1;
			Gamepanel::gamepanel->Layer_B=Node::create();
			Gamepanel::gamepanel->Layer_A->addChild(Gamepanel::gamepanel->Layer_B,3);
		}

		if(Gamepanel::LayerSwitch_C==0)
		{
			Gamepanel::LayerSwitch_C=1;
			Gamepanel::gamepanel->Layer_C=Node::create();
			Gamepanel::gamepanel->Layer_A->addChild(Gamepanel::gamepanel->Layer_C,5);
		}

		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto mask=Sprite::create("mask.png");
		mask->setScale(100);
        Gamepanel::gamepanel->Layer_A->addChild(mask);

		auto petbg=Sprite::createWithSpriteFrameName("ditu1.png");
		petbg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
		petbg->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(petbg);
        
		auto title=Sprite::createWithSpriteFrameName("biaotibeijing.png");
		title->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+550*Gamepanel::scaleFactory));
		auto tiletext=Sprite::createWithSpriteFrameName("chongwutuqian.png");
		tiletext->setPosition(Vec2(title->getContentSize().width/2,title->getContentSize().height/2));
		title->addChild(tiletext);
		title->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(title);

		anniudi=Sprite::createWithSpriteFrameName("k3.png");
		anniudi->setPosition(Vec2(1434*Gamepanel::scaleFactory,975*Gamepanel::scaleFactory));
		anniudi->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(anniudi);

		auto neirongdi=Sprite::createWithSpriteFrameName("neirongdi.png");
		neirongdi->setPosition(Vec2(1430*Gamepanel::scaleFactory,512*Gamepanel::scaleFactory));
		neirongdi->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(neirongdi,2);

		auto esc=MenuItemImage::create("","",CC_CALLBACK_1(PetBag::allbuttoncallback,this));
		esc->setNormalImage(Sprite::createWithSpriteFrameName("guanbi.png"));
		esc->setSelectedImage(Sprite::createWithSpriteFrameName("guanbi.png"));
		esc->setPosition(Vec2(1020*2*Gamepanel::scaleFactory,550*2*Gamepanel::scaleFactory));
		esc->setScale(Gamepanel::scaleFactory);
		esc->setTag(PetBagType_ESC);

		shuxing=MenuItemImage::create("","",CC_CALLBACK_1(PetBag::allbuttoncallback,this));
		shuxing->setNormalImage(Sprite::createWithSpriteFrameName("sx1.png"));
		shuxing->setSelectedImage(Sprite::createWithSpriteFrameName("sx1.png"));
		shuxing->setDisabledImage(Sprite::createWithSpriteFrameName("sx2.png"));
		shuxing->setPosition(Vec2(1053*Gamepanel::scaleFactory,967*Gamepanel::scaleFactory));
		shuxing->setScale(Gamepanel::scaleFactory);
		shuxing->setTag(PetBagType_SHUXING);
		shuxing->setEnabled(false);

		jineng=MenuItemImage::create("","",CC_CALLBACK_1(PetBag::allbuttoncallback,this));
		jineng->setNormalImage(Sprite::createWithSpriteFrameName("jineng1.png"));
		jineng->setSelectedImage(Sprite::createWithSpriteFrameName("jineng1.png"));
		jineng->setDisabledImage(Sprite::createWithSpriteFrameName("jineng2.png"));
		jineng->setPosition(Vec2(1446*Gamepanel::scaleFactory,967*Gamepanel::scaleFactory));
		jineng->setScale(Gamepanel::scaleFactory);
		jineng->setTag(PetBagType_JINENG);

		jinjie=MenuItemImage::create("","",CC_CALLBACK_1(PetBag::allbuttoncallback,this));
		jinjie->setNormalImage(Sprite::createWithSpriteFrameName("jinjie1.png"));
		jinjie->setSelectedImage(Sprite::createWithSpriteFrameName("jinjie1.png"));
		jinjie->setDisabledImage(Sprite::createWithSpriteFrameName("jinjie2.png"));
		jinjie->setPosition(Vec2(1839*Gamepanel::scaleFactory,967*Gamepanel::scaleFactory));
		jinjie->setScale(Gamepanel::scaleFactory);
		jinjie->setTag(PetBagType_JINJIE);

		auto menu=Menu::create(esc,shuxing,jineng,jinjie,NULL);
		menu->setPosition(Vec2::ZERO);
		Gamepanel::gamepanel->Layer_A->addChild(menu,2);

		Gamepanel::gamepanel->scrollView = extension::ScrollView::create();
		Gamepanel::gamepanel->continerLayer = Layer::create();
		Gamepanel::gamepanel->continerLayer->setAnchorPoint(Vec2(0,0));
		Gamepanel::gamepanel->continerLayer->setPosition(Vec2(0,0));
		Gamepanel::gamepanel->scrollView->setPosition(Vec2(145*Gamepanel::scaleFactory,164*Gamepanel::scaleFactory));
    
		Gamepanel::gamepanel->scrollView->setViewSize(Size(643*Gamepanel::scaleFactory, 887*Gamepanel::scaleFactory));
		Gamepanel::gamepanel->continerLayer->setContentSize(Size(643*Gamepanel::scaleFactory, 887*Gamepanel::scaleFactory+220*11*Gamepanel::scaleFactory));
		Gamepanel::gamepanel->continerLayer->setPosition(Vec2(0,-220*11*Gamepanel::scaleFactory));
		Gamepanel::gamepanel->scrollView->setContentSize(Gamepanel::gamepanel->continerLayer->getContentSize());
		Gamepanel::gamepanel->scrollView->setContainer(Gamepanel::gamepanel->continerLayer);
    
		Gamepanel::gamepanel->scrollView->setTouchEnabled(true);
		Gamepanel::gamepanel->scrollView->setDirection(extension::ScrollView::Direction::VERTICAL);
		Gamepanel::gamepanel->scrollView->setBounceable(true);
		Gamepanel::gamepanel->scrollView->setDelegate(Gamepanel::gamepanel);
		Gamepanel::gamepanel->Layer_A->addChild(Gamepanel::gamepanel->scrollView,1);

		Gamepanel::gamepanel->menuitem=Mymenu::create();
		Gamepanel::gamepanel->menuitem->setAnchorPoint(Vec2::ZERO);
		Gamepanel::gamepanel->menuitem->setPosition(Vec2::ZERO);
		Gamepanel::gamepanel->continerLayer->addChild(Gamepanel::gamepanel->menuitem,2);
       	for(int i=0;i<45;i++)
		{
			int x=i%3*100+60;
			int y=390-i/3*110;
			auto kuangzi=Sprite::createWithSpriteFrameName("wupinkuang.png");
			kuangzi->setScale(0.9*Gamepanel::scaleFactory);
			kuangzi->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+11*220*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->continerLayer->addChild(kuangzi,1);
			if(i+1>petBagcapacitance)
			{
				Lock *lk=petbaglockvec.at(i-petBagcapacitance);
				lk->lockpic->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+11*220*Gamepanel::scaleFactory));
				lk->lockpic->setScale(0.9*Gamepanel::scaleFactory);
				Gamepanel::gamepanel->menuitem->addChild(lk->lockpic);
				
			}
		}
	
		for(int i=0;i<petbagVec.size();i++)
		{
			int x=i%3*100+60;
			int y=390-i/3*110;
			Pet *p=petbagVec.at(i);
			p->pic->setScale(Gamepanel::scaleFactory);
			p->pic->setPosition(Vec2(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+11*220*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->menuitem->addChild(p->pic,1);
		}
	}
}

void PetBag::addPet(std::string id)
{
	Pet *pet=new Pet(id);
	petbagVec.pushBack(pet);
}

void PetBag::shuxingface()
{
	Gamepanel::gamepanel->Layer_B->removeAllChildren();

	auto dizuo=Sprite::createWithSpriteFrameName("dizuo.png");
	dizuo->setPosition(Vec2(1100*Gamepanel::scaleFactory,300*Gamepanel::scaleFactory));
	dizuo->setScale(Gamepanel::scaleFactory);
	auto yz=Sprite::createWithSpriteFrameName("yycw.png");
	yz->setPosition(Vec2(dizuo->getContentSize().width/2,dizuo->getContentSize().height/2));
	dizuo->addChild(yz);
	Gamepanel::gamepanel->Layer_B->addChild(dizuo);

	auto touxiang=Sprite::createWithSpriteFrameName(currentPet->petbodypic);
	touxiang->setPosition(Vec2(1100*Gamepanel::scaleFactory,550*Gamepanel::scaleFactory));
	touxiang->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_B->addChild(touxiang);

	auto msk=Sprite::createWithSpriteFrameName("miaoshuk.png");
	msk->setPosition(Vec2(1680*Gamepanel::scaleFactory,750*Gamepanel::scaleFactory));
	msk->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_B->addChild(msk);

	auto miaoshu=Sprite::createWithSpriteFrameName(currentPet->petdescription);
	miaoshu->setPosition(Vec2(1680*Gamepanel::scaleFactory,750*Gamepanel::scaleFactory));
	miaoshu->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_B->addChild(miaoshu);

	auto sxk=Sprite::createWithSpriteFrameName("sxk.png");
	sxk->setPosition(Vec2(1680*Gamepanel::scaleFactory,490*Gamepanel::scaleFactory));
	sxk->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_B->addChild(sxk);

	auto jiaqiyue=MenuItemImage::create("","",CC_CALLBACK_1(PetBag::allbuttoncallback,this));
	jiaqiyue->setNormalImage(Sprite::createWithSpriteFrameName("lhqy1.png"));
	jiaqiyue->setSelectedImage(Sprite::createWithSpriteFrameName("lhqy2.png"));
	jiaqiyue->setPosition(Vec2(1510*Gamepanel::scaleFactory,230*Gamepanel::scaleFactory));
	jiaqiyue->setScale(Gamepanel::scaleFactory);
	jiaqiyue->setTag(PetBagType_JIAQIYUE);

	auto jianqiyue=MenuItemImage::create("","",CC_CALLBACK_1(PetBag::allbuttoncallback,this));
	jianqiyue->setNormalImage(Sprite::createWithSpriteFrameName("jiechuqiyue1.png"));
	jianqiyue->setSelectedImage(Sprite::createWithSpriteFrameName("jiechuqiyue2.png"));
	jianqiyue->setPosition(Vec2(1850*Gamepanel::scaleFactory,230*Gamepanel::scaleFactory));
	jianqiyue->setScale(Gamepanel::scaleFactory);
	jianqiyue->setTag(PetBagType_JIANQIYUE);

	auto menu=Menu::create(jiaqiyue,jianqiyue,NULL);
	menu->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->Layer_B->addChild(menu);
}

void PetBag::jinengface()
{
	Gamepanel::gamepanel->Layer_B->removeAllChildren();
}

void PetBag::jinjieface()
{
	Gamepanel::gamepanel->Layer_B->removeAllChildren();
}

void PetBag::setCurrentPet(Pet *pet)
{
	currentPet=pet;
}

void PetBag::addqiyue()
{
	if(currentPet->iszhuangbei==1||currentPet->isqiyue==1)
		return;
	currentPet->isqiyue=1;
	currentPet->qypic=Sprite::create("qy.png");
	currentPet->qypic->setPosition(Vec2(currentPet->pic->getContentSize().width-50,currentPet->pic->getContentSize().height-20));
	currentPet->pic->addChild(currentPet->qypic);
}

void PetBag::cancelqiyue()
{
	if(currentPet->iszhuangbei==1||currentPet->isqiyue==0)
		return;
	currentPet->isqiyue=0;
	currentPet->pic->removeChild(currentPet->qypic);
}
void PetBag::jiesuoBag()
{	
	Gamepanel::gamepanel->Layer_C->removeAllChildren();

	auto mask=Sprite::create("mask.png");
	mask->setScale(100);
	Gamepanel::gamepanel->Layer_C->addChild(mask);

	auto buybg=Sprite::create("buybg.png");
	buybg->setScale(Gamepanel::scaleFactory);
	buybg->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2));
	Gamepanel::gamepanel->Layer_C->addChild(buybg);

	auto buywords=Sprite::create("buywords.png");
	buywords->setScale(Gamepanel::scaleFactory);
	buywords->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2+150*Gamepanel::scaleFactory));
	Gamepanel::gamepanel->Layer_C->addChild(buywords);

	auto di=Sprite::createWithSpriteFrameName("beibaojinbiditu.png");
	di->setScale(Gamepanel::scaleFactory);
	di->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2));
	Gamepanel::gamepanel->Layer_C->addChild(di);

	if(petbaglockvec.at(0)->MoneyKind==1)
	{
		auto jinbi=Sprite::createWithSpriteFrameName("jinbi.png");
		jinbi->setPosition(Vec2(di->getContentSize().width-100*Gamepanel::scaleFactory,di->getContentSize().height/2));
		di->addChild(jinbi);
	}
	else
	{
		auto jinbi=Sprite::createWithSpriteFrameName("zuanshi.png");
		jinbi->setPosition(Vec2(di->getContentSize().width-100*Gamepanel::scaleFactory,di->getContentSize().height/2));
		di->addChild(jinbi);
	}
	char a[10];
	sprintf(a,"%d",petbaglockvec.at(0)->MoneyNum);
	auto lab=Label::createWithCharMap("num.png",30,30,'0');
	lab->setString(a);
	lab->setPosition(Vec2(di->getContentSize().width/2,di->getContentSize().height/2));
	di->addChild(lab);

	auto buybtn=MenuItemImage::create("buybtn.png","buybtn.png",CC_CALLBACK_1(PetBag::allbuttoncallback, this));
	buybtn->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2-200*Gamepanel::scaleFactory,Gamepanel::gamepanel->visibleSize.height/2-200*Gamepanel::scaleFactory));
	buybtn->setScale(Gamepanel::scaleFactory);
	buybtn->setTag(PetBagType_BUY);
	auto nobuybtn=MenuItemImage::create("nobuybtn.png","nobuybtn.png",CC_CALLBACK_1(PetBag::allbuttoncallback, this));
	nobuybtn->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2+200*Gamepanel::scaleFactory,Gamepanel::gamepanel->visibleSize.height/2-200*Gamepanel::scaleFactory));
	nobuybtn->setScale(Gamepanel::scaleFactory);
	nobuybtn->setTag(PetBagType_NOBUY);
	auto menu=Mymenu::create(buybtn,nobuybtn,NULL);
	menu->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->Layer_C->addChild(menu);
}

void PetBag::allbuttoncallback(Ref* pSender)
{
	MenuItemImage* pImage=(MenuItemImage*)pSender;
	int tag = pImage->getTag();
	switch(tag)
	{
	case PetBagType_ESC:
		if(Gamepanel::LayerSwitch_A==1)
		{
			Gamepanel::gamepanel->Layer_A->removeAllChildren();
			Gamepanel::gamepanel->removeChild(Gamepanel::gamepanel->Layer_A);
			Gamepanel::LayerSwitch_A=0;
			Gamepanel::LayerSwitch_B=0;
			Gamepanel::LayerSwitch_C=0;
			isshuxingface=1;
			isjinengface=0;
			isjinjieface=0;	
		}
		break;
	case PetBagType_SHUXING:
		jineng->setEnabled(true);
		jinjie->setEnabled(true);
		shuxing->setEnabled(false);
		Gamepanel::gamepanel->Layer_A->removeChild(anniudi);
		anniudi=Sprite::createWithSpriteFrameName("k3.png");
		anniudi->setPosition(Vec2(1434*Gamepanel::scaleFactory,975*Gamepanel::scaleFactory));
		anniudi->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(anniudi);
		isshuxingface=1;
		isjinengface=0;
		isjinjieface=0;
		shuxingface();
		break;
	case PetBagType_JINENG:
		jineng->setEnabled(false);
		jinjie->setEnabled(true);
		shuxing->setEnabled(true);
		Gamepanel::gamepanel->Layer_A->removeChild(anniudi);
		anniudi=Sprite::createWithSpriteFrameName("k2.png");
		anniudi->setPosition(Vec2(1434*Gamepanel::scaleFactory,975*Gamepanel::scaleFactory));
		anniudi->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(anniudi);

		isshuxingface=0;
		isjinengface=1;
		isjinjieface=0;
		jinengface();
		break;
	case PetBagType_JINJIE:
		jineng->setEnabled(true);
		jinjie->setEnabled(false);
		shuxing->setEnabled(true);
		Gamepanel::gamepanel->Layer_A->removeChild(anniudi);
		anniudi=Sprite::createWithSpriteFrameName("k1.png");
		anniudi->setPosition(Vec2(1434*Gamepanel::scaleFactory,975*Gamepanel::scaleFactory));
		anniudi->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(anniudi);

		isshuxingface=0;
		isjinengface=0;
		isjinjieface=1;

		jinjieface();
		break;
	case PetBagType_JIAQIYUE:
		addqiyue();
		break;
	case PetBagType_JIANQIYUE:
		cancelqiyue();
		break;
	case PetBagType_BUY:
		Buycell();
		break;
	case PetBagType_NOBUY:
		Gamepanel::gamepanel->Layer_C->removeAllChildren();
		break;
	}
}

void PetBag::Buycell()
{
	Lock *lk=petbaglockvec.at(0);
	if(Hero::getInstance()->Money>lk->MoneyNum)
	{
		Hero::getInstance()->Money-=lk->MoneyNum;
		petBagcapacitance++;
		char a[8];
		sprintf(a,"%d",Hero::getInstance()->Money);
		Gamepanel::gamepanel->moneylab->setString(a);

		Gamepanel::gamepanel->Layer_C->removeAllChildren();
		lk->releaseself();
		petbaglockvec.erase(0);
		delete lk;
		lk=NULL;
	}
}