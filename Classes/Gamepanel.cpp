#include "Gamepanel.h"
#include "CsvUtil.h"
#include "ItemCreator.h"
#include "ItemData.h"
#include "Item.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
Gamepanel *Gamepanel::gamepanel=nullptr;
int Gamepanel::Money=0;
int Gamepanel::LayerSwitch_A=0;
int Gamepanel::LayerSwitch_B=0;
int Gamepanel::LayerSwitch_C=0;
int Gamepanel::LayerSwitch_D=0;
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
	additem->setPosition(ccp(100,600));
	menu->addChild(additem);
	auto delitem=MenuItemImage::create("xx.png","xx.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	delitem->setTag(101);
	delitem->setPosition(ccp(160,600));
	menu->addChild(delitem);
	auto showAkinditem=MenuItemImage::create("xx.png","xx.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	showAkinditem->setTag(102);
	showAkinditem->setPosition(ccp(220,600));
	menu->addChild(showAkinditem);
    
	auto moneypic=Sprite::create("gold.png");
	moneypic->setPosition(ccp(800,600));
	this->addChild(moneypic,1);

	moneylab= Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30); 
    moneylab->setPosition(ccp(750,600));
    this->addChild(moneylab, 1);

	initMainFace();
    return true;
}

void Gamepanel::initMainFace()
{
	MainFaceBg=Sprite::create("mainbg.png");
	MainFaceBg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(MainFaceBg);

	Heroskeleton = SkeletonAnimation::createWithFile("spineboy.json", "spineboy.atlas", 0.3f);
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
	Heroskeleton->setAnimation(0, "walk", true);
	Heroskeleton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2-200));
	addChild(Heroskeleton);
	
	Jewel=MenuItemImage::create("uimainface/11.png","uimainface/11.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Jewel->setPosition(Vec2(900,600));
	addChild(Jewel);
	Vitality=MenuItemImage::create("uimainface/12.png","uimainface/12.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Vitality->setPosition(Vec2(1000,600));
	addChild(Vitality);
	RankList=MenuItemImage::create("uimainface/1.png","uimainface/1.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	RankList->setPosition(Vec2(100,350));
	addChild(RankList);
	Pets=MenuItemImage::create("uimainface/2.png","uimainface/2.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Pets->setPosition(Vec2(100,150));
	addChild(Pets);
	Forge=MenuItemImage::create("uimainface/3.png","uimainface/3.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Forge->setPosition(Vec2(250,280));
	addChild(Forge);
	Shop=MenuItemImage::create("uimainface/3.png","uimainface/3.png",CC_CALLBACK_1(Gamepanel::allbuttoncallback,this));
	Forge->setPosition(Vec2(250,280));
	addChild(Forge);
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
		bagbg->setPosition(Vec2(visibleSize.width/2+100,visibleSize.height - bagbg->getContentSize().height));
		this->addChild(bagbg,1);
		bagclose->setPosition(Vec2(visibleSize.width/2+280,visibleSize.height - bagbg->getContentSize().height+200));
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
	scrollView->setPosition(ccp(visibleSize.width/2-50,visibleSize.height/2-250));
    
    scrollView->setViewSize(Size(360, 400));
    continerLayer->setContentSize(Size(400, 400));
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
		int x=i%4*80+40;
		int y=330-i/4*80;
		Item *tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		tempbgt->pic->setPosition(ccp(x,y));
		menuitem->addChild(tempbgt->pic);
		log(tempbgt->id.c_str());
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
