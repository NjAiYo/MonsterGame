#include "Gamepanel.h"
#include "CsvUtil.h"
#include "ItemCreator.h"
#include "ItemData.h"
#include "Item.h"
#include "Hero.h"
#include "PetBag.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "GameManager.h"
#include "BagLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
Gamepanel* Gamepanel::gamepanel = nullptr;
short Gamepanel::LayerSwitch_A=0;
 short Gamepanel::LayerSwitch_B=0;
 short Gamepanel::LayerSwitch_C=0;
 short Gamepanel::LayerSwitch_D=0;
 short Gamepanel::JueseSysytem=0;
 short Gamepanel::DuanzaoSystem=0;
 short Gamepanel::BagSystem=0;
 short Gamepanel::TalentSystem=0;
 short Gamepanel::EquipSystem=0;
 float Gamepanel::scaleFactory=0;
Scene* Gamepanel::createScene()
{
    auto scene = Scene::create();
    auto layer = Gamepanel::create();
    scene->addChild(layer);
    return scene;
}

bool Gamepanel::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    hero = GameManager::getInstance()->getPlayer();
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    Gamepanel::scaleFactory = app->scaleFactory;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Gamepanel::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Gamepanel::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Gamepanel::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);  

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



	
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


    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("itemicons.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainface.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bagpic.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pet.plist");
	initMainFace();
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("mainface.plist");
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Bagpic.plist");
    
    bagLayer = new BagLayer();
    bagLayer->initWithGamePanel(this);
    addChild(bagLayer);
    bagLayer->setVisible(false);
    bagLayer->release();
    
    scheduleUpdate();
    return true;
}

void Gamepanel::initMainFace()
{
    ZipUtils::setPvrEncryptionKeyPart(0,0xf858f36b);
    ZipUtils::setPvrEncryptionKeyPart(1,0xcc54eed0);
    ZipUtils::setPvrEncryptionKeyPart(2,0xdbf1274e);
    ZipUtils::setPvrEncryptionKeyPart(3,0xf3d29164);
    
	MainFaceBg=Sprite::create("mainbg.png");
	MainFaceBg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	this->addChild(MainFaceBg);

	auto jinbikuang=Sprite::createWithSpriteFrameName("jinbikuang.png");
	jinbikuang->setPosition(ccp(1200*scaleFactory,1180*scaleFactory));
	this->addChild(jinbikuang);

	auto moneypic=Sprite::createWithSpriteFrameName("jinbi.png");
	moneypic->setPosition(ccp(1070*scaleFactory,1180*scaleFactory));
	this->addChild(moneypic);

    moneylab= Label::createWithSystemFont("0", "Arial", 30);
    moneylab->setPosition(ccp(1200*scaleFactory,1180*scaleFactory));
    this->addChild(moneylab);
	
	auto addjinbi=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	addjinbi->setNormalImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addjinbi->setSelectedImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addjinbi->setPosition(Vec2(1340*scaleFactory,1180*scaleFactory));


	auto zuanshikuang=Sprite::createWithSpriteFrameName("jinbikuang.png");
	zuanshikuang->setPosition(ccp(1573*scaleFactory,1180*scaleFactory));
	this->addChild(zuanshikuang);

	auto zuanshipic=Sprite::createWithSpriteFrameName("zuanshi.png");
	zuanshipic->setPosition(ccp(1443*scaleFactory,1180*scaleFactory));
	this->addChild(zuanshipic);

	zuanshilab= Label::createWithSystemFont("0", "Arial", 30);
    zuanshilab->setPosition(ccp(1573*scaleFactory,1180*scaleFactory));
    this->addChild(zuanshilab);
	
	auto addzuanshi=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	addzuanshi->setNormalImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addzuanshi->setSelectedImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addzuanshi->setPosition(Vec2(1713*scaleFactory,1180*scaleFactory));


	auto tilikuang=Sprite::createWithSpriteFrameName("jinbikuang.png");
	tilikuang->setPosition(ccp(1946*scaleFactory,1180*scaleFactory));
	this->addChild(tilikuang);

	auto tilipic=Sprite::createWithSpriteFrameName("tili.png");
	tilipic->setPosition(ccp(1816*scaleFactory,1180*scaleFactory));
	this->addChild(tilipic);

	tililab= Label::createWithSystemFont("0", "Arial", 30);
    tililab->setPosition(ccp(1946*scaleFactory,1180*scaleFactory));
    this->addChild(tililab);
	
	auto addtili=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	addtili->setNormalImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addtili->setSelectedImage(Sprite::createWithSpriteFrameName("jiahao1.png"));
	addtili->setPosition(Vec2(2086*scaleFactory,1180*scaleFactory));

	auto herobgbtn=MenuItemImage::create("heromask.png","heromask.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	herobgbtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2-200*scaleFactory));
	herobgbtn->setOpacity(0);
	herobgbtn->setTag(JUESE);
	Heroskeleton = SkeletonAnimation::createWithFile("liemoren.json", "liemoren.atlas", 0.5f*scaleFactory);
	Heroskeleton->setAnimation(0, "daiji", true);
	Heroskeleton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2-400*scaleFactory));
	addChild(Heroskeleton);

	RankList=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	RankList->setNormalImage(Sprite::createWithSpriteFrameName("paihangbang.png"));
	RankList->setSelectedImage(Sprite::createWithSpriteFrameName("paihangbang.png"));
	RankList->setPosition(Vec2(1260*scaleFactory,960*scaleFactory));

	Pets=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Pets->setNormalImage(Sprite::createWithSpriteFrameName("chongwulong.png"));
	Pets->setSelectedImage(Sprite::createWithSpriteFrameName("chongwulong.png"));
	Pets->setPosition(Vec2(200*scaleFactory,300*scaleFactory));
	Pets->setTag(CHONGWU);

	Forge=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Forge->setNormalImage(Sprite::createWithSpriteFrameName("duanzaotai.png"));
	Forge->setSelectedImage(Sprite::createWithSpriteFrameName("duanzaotai.png"));
	Forge->setPosition(Vec2(700*scaleFactory,440*scaleFactory));

	Shop=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Shop->setNormalImage(Sprite::createWithSpriteFrameName("shenmishangren.png"));
	Shop->setSelectedImage(Sprite::createWithSpriteFrameName("shenmishangren.png"));
	Shop->setPosition(Vec2(1700*scaleFactory,900*scaleFactory));

    Store=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Store->setNormalImage(Sprite::createWithSpriteFrameName("chucangxiang.png"));
	Store->setSelectedImage(Sprite::createWithSpriteFrameName("chucangxiang.png"));
    Store->setPosition(Vec2(1580*scaleFactory,360*scaleFactory));
	Store->setTag(BAGBTN);

    Mission=MenuItemImage::create("","",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Mission->setNormalImage(Sprite::createWithSpriteFrameName("guaqiarenwu.png"));
	Mission->setSelectedImage(Sprite::createWithSpriteFrameName("guaqiarenwu.png"));
    Mission->setPosition(Vec2(2100*scaleFactory,240*scaleFactory));
    Mission->setTag(MISSION);
    
    MainFaceMenu=Menu::create(RankList,Pets,Forge,Shop,Store,Mission,herobgbtn,addjinbi,addzuanshi,addtili,NULL);
    MainFaceMenu->setPosition(Vec2::ZERO);
    addChild(MainFaceMenu);

	initdata();
}

