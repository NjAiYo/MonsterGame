#include "Gamepanel.h"
#include "CsvUtil.h"
#include "ItemCreator.h"
#include "ItemData.h"
#include "Item.h"
#include "AppDelegate.h"
#include "GameScene.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
Gamepanel *Gamepanel::gamepanel=nullptr;
int Gamepanel::Money=0;
int Gamepanel::LayerSwitch_A=0;
int Gamepanel::LayerSwitch_B=0;
int Gamepanel::LayerSwitch_C=0;
int Gamepanel::LayerSwitch_D=0;
float scaleFactory=1.0;
int templine=0;
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
	Bagopen=0;
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


	dropbtn = MenuItemImage::create("menudown.png", "menudown.png", CC_CALLBACK_1(Gamepanel::allbuttoncallback, this));
	dropbtn->setTag(DROPBTN);
	dropbtn->setPosition(Vec2(origin.x + visibleSize.width - dropbtn->getContentSize().width/2 ,origin.y + visibleSize.height - dropbtn->getContentSize().height/2));

	bag=MenuItemImage::create("bag.png","bag.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	bag->setTag(BAGBTN);
	bag->setPosition(Vec2(origin.x +visibleSize.width-bag->getContentSize().width/2,origin.y +visibleSize.height+bag->getContentSize().height/2));

	bagclose=MenuItemImage::create("xx.png","xx.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	bagclose->setTag(BAGCLOSEBTN);
	bagclose->setVisible(false);
	
	menu = Menu::create(dropbtn, NULL);
    menu->setPosition(Vec2::ZERO);
	menu->addChild(bag);
	menu->addChild(bagclose);
    this->addChild(menu, 1);

	auto additem=MenuItemImage::create("xxp.png","xxp.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	additem->setTag(100);
	additem->setPosition(ccp(200*scaleFactory,1200*scaleFactory));
    additem->setScale(scaleFactory);
	menu->addChild(additem);
	auto delitem=MenuItemImage::create("xx.png","xx.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	delitem->setTag(101);
	delitem->setPosition(ccp(320*scaleFactory,1200*scaleFactory));
    delitem->setScale(scaleFactory);
	menu->addChild(delitem);
	auto showAkinditem=MenuItemImage::create("xx.png","xx.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	showAkinditem->setTag(102);
	showAkinditem->setPosition(ccp(440*scaleFactory,1200*scaleFactory));
    showAkinditem->setScale(scaleFactory);
	menu->addChild(showAkinditem);
    
	auto moneypic=Sprite::create("gold.png");
	moneypic->setPosition(ccp(1600*scaleFactory,1200*scaleFactory));
    moneypic->setScale(scaleFactory);
	this->addChild(moneypic,1);

	moneylab= Label::create("0", "Arial", 30);
    moneylab->setPosition(ccp(1500*scaleFactory,1200*scaleFactory));
    moneylab->setScale(scaleFactory);
    this->addChild(moneylab, 1);

	initMainFace();
    return true;
}

void Gamepanel::initMainFace()
{
	MainFaceBg=Sprite::create("mainbg.png");
	MainFaceBg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    MainFaceBg->setScale(scaleFactory);
	this->addChild(MainFaceBg);

    ZipUtils::setPvrEncryptionKeyPart(0,0xf858f36b);
    ZipUtils::setPvrEncryptionKeyPart(1,0xcc54eed0);
    ZipUtils::setPvrEncryptionKeyPart(2,0xdbf1274e);
    ZipUtils::setPvrEncryptionKeyPart(3,0xf3d29164);
    
    spAtlas* atlas = spAtlas_createFromFile("liemoren.atlas", 0);
    SkeletonAnimation *skeletonNode = SkeletonAnimation::createWithFile("liemoren.json", atlas);
    //skeletonNode->setAnimation(0, "walk", true);
    //        spine::SkeletonAnimation *skeletonNode = SkeletonAnimation::createWithFile("hero.json", "hero.atlas", 0.6f);
    
    skeletonNode->setPosition(visibleSize.width/2, 10);
    skeletonNode->setScale(0.5*scaleFactory);
    addChild(skeletonNode);
    skeletonNode->setAnimation(0, "daiji", true);
	
	Jewel=MenuItemImage::create("uimainface/11.png","uimainface/11.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Jewel->setPosition(Vec2(1800*scaleFactory,1200*scaleFactory));
    Jewel->setScale(scaleFactory);
	Vitality=MenuItemImage::create("uimainface/12.png","uimainface/12.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Vitality->setPosition(Vec2(2000*scaleFactory,1200*scaleFactory));
    Vitality->setScale(scaleFactory);
	RankList=MenuItemImage::create("uimainface/1.png","uimainface/1.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	RankList->setPosition(Vec2(200*scaleFactory,700*scaleFactory));
    RankList->setScale(scaleFactory);
	Pets=MenuItemImage::create("uimainface/2.png","uimainface/2.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Pets->setPosition(Vec2(200*scaleFactory,300*scaleFactory));
    Pets->setScale(scaleFactory);
	Forge=MenuItemImage::create("uimainface/3.png","uimainface/3.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Forge->setPosition(Vec2(500*scaleFactory,560*scaleFactory));
    Forge->setScale(scaleFactory);
	Shop=MenuItemImage::create("uimainface/6.png","uimainface/6.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Shop->setPosition(Vec2(1800*scaleFactory,800*scaleFactory));
    Shop->setScale(scaleFactory);
    Store=MenuItemImage::create("uimainface/5.png","uimainface/5.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
    Store->setPosition(Vec2(1800*scaleFactory,300*scaleFactory));
    Store->setScale(scaleFactory);
    Mission=MenuItemImage::create("uimainface/7.png","uimainface/7.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
    Mission->setPosition(Vec2(1600*scaleFactory,560*scaleFactory));
    Mission->setScale(scaleFactory);
    Mission->setTag(MISSION);

    
    MainFaceMenu=Menu::create(Jewel,Vitality,RankList,Pets,Forge,Shop,Store,Mission,NULL);
    MainFaceMenu->setPosition(Vec2::ZERO);
    addChild(MainFaceMenu);
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
	if(Bagopen==0)
	{
		bagbg=Sprite::create("bagbg.png");
		bagbg->setPosition(Vec2(1652*scaleFactory,621*scaleFactory));
		this->addChild(bagbg,1);
		bagclose->setPosition(Vec2(1652*scaleFactory+250,621*scaleFactory+250));
		bagclose->setVisible(true);
		initbag();
	}
	Bagopen=1;
}

void Gamepanel::initbag()
{
	bagitemshowpanel=Node::create();
	this->addChild(bagitemshowpanel,1);
	itemsellshow=Node::create();
	this->addChild(itemsellshow,2);

	scrollView = ScrollView::create();
	continerLayer = Layer::create();
    continerLayer->setAnchorPoint(Vec2(0,0));
    continerLayer->setPosition(Vec2(0,0));
	scrollView->setPosition(ccp(1402*scaleFactory,360*scaleFactory));
    if(ItemData::getInstance()->Allbagitemvec.size()<=20)
    {
       continerLayer->setContentSize(Size(500*scaleFactory, 500*scaleFactory));
    }
    else
    {
        templine=(ItemData::getInstance()->Allbagitemvec.size()-20)/5%5==0?(ItemData::getInstance()->Allbagitemvec.size()-20)/5:(ItemData::getInstance()->Allbagitemvec.size()-20)/5+1;
        continerLayer->setContentSize(Size(500*scaleFactory,(500+templine*100)*scaleFactory));
        continerLayer->setPosition(Vec2(0,-templine*40));
    }
    scrollView->setViewSize(Size(500*scaleFactory, 500*scaleFactory));
    
	scrollView->setContentSize(continerLayer->getContentSize());
    scrollView->setContainer(continerLayer);
    
    scrollView->setTouchEnabled(true);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	scrollView->setBounceable(true);
    scrollView->setDelegate(this);
    this->addChild(scrollView,1);




	menuitem=Mymenu::create();
	menuitem->setAnchorPoint(Vec2::ZERO);
	menuitem->setPosition(Vec2::ZERO);
	continerLayer->addChild(menuitem,10);

	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{
		int x=i%5*80*scaleFactory+80*scaleFactory;
		int y=450*scaleFactory-i/5*80*scaleFactory;
		Item *tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		tempbgt->pic->setPosition(ccp(x,y+templine*100));
		menuitem->addChild(tempbgt->pic);
		log(tempbgt->id.c_str());
	}
}
void Gamepanel::additem()
{
	ItemCreator::getInstance()->createItem_unique(1,0,5);
    ItemCreator::getInstance()->createItem_unique(1,0,5);
    ItemCreator::getInstance()->createItem_unique(1,0,5);
    ItemCreator::getInstance()->createItem_unique(1,0,5);
    ItemCreator::getInstance()->createItem_unique(1,0,5);
	//ItemCreator::getInstance()->createItem_normal("cl001");
	//ItemCreator::getInstance()->createItem_normal("soul001");
	//ItemCreator::getInstance()->createItem_normal("xhp001");
	//ItemCreator::getInstance()->createItem_normal("wq001");
}

void Gamepanel::deleteitem()
{


}

void Gamepanel::showall()
{

}

void Gamepanel::closebag()
{
	if(LayerSwitch_B==0)
	{
		this->removeChild(bagbg);
		bagclose->setVisible(false);
		this->removeChild(bagitemshowpanel);
		this->removeChild(scrollView);
		Bagopen=0;
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
    case MISSION:
            Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createSceneWithLevel(0)));
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
