#include "Gamepanel.h"
#include "CsvUtil.h"
#include "ItemCreator.h"
#include "ItemData.h"
#include "Item.h"
#include "Hero.h"
#include "PetBag.h"
#include "AppDelegate.h"
#include "GameScene.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
Gamepanel *Gamepanel::gamepanel=nullptr;
float Gamepanel::scaleFactory=0.5;
int Gamepanel::Money=0;
int Gamepanel::LayerSwitch_A=0;
int Gamepanel::LayerSwitch_B=0;
int Gamepanel::LayerSwitch_C=0;
int Gamepanel::LayerSwitch_D=0;
int Gamepanel::JueseSysytem=0;
int Gamepanel::DuanzaoSystem=0;
int Gamepanel::BagSystem=0;
Scene* Gamepanel::createScene()
{
    auto scene = Scene::create();
    auto layer = Gamepanel::create();
    scene->addChild(layer);
    return scene;
}
int xx=60,yy=100;
char asdf[30];
bool Gamepanel::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    scaleFactory = app->scaleFactory;
	gamepanel=this;
	Money=0;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Gamepanel::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Gamepanel::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Gamepanel::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);  

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bar=Sprite::create("aa.png");
	barY=visibleSize.height+bar->getContentSize().height/2;
	barFlag=0;
	bar->setPosition(Vec2(visibleSize.width-bar->getContentSize().width/2+128,barY));
	this->addChild(bar,1);


	
	menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto additem=MenuItemImage::create("x1.png","x1.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	additem->setTag(100);
	additem->setPosition(ccp(200*scaleFactory,1200*scaleFactory));
	menu->addChild(additem);
	auto delitem=MenuItemImage::create("x1.png","xx.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	delitem->setTag(101);
	delitem->setPosition(ccp(320*scaleFactory,1200*scaleFactory));
	menu->addChild(delitem);
	auto showAkinditem=MenuItemImage::create("x1.png","x1.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	showAkinditem->setTag(102);
	showAkinditem->setPosition(ccp(440*scaleFactory,1200*scaleFactory));
	menu->addChild(showAkinditem);



	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainface.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bagpic.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Petpic.plist");
	initMainFace();
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("mainface.plist");
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Bagpic.plist");
    return true;
}

void Gamepanel::initMainFace()
{
    ZipUtils::setPvrEncryptionKeyPart(0,0xf858f36b);
    ZipUtils::setPvrEncryptionKeyPart(1,0xcc54eed0);
    ZipUtils::setPvrEncryptionKeyPart(2,0xdbf1274e);
    ZipUtils::setPvrEncryptionKeyPart(3,0xf3d29164);
    
	MainFaceBg=Sprite::createWithSpriteFrameName("mainbg.png");
	MainFaceBg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	MainFaceBg->setScale(scaleFactory);
	this->addChild(MainFaceBg);

	auto jinbikuang=Sprite::createWithSpriteFrameName("jinbikuang.png");
	jinbikuang->setPosition(ccp(1200*scaleFactory,1180*scaleFactory));
	jinbikuang->setScale(scaleFactory);
	this->addChild(jinbikuang);

	auto moneypic=Sprite::createWithSpriteFrameName("jinbi.png");
	moneypic->setPosition(ccp(1070*scaleFactory,1180*scaleFactory));
	moneypic->setScale(scaleFactory);
	this->addChild(moneypic);

	moneylab= Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30); 
    moneylab->setPosition(ccp(1200*scaleFactory,1180*scaleFactory));
    this->addChild(moneylab);
	
	auto addjinbi=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	addjinbi->setNormalImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addjinbi->setSelectedImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addjinbi->setScale(scaleFactory);
	addjinbi->setPosition(Vec2(1340*scaleFactory,1180*scaleFactory));


	auto zuanshikuang=Sprite::createWithSpriteFrameName("jinbikuang.png");
	zuanshikuang->setPosition(ccp(1573*scaleFactory,1180*scaleFactory));
	zuanshikuang->setScale(scaleFactory);
	this->addChild(zuanshikuang);

	auto zuanshipic=Sprite::createWithSpriteFrameName("zuanshi.png");
	zuanshipic->setPosition(ccp(1443*scaleFactory,1180*scaleFactory));
	zuanshipic->setScale(scaleFactory);
	this->addChild(zuanshipic);

	zuanshilab= Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30); 
    zuanshilab->setPosition(ccp(1573*scaleFactory,1180*scaleFactory));
    this->addChild(zuanshilab);
	
	auto addzuanshi=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	addzuanshi->setNormalImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addzuanshi->setSelectedImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addzuanshi->setScale(scaleFactory);
	addzuanshi->setPosition(Vec2(1713*scaleFactory,1180*scaleFactory));


	auto tilikuang=Sprite::createWithSpriteFrameName("jinbikuang.png");
	tilikuang->setPosition(ccp(1946*scaleFactory,1180*scaleFactory));
	tilikuang->setScale(scaleFactory);
	this->addChild(tilikuang);

	auto tilipic=Sprite::createWithSpriteFrameName("tili.png");
	tilipic->setPosition(ccp(1816*scaleFactory,1180*scaleFactory));
	tilipic->setScale(scaleFactory);
	this->addChild(tilipic);

	tililab= Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30); 
    tililab->setPosition(ccp(1946*scaleFactory,1180*scaleFactory));
    this->addChild(tililab);
	
	auto addtili=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	addtili->setNormalImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addtili->setSelectedImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addtili->setScale(scaleFactory);
	addtili->setPosition(Vec2(2086*scaleFactory,1180*scaleFactory));

	auto herobgbtn=MenuItemImage::create("heromask.png","heromask.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	herobgbtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2*scaleFactory-200*scaleFactory));
	herobgbtn->setOpacity(0);
    herobgbtn->setScale(scaleFactory);
	herobgbtn->setTag(JUESE);
	Heroskeleton = SkeletonAnimation::createWithFile("liemoren.json", "liemoren.atlas", 0.4f*scaleFactory);
	Heroskeleton->setStartListener( [this] (int trackIndex) {
		spTrackEntry* entry = spAnimationState_getCurrent(Heroskeleton->getState(), trackIndex);
		const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;	
	});
	Heroskeleton->setEndListener( [] (int trackIndex) {
	});
	Heroskeleton->setCompleteListener( [this] (int trackIndex, int loopCount) {	
	});
	Heroskeleton->setEventListener( [] (int trackIndex, spEvent* event) {
	});
	Heroskeleton->setAnimation(0, "daiji", true);
	Heroskeleton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2*scaleFactory-400*scaleFactory));
	addChild(Heroskeleton);

	RankList=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	RankList->setNormalImage(Sprite::createWithSpriteFrameName("paihangbang.png"));
	RankList->setSelectedImage(Sprite::createWithSpriteFrameName("paihangbang.png"));
	RankList->setScale(scaleFactory);
	RankList->setPosition(Vec2(1260*scaleFactory,960*scaleFactory));

	Pets=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Pets->setNormalImage(Sprite::createWithSpriteFrameName("chongwulong.png"));
	Pets->setSelectedImage(Sprite::createWithSpriteFrameName("chongwulong.png"));
	Pets->setScale(scaleFactory);
	Pets->setPosition(Vec2(200*scaleFactory,300*scaleFactory));
	Pets->setTag(CHONGWU);

	Forge=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Forge->setNormalImage(Sprite::createWithSpriteFrameName("duanzaotai.png"));
	Forge->setSelectedImage(Sprite::createWithSpriteFrameName("duanzaotai.png"));
	Forge->setScale(scaleFactory);
	Forge->setPosition(Vec2(700*scaleFactory,440*scaleFactory));

	Shop=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Shop->setNormalImage(Sprite::createWithSpriteFrameName("shenmishangren.png"));
	Shop->setSelectedImage(Sprite::createWithSpriteFrameName("shenmishangren.png"));
	Shop->setScale(scaleFactory);
	Shop->setPosition(Vec2(1700*scaleFactory,900*scaleFactory));

    Store=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Store->setNormalImage(Sprite::createWithSpriteFrameName("chucangxiang.png"));
	Store->setSelectedImage(Sprite::createWithSpriteFrameName("chucangxiang.png"));
	Store->setScale(scaleFactory);
    Store->setPosition(Vec2(1580*scaleFactory,360*scaleFactory));
	Store->setTag(BAGBTN);

    Mission=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Mission->setNormalImage(Sprite::createWithSpriteFrameName("guaqiarenwu.png"));
	Mission->setSelectedImage(Sprite::createWithSpriteFrameName("guaqiarenwu.png"));
	Mission->setScale(scaleFactory);
    Mission->setPosition(Vec2(2100*scaleFactory,240*scaleFactory));
    Mission->setTag(MISSION);
    
    MainFaceMenu=Menu::create(RankList,Pets,Forge,Shop,Store,Mission,herobgbtn,addjinbi,addzuanshi,addtili,NULL);
    MainFaceMenu->setPosition(Vec2::ZERO);
    addChild(MainFaceMenu);

	initdata();
}