void Gamepanel::initdata()
{
	
	char temp[5];
	for(int i=20;i<100;i++)
	{
		sprintf(temp,"%d",i+1);
		Lock *lk=new Lock(temp,2);
		ItemData::getInstance()->baglockvec.pushBack(lk);
        lk->release();
	}


	Item *cjj=new Item("cjj",0);
	Item *cjq=new Item("cjq",0);
	ItemData::getInstance()->additem(cjj);
	ItemData::getInstance()->additem(cjq);
    cjj->release();
    cjq->release();
	Hero::getInstance()->initAllProperties();
	PetBag::getInstance()->initPetBagData();
}

void Gamepanel::showbag()
{
    bagLayer->setVisible(true);
    bagLayer->setLocalZOrder(10);
}

void Gamepanel::additem()
{
	ItemCreator::getInstance()->createItem_unique(1,0,1);
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
		menuitem->addChild(tempbgt->pic);
	}
	for(int i=0;i<100;i++)
	{
		int x=i%5*110+60;
		int y=380-i/5*110;
		if(i+1>hero->capacitance)
		{
			Lock *lk=ItemData::getInstance()->baglockvec.at(i-hero->capacitance);
			lk->lockpic->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+16*220*Gamepanel::scaleFactory));
			menuitem->addChild(lk->lockpic);
		}

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
			tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
			menuitem->addChild(tempbgt->pic);
			tempi++;
		}
	}
	for(int i=0;i<100;i++)
	{
		int x=i%5*110+60;
		int y=380-i/5*110;
		if(i+1>hero->capacitance)
		{
			Lock *lk=ItemData::getInstance()->baglockvec.at(i-hero->capacitance);
			lk->lockpic->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+16*220*Gamepanel::scaleFactory));
			menuitem->addChild(lk->lockpic);
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
			tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
			menuitem->addChild(tempbgt->pic);
			tempi++;
		}
	}
	for(int i=0;i<100;i++)
	{
		int x=i%5*110+60;
		int y=380-i/5*110;
		if(i+1>hero->capacitance)
		{
			Lock *lk=ItemData::getInstance()->baglockvec.at(i-hero->capacitance);
			lk->lockpic->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+16*220*Gamepanel::scaleFactory));
			menuitem->addChild(lk->lockpic);
		}

	}
}