void Gamepanel::initdata()
{
	capacitance=20;
	Item *cjj=new Item("cjj",0);
	Item *cjq=new Item("cjq",0);
	ItemData::getInstance()->additem(cjj);
	ItemData::getInstance()->additem(cjq);

	Hero::getInstance()->initAllProperties();
}

void Gamepanel::showbarorhidebar()
{
	if(barFlag==0)
	{
		MoveTo *moveto=MoveTo::create(0.2f,Point(visibleSize.width-bar->getContentSize().width/2+128,visibleSize.height-bar->getContentSize().height/2+30));
		bar->runAction(moveto);
		MoveTo *moveto1=MoveTo::create(0.2f,Point(visibleSize.width-bag->getContentSize().width/2,visibleSize.height-bar->getContentSize().height/2+30));
		bag->runAction(moveto1);
		barFlag=1;
	}
	else 
	{
		MoveTo *moveto=MoveTo::create(0.2f,Point(visibleSize.width-bar->getContentSize().width/2+128,visibleSize.height+bar->getContentSize().height/2));
		bar->runAction(moveto);
		MoveTo *moveto1=MoveTo::create(0.2f,Point(visibleSize.width-bag->getContentSize().width/2,visibleSize.height+bar->getContentSize().height/2+30));
		bag->runAction(moveto1);
		barFlag=0;
	}
}