void Gamepanel::closebag()
{
	if(LayerSwitch_C==1||LayerSwitch_D==1)
		return;
	if(LayerSwitch_A==1)
	{
		Layer_A->removeAllChildren();
		this->removeChild(Layer_A);
		LayerSwitch_A=0;
		LayerSwitch_B=0;
		LayerSwitch_D=0;
		BagSystem=0;
	}
}

void Gamepanel::allbuttoncallback(Ref* pSender)
{
	MenuItemImage* pImage=(MenuItemImage*)pSender;
	int tag = pImage->getTag();
	switch(tag)
	{
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
		if(LayerSwitch_D==1)
			return;
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
		if(LayerSwitch_D==1)
			return;
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
		if(LayerSwitch_D==1)
			return;
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
		if(LayerSwitch_D==1)
			return;
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
	case BAGBUY:
		buyCell();
		break;
	case BAGNOBUY:
		LayerSwitch_D=0;
		menuitem->setEnabled(true);
		scrollView->setTouchEnabled(true);
		Layer_D->removeAllChildren();
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
		/*int tempi=0;
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
		}*/
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

void Gamepanel::jiesuoBag()
{
	Layer_D->removeAllChildren();
	LayerSwitch_D=1;
	menuitem->setEnabled(false);
	scrollView->setTouchEnabled(false);
	auto mask=Sprite::create("mask.png");
	mask->setScale(100);
	Layer_D->addChild(mask);

	auto buybg=Sprite::create("buybg.png");
	buybg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	Layer_D->addChild(buybg);

	auto buywords=Sprite::create("buywords.png");
	buywords->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+150*Gamepanel::scaleFactory));
	Layer_D->addChild(buywords);

	auto di=Sprite::createWithSpriteFrameName("beibaojinbiditu.png");
	di->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	Layer_D->addChild(di);

	if(ItemData::getInstance()->baglockvec.at(0)->MoneyKind==1)
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
	sprintf(a,"%d",ItemData::getInstance()->baglockvec.at(0)->MoneyNum);
	auto lab=Label::createWithCharMap("num.png",30,30,'0');
	lab->setString(a);
	lab->setPosition(Vec2(di->getContentSize().width/2,di->getContentSize().height/2));
	di->addChild(lab);

	auto buybtn=MenuItemImage::create("buybtn.png","buybtn.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback, this));
	buybtn->setPosition(Vec2(visibleSize.width/2-200*Gamepanel::scaleFactory,visibleSize.height/2-200*Gamepanel::scaleFactory));

	buybtn->setTag(BAGBUY);
	auto nobuybtn=MenuItemImage::create("nobuybtn.png","nobuybtn.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback, this));
	nobuybtn->setPosition(Vec2(visibleSize.width/2+200*Gamepanel::scaleFactory,visibleSize.height/2-200*Gamepanel::scaleFactory));

	nobuybtn->setTag(BAGNOBUY);
	auto menu=Menu::create(buybtn,nobuybtn,NULL);
	menu->setPosition(Vec2::ZERO);
	Layer_D->addChild(menu);
}

void Gamepanel::buyCell()
{
	Lock *lk=ItemData::getInstance()->baglockvec.at(0);
	if(Hero::getInstance()->Money>lk->MoneyNum)
	{
		LayerSwitch_D=0;
		menuitem->setEnabled(true);
		scrollView->setTouchEnabled(true);
		Hero::getInstance()->Money-=lk->MoneyNum;
		hero->capacitance++;
		char a[8];
		sprintf(a,"%d",Hero::getInstance()->Money);
		moneylab->setString(a);

		Layer_D->removeAllChildren();
		lk->releaseself();
		ItemData::getInstance()->baglockvec.erase(0);
		delete lk;
		lk=NULL;
	}
}

void Gamepanel::update(float dt)
{
	if(Gamepanel::BagSystem==1)
	{
		Item::randomforproperty=rand()%100;
	}
	if(Gamepanel::TalentSystem==1)
	{
		if(continerLayer->getPositionY()>-540*Gamepanel::scaleFactory&&continerLayer->getPositionY()<0)
		{
			float currentY=continerLayer->getPositionY()*340*Gamepanel::scaleFactory/(540*Gamepanel::scaleFactory);
			Hero::getInstance()->huatiao->setPosition(Vec2(2000*Gamepanel::scaleFactory,764*Gamepanel::scaleFactory-currentY-340*Gamepanel::scaleFactory));
		}
	}
}