void Gamepanel::showbag()
{
	if(LayerSwitch_A==0)
	{
		BagSystem=1;
		LayerSwitch_A=1;
		Layer_A=Node::create();
		this->addChild(Layer_A,2);

		auto mask=Sprite::create("mask.png");
		mask->setScale(100);
		Layer_A->addChild(mask);

		auto bagbg=Sprite::createWithSpriteFrameName("beibaobeijing.png");
		bagbg->setScale(scaleFactory);
		bagbg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
		Layer_A->addChild(bagbg);

		bagquanbu=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		bagquanbu->setNormalImage(Sprite::createWithSpriteFrameName("bagquanbu.png"));
		bagquanbu->setSelectedImage(Sprite::createWithSpriteFrameName("bagquanbu.png"));
		bagquanbu->setDisabledImage(Sprite::createWithSpriteFrameName("bagquanbu1.png"));
		bagquanbu->setTag(SHOWALL);
		bagquanbu->setPosition(Vec2(2060*scaleFactory,900*scaleFactory));
		bagquanbu->setScale(scaleFactory);
		bagquanbu->setEnabled(false);

		bagzhuangbei=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		bagzhuangbei->setNormalImage(Sprite::createWithSpriteFrameName("bagzhuangbei.png"));
		bagzhuangbei->setSelectedImage(Sprite::createWithSpriteFrameName("bagzhuangbei.png"));
		bagzhuangbei->setDisabledImage(Sprite::createWithSpriteFrameName("bagzhuangbei1.png"));
		bagzhuangbei->setTag(SHOWZHUANGBEI);
		bagzhuangbei->setPosition(Vec2(2060*scaleFactory,700*scaleFactory));
		bagzhuangbei->setScale(scaleFactory);
		
		bagcailiao=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		bagcailiao->setNormalImage(Sprite::createWithSpriteFrameName("bagcaoliao.png"));
		bagcailiao->setSelectedImage(Sprite::createWithSpriteFrameName("bagcaoliao.png"));
		bagcailiao->setDisabledImage(Sprite::createWithSpriteFrameName("bagcailiao1.png"));
		bagcailiao->setTag(SHOWCAILIAO);
		bagcailiao->setPosition(Vec2(2060*scaleFactory,500*scaleFactory));
		bagcailiao->setScale(scaleFactory);
		
		bagdaoju=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		bagdaoju->setNormalImage(Sprite::createWithSpriteFrameName("bagdaoju.png"));
		bagdaoju->setSelectedImage(Sprite::createWithSpriteFrameName("bagdaoju.png"));
		bagdaoju->setDisabledImage(Sprite::createWithSpriteFrameName("bagdaoju1.png"));
		bagdaoju->setTag(SHOWDAOJU);
		bagdaoju->setPosition(Vec2(2060*scaleFactory,300*scaleFactory));
		bagdaoju->setScale(scaleFactory);
		
		auto menubagmiddle=Menu::create(bagquanbu,bagzhuangbei,bagcailiao,bagdaoju,NULL);
		menubagmiddle->setPosition(Vec2::ZERO);
		Layer_A->addChild(menubagmiddle);

		auto bagmiddle=Sprite::createWithSpriteFrameName("bagmiddle.png");
		bagmiddle->setScale(scaleFactory);
		bagmiddle->setPosition(Vec2(visibleSize.width/2-60*scaleFactory,visibleSize.height/2));
		Layer_A->addChild(bagmiddle);

		auto bagtitle=Sprite::createWithSpriteFrameName("biaotibeijing.png");
		bagtitle->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+550*scaleFactory));
		auto bagtiletext=Sprite::createWithSpriteFrameName("chucangxiangbiaoti.png");
		bagtiletext->setPosition(Vec2(bagtitle->getContentSize().width/2,bagtitle->getContentSize().height/2));
		bagtitle->addChild(bagtiletext);
		bagtitle->setScale(scaleFactory);
		Layer_A->addChild(bagtitle);

		auto di=Sprite::createWithSpriteFrameName("shuziditu.png");
		di->setPosition(Vec2(300*scaleFactory,500*scaleFactory));
		di->setScale(scaleFactory);
		Layer_A->addChild(di);

		auto di1=Sprite::createWithSpriteFrameName("beibaojinbiditu.png");
		di1->setPosition(Vec2(460*scaleFactory,380*scaleFactory));
		auto di1jinbi=Sprite::createWithSpriteFrameName("beibaojinbi.png");
		di1jinbi->setPosition(Vec2(di1->getContentSize().width/2+230*scaleFactory,di1->getContentSize().height/2));
		di1->addChild(di1jinbi);
		di1->setScale(scaleFactory);
		Layer_A->addChild(di1);

		auto di2=Sprite::createWithSpriteFrameName("wupinminchenkuang.png");
		di2->setPosition(Vec2(285*2*scaleFactory,470*2*scaleFactory));
		di2->setScale(scaleFactory);
		Layer_A->addChild(di2);

		auto di3=Sprite::createWithSpriteFrameName("wupinmiaoshukuang.png");
		di3->setPosition(Vec2(230*2*scaleFactory,350*2*scaleFactory));
		di3->setScale(scaleFactory);
		Layer_A->addChild(di3);

		auto di4=Sprite::createWithSpriteFrameName("wupinkuang.png");
		di4->setPosition(Vec2(135*2*scaleFactory,470*2*scaleFactory));
		di4->setScale(scaleFactory);
		Layer_A->addChild(di4);

		auto bagclose=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		bagclose->setNormalImage(Sprite::createWithSpriteFrameName("guanbi.png"));
		bagclose->setSelectedImage(Sprite::createWithSpriteFrameName("guanbi.png"));
		bagclose->setPosition(Vec2(1020*2*scaleFactory,550*2*scaleFactory));
		bagclose->setScale(scaleFactory);
		bagclose->setTag(BAGCLOSEBTN);

		auto bagjian=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		bagjian->setNormalImage(Sprite::createWithSpriteFrameName("beibaojian.png"));
		bagjian->setSelectedImage(Sprite::createWithSpriteFrameName("beibaojian.png"));
		bagjian->setPosition(Vec2(100*2*scaleFactory,250*2*scaleFactory));
		bagjian->setScale(scaleFactory);

		auto bagjia=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		bagjia->setNormalImage(Sprite::createWithSpriteFrameName("beibaojia.png"));
		bagjia->setSelectedImage(Sprite::createWithSpriteFrameName("beibaojia.png"));
		bagjia->setPosition(Vec2(210*2*scaleFactory,250*2*scaleFactory));
		bagjia->setScale(scaleFactory);

		auto sellall=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		sellall->setNormalImage(Sprite::createWithSpriteFrameName("quanbuanniu1.png"));
		sellall->setSelectedImage(Sprite::createWithSpriteFrameName("quanbuanniu2.png"));
		sellall->setPosition(Vec2(330*2*scaleFactory,250*2*scaleFactory));
		sellall->setScale(scaleFactory);

		auto sell=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
		sell->setNormalImage(Sprite::createWithSpriteFrameName("chushou1.png"));
		sell->setSelectedImage(Sprite::createWithSpriteFrameName("chushou1.png"));
		//sell->setDisabledImage(Sprite::createWithSpriteFrameName("bukechushou.png"));
		sell->setPosition(Vec2(230*2*scaleFactory,120*2*scaleFactory));
		sell->setScale(scaleFactory);

		auto menubag=Menu::create(bagclose,bagjian,bagjia,sellall,sell,NULL);
		menubag->setPosition(Vec2::ZERO);
		Layer_A->addChild(menubag);


		scrollView = ScrollView::create();
		continerLayer = Layer::create();
		continerLayer->setAnchorPoint(Vec2(0,0));
		continerLayer->setPosition(Vec2(0,0));
		scrollView->setPosition(ccp(804*scaleFactory,188*scaleFactory));
    
		scrollView->setViewSize(Size(1104*scaleFactory, 887*scaleFactory));
		bagline=0;
		if(ItemData::getInstance()->Allbagitemvec.size()<=20)
		{
			continerLayer->setContentSize(Size(1094*scaleFactory, 887*scaleFactory));
		}
		else
		{
			bagline=(ItemData::getInstance()->Allbagitemvec.size()-20)%5==0? (ItemData::getInstance()->Allbagitemvec.size()-20)/5:(ItemData::getInstance()->Allbagitemvec.size()-20)/5+1;
			continerLayer->setContentSize(Size(1094*scaleFactory,887*scaleFactory+220*bagline*scaleFactory));
			continerLayer->setPosition(Vec2(0,-220*bagline*scaleFactory));
		}
		scrollView->setContentSize(continerLayer->getContentSize());
		scrollView->setContainer(continerLayer);
    
		scrollView->setTouchEnabled(true);
		scrollView->setDirection(ScrollView::Direction::VERTICAL);
		scrollView->setBounceable(true);
		scrollView->setDelegate(this);
		Layer_A->addChild(scrollView);

		menuitem=Mymenu::create();
		menuitem->setAnchorPoint(Vec2::ZERO);
		menuitem->setPosition(Vec2::ZERO);
		continerLayer->addChild(menuitem,10);
		
		for(int i=0;i<capacitance;i++)
		{
			int x=i%5*110+60;
			int y=380-i/5*110;
			auto kuangzi=Sprite::createWithSpriteFrameName("wupinkuang.png");
			kuangzi->setScale(scaleFactory);
			kuangzi->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
			continerLayer->addChild(kuangzi,1);
		}

		for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
		{
			int x=i%5*110+60;
			int y=380-i/5*110;
			Item *tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
			tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
            tempbgt->pic->setScale(scaleFactory);
			menuitem->addChild(tempbgt->pic);
			//log(tempbgt->id.c_str());
		}
	}
	
}

void Gamepanel::additem()
{
	ItemCreator::getInstance()->createItem_unique(1,0,5);
	ItemCreator::getInstance()->createItem_normal("cl001");
	ItemCreator::getInstance()->createItem_normal("soul001");
	ItemCreator::getInstance()->createItem_normal("xhp001");
	ItemCreator::getInstance()->createItem_normal("wq001");
}

void Gamepanel::deleteitem()
{

}

void Gamepanel::showall()
{
	menuitem->removeAllChildren();
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{
		int x=i%5*110+60;
		int y=380-i/5*110;
		Item *tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
        tempbgt->pic->setScale(scaleFactory);
		menuitem->addChild(tempbgt->pic);
	}
}

void Gamepanel::showequipments()
{
	menuitem->removeAllChildren();
	int tempi=0;
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{			
		auto tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		if(tempbgt->kind==1||tempbgt->kind==0)
		{
			int x=tempi%5*110+60;
			int y=380-tempi/5*110;
			tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory));
            tempbgt->pic->setScale(scaleFactory);
			menuitem->addChild(tempbgt->pic);
			tempi++;
		}
	}
}

void Gamepanel::showitems()
{
	menuitem->removeAllChildren();
	int tempi=0;
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{			
		auto tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		if(tempbgt->kind==2)
		{
			int x=tempi%5*110+60;
			int y=380-tempi/5*110;
			tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory));
            tempbgt->pic->setScale(scaleFactory);
			menuitem->addChild(tempbgt->pic);
			tempi++;
		}
	}
}

void Gamepanel::closebag()
{
	if(LayerSwitch_A==1)
	{
		Layer_A->removeAllChildren();
		this->removeChild(Layer_A);
		LayerSwitch_A=0;
	}
}

void Gamepanel::allbuttoncallback(Ref* pSender)
{
	MenuItemImage* pImage=(MenuItemImage*)pSender;
	int tag = pImage->getTag();
	switch(tag)
	{
	case DROPBTN:
			showbarorhidebar();
		break;
	case BAGBTN:
			showbag();
		break;
	case BAGCLOSEBTN:
			closebag();
		break;
	case JUESE:
		Hero::getInstance()->initJueseFace();
		break;
	case CHONGWU:
		PetBag::getInstance()->initPetFace();
		break;
    case MISSION:
            Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::createSceneWithLevel(0)));
        break;
	case SHOWALL:
		bagcailiao->setEnabled(true);
		bagcailiao->setPosition(Vec2(1030*2*scaleFactory,250*2*scaleFactory));
		bagdaoju->setEnabled(true);
		bagdaoju->setPosition(Vec2(1030*2*scaleFactory,150*2*scaleFactory));
		bagzhuangbei->setEnabled(true);
		bagzhuangbei->setPosition(Vec2(1030*2*scaleFactory,350*2*scaleFactory));
		bagquanbu->setEnabled(false);
		bagquanbu->setPosition(Vec2(1040*2*scaleFactory,450*2*scaleFactory));
		showall();
		break;
	case SHOWZHUANGBEI:
		bagcailiao->setEnabled(true);
		bagcailiao->setPosition(Vec2(1030*2*scaleFactory,250*2*scaleFactory));
		bagdaoju->setEnabled(true);
		bagdaoju->setPosition(Vec2(1030*2*scaleFactory,150*2*scaleFactory));
		bagzhuangbei->setEnabled(false);
		bagquanbu->setEnabled(true);
		bagquanbu->setPosition(Vec2(1030*2*scaleFactory,450*2*scaleFactory));
		bagzhuangbei->setPosition(Vec2(1040*2*scaleFactory,350*2*scaleFactory));
		showequipments();
		break;
	case SHOWCAILIAO:
		bagcailiao->setEnabled(false);
		bagdaoju->setEnabled(true);
		bagdaoju->setPosition(Vec2(1030*2*scaleFactory,150*2*scaleFactory));
		bagzhuangbei->setEnabled(true);
		bagzhuangbei->setPosition(Vec2(1030*2*scaleFactory,350*2*scaleFactory));
		bagquanbu->setEnabled(true);
		bagquanbu->setPosition(Vec2(1030*2*scaleFactory,450*2*scaleFactory));
		bagcailiao->setPosition(Vec2(1040*2*scaleFactory,250*2*scaleFactory));
		showitems();
		break;
	case SHOWDAOJU:
		bagcailiao->setEnabled(true);
		bagcailiao->setPosition(Vec2(1030*2*scaleFactory,250*2*scaleFactory));
		bagdaoju->setEnabled(false);
		bagzhuangbei->setEnabled(true);
		bagzhuangbei->setPosition(Vec2(1030*2*scaleFactory,350*2*scaleFactory));
		bagquanbu->setEnabled(true);
		bagquanbu->setPosition(Vec2(1030*2*scaleFactory,450*2*scaleFactory));
		bagdaoju->setPosition(Vec2(1040*2*scaleFactory,150*2*scaleFactory));
		showitems();
		break;
	case 100:
		additem();
		break;
	case 101:
		/*menuitem->removeAllChildren();
		for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
		{
			int x=i%4*80+40;
			int y=330-i/4*80;
			auto tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
			tempbgt->pic->setPosition(ccp(x,y));
			menuitem->addChild(tempbgt->pic);
		}*/
		deleteitem();
	break;
	case 102:
		menuitem->removeAllChildren();
		int tempi=0;
		for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
		{			
			auto tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
			if(tempbgt->kind==2)
			{
				int x=tempi%4*80+40;
				int y=330-tempi/4*80;
				tempbgt->pic->setPosition(ccp(x,y));
				menuitem->addChild(tempbgt->pic);
				tempi++;
			}
		}
		break;
	}
}


bool Gamepanel::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void Gamepanel::onTouchMoved(Touch *touch, Event *event)
{

} 

void Gamepanel::onTouchEnded(Touch *touch, Event *event)
{

}


void Gamepanel::scrollViewDidScroll(extension::ScrollView* view)
{

}

void Gamepanel::scrollViewDidZoom(extension::ScrollView* view)
{
	
}



void Gamepanel::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	//if(Bagopen==1)
	//{
		Item::randomforproperty=rand()%100;
	//}
		
}
