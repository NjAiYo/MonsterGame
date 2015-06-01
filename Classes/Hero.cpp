#include "Hero.h"
#include "Gamepanel.h"
#include "ItemData.h"
#include "Item.h"
#include "CsvUtil.h"
#include "TalentPoint.h"
Hero *Hero::hero=nullptr;
Hero *Hero::getInstance()
{
	if(hero==nullptr)
	{
		hero=new Hero();
        if(hero&&hero->init())
        {
            hero->autorelease();
            hero->retain();
        }
        else
        {
            CC_SAFE_DELETE(hero);
            hero=nullptr;
        }
	}
	return hero;
}

bool Hero::init()
{
    return true;
}

void Hero::initAllProperties()
{
    capacitance=20;
	Money=0;
	skillpoint=3;
	Exp=1000;
	NeckLace=nullptr;
	Ring1=nullptr;
	Ring2=nullptr;
	Weapon1=ItemData::getInstance()->Allbagitemvec.at(1);
	Weapon2=ItemData::getInstance()->Allbagitemvec.at(0);;
	Pet1=nullptr;
	Pet2=nullptr;
	Pet3=nullptr;
	level=1;
	HP=(int)(100*level*1.1);
	gong_ji_li_dao=Weapon1->ping_jun_gong_ji_li;
	gong_ji_li_qiang=Weapon2->ping_jun_gong_ji_li;
	fang_yu_li=5;
	bao_ji=0.05;
	bao_ji_shang_hai=1;
	shan_bi_lv=0;
	ming_zhong_lv=0.75;
	xing_yun_zhi=10;
	dan_yao_zhi=100;
	nai_jiu_zhi=100;
	neng_liang_zhi=100;
	qiang_xuan_yun_ji_lv=0.05;
	jin_bi_e_wai_diao_luo_lv=0;
	xue_qiu_shi_qu_liang=0;
	neng_liang_qiu_shi_qu_liang=0;
	dan_yao_shi_qu_liang=0;
	jin_yan_zhi=0;
	jin_yan_zhi_huo_de_liang=0;
	neng_liang_huo_de=0;
	lian_ji_shu=0;
	te_shu_ji_xiao_hao_jian_di=0;
	xi_xue_gai_lv=0;
	xi_xue_liang=0;
	gong_ji_li_bai_fen_bi=0;
	HP_bai_fen_bi=0;
	wu_qi_xiang_kong=0;

	for(int i=0;i<12;i++)
	{
		isEquip[i]=0;
	}
	isEquip[3]=1;
	isEquip[4]=1;

	initTalentData();
}

void Hero::updateProperties()
{
	level=log10(1.29*Exp/1000)/log10(1.29);
	HP=(int)(100*level*1.1)+(TalentData.at(0)->state==1?TalentData.at(0)->addvalue:0);
	gong_ji_li_dao=Weapon1->ping_jun_gong_ji_li;
	gong_ji_li_qiang=Weapon2->ping_jun_gong_ji_li;
	fang_yu_li=Weapon1->fang_yu_li+Weapon2->fang_yu_li+(NeckLace==nullptr?0:NeckLace->fang_yu_li)+(Ring1==nullptr?0:Ring1->fang_yu_li)+(Ring2==nullptr?0:Ring2->fang_yu_li);

}

void Hero::initJueseFace()
{
	if(Gamepanel::LayerSwitch_A==0)
	{
		Gamepanel::gamepanel->Layer_A=Node::create();
		Gamepanel::gamepanel->addChild(Gamepanel::gamepanel->Layer_A,1);

		auto mask=Sprite::create("mask.png");
		mask->setScale(100);
		Gamepanel::gamepanel->Layer_A->addChild(mask);

		auto juesebg=Sprite::createWithSpriteFrameName("yxdt.png");
		juesebg->setPosition(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2);
		juesebg->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(juesebg);

		if(Gamepanel::LayerSwitch_C==0)
		{
			Gamepanel::LayerSwitch_C=1;
			Gamepanel::gamepanel->Layer_C=Node::create();
			Gamepanel::gamepanel->addChild(Gamepanel::gamepanel->Layer_C,2);
		}

		shuxingface();

		di=Sprite::createWithSpriteFrameName("xyk1.png");
		di->setPosition(Vec2(1510*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		di->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(di);

		auto beiying=Sprite::createWithSpriteFrameName("bgxwg.png");
		beiying->setPosition(Vec2(270,300));
		beiying->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(beiying);

		auto title=Sprite::createWithSpriteFrameName("biaotibeijing.png");
		title->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2+550*Gamepanel::scaleFactory));
		auto tiletext=Sprite::createWithSpriteFrameName("yxwz.png");
		tiletext->setPosition(Vec2(title->getContentSize().width/2,title->getContentSize().height/2));
		title->addChild(tiletext);
		title->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(title);

		auto taizi=Sprite::createWithSpriteFrameName("yxdz.png");
		taizi->setPosition(Vec2(270,225));
		taizi->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(taizi);

		Gamepanel::gamepanel->Heroskeleton->setPosition(Vec2(270,180));
		Gamepanel::gamepanel->Heroskeleton->setZOrder(1);

		auto dibu=Sprite::createWithSpriteFrameName("djldt.png");
		dibu->setPosition(Vec2(270,100));
		dibu->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(dibu);

		auto escface=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		escface->setNormalImage(Sprite::createWithSpriteFrameName("guanbi.png"));
		escface->setSelectedImage(Sprite::createWithSpriteFrameName("guanbi.png"));
		escface->setPosition(Vec2(1020*2*Gamepanel::scaleFactory,550*2*Gamepanel::scaleFactory));
		escface->setScale(Gamepanel::scaleFactory);
		escface->setTag(ButtonType_ESCFACE);

		auto necklace=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		necklace->setNormalImage(Sprite::createWithSpriteFrameName("span1.png"));
		necklace->setSelectedImage(Sprite::createWithSpriteFrameName("span1.png"));
		necklace->setDisabledImage(Sprite::createWithSpriteFrameName("span2.png"));
		necklace->setScale(Gamepanel::scaleFactory);
		necklace->setPosition(ccp(110,490));
		necklace->setTag(ButtonType_NECKLACE);
		//if(level<=2)
			//necklace->setEnabled(false);

		auto ringa=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		ringa->setNormalImage(Sprite::createWithSpriteFrameName("span1.png"));
		ringa->setSelectedImage(Sprite::createWithSpriteFrameName("span1.png"));
		ringa->setDisabledImage(Sprite::createWithSpriteFrameName("span2.png"));
		ringa->setScale(Gamepanel::scaleFactory);
		ringa->setPosition(ccp(110,400));
		ringa->setTag(ButtonType_RINGA);
		if(level<=2)
			ringa->setEnabled(false);

		auto ringb=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		ringb->setNormalImage(Sprite::createWithSpriteFrameName("span1.png"));
		ringb->setSelectedImage(Sprite::createWithSpriteFrameName("span1.png"));
		ringb->setDisabledImage(Sprite::createWithSpriteFrameName("span2.png"));
		ringb->setScale(Gamepanel::scaleFactory);
		ringb->setPosition(ccp(110,310));
		ringb->setTag(ButtonType_RINGB);
		if(level<=2)
			ringb->setEnabled(false);

		auto equipa=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		equipa->setNormalImage(Sprite::createWithSpriteFrameName("wqan1.png"));
		equipa->setSelectedImage(Sprite::createWithSpriteFrameName("wqan1.png"));
		equipa->setPosition(ccp(115,210));
		equipa->setScale(Gamepanel::scaleFactory);
		equipa->setTag(ButtonType_EQUIPA);

		if(isEquip[3]==1)
		{
			showpic[3]=Sprite::create("zbqiang.png");//可以用weapon->picname加上一个字符组成新图的名称，来处理
			showpic[3]->setPosition(Vec2(115,210));
			showpic[3]->setScale(Gamepanel::scaleFactory);
			Gamepanel::gamepanel->Layer_A->addChild(showpic[3],3);
		}

		auto peta=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		peta->setNormalImage(Sprite::createWithSpriteFrameName("span1.png"));
		peta->setSelectedImage(Sprite::createWithSpriteFrameName("span1.png"));
		peta->setDisabledImage(Sprite::createWithSpriteFrameName("span2.png"));
		peta->setScale(Gamepanel::scaleFactory);
		peta->setPosition(ccp(430,490));
		peta->setTag(ButtonType_PETA);
		if(level<=2)
			peta->setEnabled(false);

		auto petb=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		petb->setNormalImage(Sprite::createWithSpriteFrameName("span1.png"));
		petb->setSelectedImage(Sprite::createWithSpriteFrameName("span1.png"));
		petb->setDisabledImage(Sprite::createWithSpriteFrameName("span2.png"));
		petb->setScale(Gamepanel::scaleFactory);
		petb->setPosition(ccp(430,400));
		petb->setTag(ButtonType_PETB);
		if(level<=2)
			petb->setEnabled(false);

		auto petc=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		petc->setNormalImage(Sprite::createWithSpriteFrameName("span1.png"));
		petc->setSelectedImage(Sprite::createWithSpriteFrameName("span1.png"));
		petc->setDisabledImage(Sprite::createWithSpriteFrameName("span2.png"));
		petc->setScale(Gamepanel::scaleFactory);
		petc->setPosition(ccp(430,310));
		petc->setTag(ButtonType_PETC);
		if(level<=2)
			petc->setEnabled(false);

		auto equipb=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		equipb->setNormalImage(Sprite::createWithSpriteFrameName("wqan1.png"));
		equipb->setSelectedImage(Sprite::createWithSpriteFrameName("wqan1.png"));
		equipb->setPosition(ccp(425,210));
		equipb->setScale(Gamepanel::scaleFactory);
		equipb->setTag(ButtonType_EQUIPB);

		if(isEquip[4]==1)
		{
			showpic[4]=Sprite::create("zbdao.png");
			showpic[4]->setPosition(Vec2(425,210));
			showpic[4]->setScale(Gamepanel::scaleFactory);
			Gamepanel::gamepanel->Layer_A->addChild(showpic[4],3);
		}

		auto zhudonga=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		zhudonga->setNormalImage(Sprite::createWithSpriteFrameName("djan1.png"));
		zhudonga->setSelectedImage(Sprite::createWithSpriteFrameName("djan1.png"));
		zhudonga->setDisabledImage(Sprite::createWithSpriteFrameName("djan2.png"));
		zhudonga->setScale(Gamepanel::scaleFactory);
		zhudonga->setPosition(ccp(120,100));
		zhudonga->setTag(ButtonType_ZHUDONGA);

		auto beidonga=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		beidonga->setNormalImage(Sprite::createWithSpriteFrameName("djan1.png"));
		beidonga->setSelectedImage(Sprite::createWithSpriteFrameName("djan1.png"));
		beidonga->setDisabledImage(Sprite::createWithSpriteFrameName("djan2.png"));
		beidonga->setScale(Gamepanel::scaleFactory);
		beidonga->setPosition(ccp(220,100));
		beidonga->setTag(ButtonType_ZHUDONGA);

		auto zhudongb=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		zhudongb->setNormalImage(Sprite::createWithSpriteFrameName("djan1.png"));
		zhudongb->setSelectedImage(Sprite::createWithSpriteFrameName("djan1.png"));
		zhudongb->setDisabledImage(Sprite::createWithSpriteFrameName("djan2.png"));
		zhudongb->setScale(Gamepanel::scaleFactory);
		zhudongb->setPosition(ccp(320,100));
		zhudongb->setTag(ButtonType_ZHUDONGA);
		if(level<=2)
			zhudongb->setEnabled(false);

		auto beidongb=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		beidongb->setNormalImage(Sprite::createWithSpriteFrameName("djan1.png"));
		beidongb->setSelectedImage(Sprite::createWithSpriteFrameName("djan1.png"));
		beidongb->setDisabledImage(Sprite::createWithSpriteFrameName("djan2.png"));
		beidongb->setScale(Gamepanel::scaleFactory);
		beidongb->setPosition(ccp(420,100));
		beidongb->setTag(ButtonType_ZHUDONGA);
		if(level<=2)
			beidongb->setEnabled(false);


		shuxing=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		shuxing->setNormalImage(Sprite::createWithSpriteFrameName("yxsx1.png"));
		shuxing->setSelectedImage(Sprite::createWithSpriteFrameName("yxsx1.png"));
		shuxing->setDisabledImage(Sprite::createWithSpriteFrameName("yxsx2.png"));
		shuxing->setScale(Gamepanel::scaleFactory);
		shuxing->setPosition(Vec2(1135*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		shuxing->setTag(ButtonType_SHUXING);
		shuxing->setEnabled(false);

		jineng=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		jineng->setNormalImage(Sprite::createWithSpriteFrameName("yxjn1.png"));
		jineng->setSelectedImage(Sprite::createWithSpriteFrameName("yxjn1.png"));
		jineng->setDisabledImage(Sprite::createWithSpriteFrameName("yxjn2.png"));
		jineng->setScale(Gamepanel::scaleFactory);
		jineng->setPosition(Vec2(1501*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		jineng->setTag(ButtonType_JINENG);

		tianfu=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
		tianfu->setNormalImage(Sprite::createWithSpriteFrameName("yxtf1.png"));
		tianfu->setSelectedImage(Sprite::createWithSpriteFrameName("yxtf1.png"));
		tianfu->setDisabledImage(Sprite::createWithSpriteFrameName("yxtf2.png"));
		tianfu->setScale(Gamepanel::scaleFactory);
		tianfu->setPosition(Vec2(1867*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		tianfu->setTag(ButtonType_TIANFU);

		auto menuA=Menu::create(escface,necklace,ringa,ringb,equipa,peta,petb,petc,equipb,zhudonga,beidonga,zhudongb,beidongb,shuxing,jineng,tianfu,NULL);
		menuA->setPosition (Vec2::ZERO);

		Gamepanel::gamepanel->Layer_A->addChild(menuA,2);
		Gamepanel::LayerSwitch_A=1;
		Gamepanel::JueseSysytem=1;
	}

}

void Hero::initEquipmentpanel(int kind)
{
	if(Gamepanel::LayerSwitch_B==1)
		return;

		//为了解决层之间的冲突
		shuxing->setEnabled(false);
		jineng->setEnabled(true);
		tianfu->setEnabled(true);
		Gamepanel::gamepanel->Layer_A->removeChild(di);
		di=Sprite::createWithSpriteFrameName("xyk1.png");
		di->setPosition(Vec2(1510*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		di->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(di);
		shuxingface();
	
	Gamepanel::LayerSwitch_B=1;
	Gamepanel::gamepanel->Layer_B=Node::create();
	Gamepanel::gamepanel->addChild(Gamepanel::gamepanel->Layer_B,4);

	auto mask=Sprite::create("mask.png");
	mask->setScale(100);
	Gamepanel::gamepanel->Layer_B->addChild(mask);

	auto bg=Sprite::createWithSpriteFrameName("zbtcdt.png");
	bg->setPosition(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2);
	bg->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_B->addChild(bg);

	auto dikuang=Sprite::createWithSpriteFrameName("zbxqdt.png");
	dikuang->setPosition(Vec2(650*Gamepanel::scaleFactory,700*Gamepanel::scaleFactory));
	dikuang->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_B->addChild(dikuang);

	auto escpanel=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
	escpanel->setNormalImage(Sprite::createWithSpriteFrameName("guanbi.png"));
	escpanel->setSelectedImage(Sprite::createWithSpriteFrameName("guanbi.png"));
	escpanel->setPosition(950,500);
	escpanel->setScale(Gamepanel::scaleFactory);
	escpanel->setTag(ButtonType_ESCPANEL);

	auto equip=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
	equip->setNormalImage(Sprite::createWithSpriteFrameName("zban1.png"));
	equip->setSelectedImage(Sprite::createWithSpriteFrameName("zban1.png"));
	equip->setPosition(Vec2(500*Gamepanel::scaleFactory,350*Gamepanel::scaleFactory));
	equip->setScale(Gamepanel::scaleFactory);
	equip->setTag(ButtonType_EQUIP);

	auto qianghua=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
	qianghua->setNormalImage(Sprite::createWithSpriteFrameName("qh1.png"));
	qianghua->setSelectedImage(Sprite::createWithSpriteFrameName("qh1.png"));
	qianghua->setPosition(Vec2(800*Gamepanel::scaleFactory,350*Gamepanel::scaleFactory));
	qianghua->setScale(Gamepanel::scaleFactory);
	qianghua->setTag(ButtonType_QIANGHUA);

	auto menuB=Menu::create(escpanel,equip,qianghua,NULL);
	menuB->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->Layer_B->addChild(menuB,2);

	Gamepanel::gamepanel->scrollView1 = extension::ScrollView::create();
	Gamepanel::gamepanel->continerLayer1 = Layer::create();
    Gamepanel::gamepanel->continerLayer1->setAnchorPoint(Vec2(0,0));
    Gamepanel::gamepanel->continerLayer1->setPosition(Vec2(0,0));
	Gamepanel::gamepanel->scrollView1->setPosition(Vec2(985*Gamepanel::scaleFactory,266*Gamepanel::scaleFactory));
    
	Gamepanel::gamepanel->scrollView1->setViewSize(Size(880*Gamepanel::scaleFactory, 715*Gamepanel::scaleFactory));
	int equipnum=0;//该装备道具的个数
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{			
		auto tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		if(tempbgt->kind==kind)
			equipnum++;
	}

	int bagline=0;
	if(equipnum<=12)
	{
		Gamepanel::gamepanel->continerLayer1->setContentSize(Size(880*Gamepanel::scaleFactory, 715*Gamepanel::scaleFactory));
	}
	else
	{
		bagline=(equipnum-12)%4==0? (equipnum-12)/5:(equipnum-12)/5+1;
		Gamepanel::gamepanel->continerLayer1->setContentSize(Size(880*Gamepanel::scaleFactory,715*Gamepanel::scaleFactory+220*bagline*Gamepanel::scaleFactory));
		Gamepanel::gamepanel->continerLayer1->setPosition(Vec2(0,-220*bagline*Gamepanel::scaleFactory));
	}
	Gamepanel::gamepanel->scrollView1->setContentSize(Gamepanel::gamepanel->continerLayer1->getContentSize());
    Gamepanel::gamepanel->scrollView1->setContainer(Gamepanel::gamepanel->continerLayer1);
    
    Gamepanel::gamepanel->scrollView1->setTouchEnabled(true);
	Gamepanel::gamepanel->scrollView1->setDirection(extension::ScrollView::Direction::VERTICAL);
	Gamepanel::gamepanel->scrollView1->setBounceable(true);
    Gamepanel::gamepanel->scrollView1->setDelegate(Gamepanel::gamepanel);
    
	Gamepanel::gamepanel->Layer_B->addChild(Gamepanel::gamepanel->scrollView1,1);

	Gamepanel::gamepanel->menuitem1=Mymenu::create();
	Gamepanel::gamepanel->menuitem1->setAnchorPoint(Vec2::ZERO);
	Gamepanel::gamepanel->menuitem1->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->continerLayer1->addChild(Gamepanel::gamepanel->menuitem1,1);

	Gamepanel::gamepanel->menuitem1->removeAllChildren();
	for(int i=0;i<12+bagline*4;i++)
	{
		int x=i%4*110+60;
		int y=280-i/4*110;
		auto kuangzi=Sprite::createWithSpriteFrameName("wupinkuang.png");
		kuangzi->setScale(Gamepanel::scaleFactory);
		kuangzi->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+bagline*220*Gamepanel::scaleFactory));
		Gamepanel::gamepanel->continerLayer1->addChild(kuangzi);
	}

	int tempi=0;
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{			
		auto tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		if(tempbgt->kind==kind&&tempbgt->isopen==1)
		{
			int x=tempi%4*110+60;
			int y=280-tempi/4*110;
			tempbgt->pic->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+bagline*220*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->menuitem1->addChild(tempbgt->pic);
			tempi++;
		}
	}



}

void Hero::shouEquipmentdata(Item *item)
{
	Gamepanel::gamepanel->Layer_B->removeChild(Gamepanel::gamepanel->Layer_D);
	Gamepanel::gamepanel->Layer_D=Node::create();
	Gamepanel::gamepanel->Layer_B->addChild(Gamepanel::gamepanel->Layer_D);
	
	auto namelab=Label::createWithSystemFont("SUPER SOWRD(+2)","fonts/arial.ttf",20);
	namelab->setColor(Color3B::GREEN);
	namelab->setPosition(ccp(650*Gamepanel::scaleFactory,880*Gamepanel::scaleFactory));
	Gamepanel::gamepanel->Layer_D->addChild(namelab);

	char miaoshu[50];
	const char *path="pn.csv";
	CsvUtil::getInstance()->loadFile(path);
	Value v1=CsvUtil::getInstance()->getValue(0,0,path);
	sprintf(miaoshu,":%.2f-%.2f",item->xia_xian_gong_ji_li,item->shang_xian_gong_ji_li);
	auto lab1=Label::create(v1.asString()+miaoshu,"",12);
	lab1->setPosition(ccp(260,370));
	Gamepanel::gamepanel->Layer_D->addChild(lab1);
	int templineb=1;
		if(item->gong_ji_li_jia_cheng!=0)
		{
			sprintf(miaoshu,":+%g%%",item->gong_ji_li_jia_cheng*100);
			Value v1=CsvUtil::getInstance()->getValue(0,1,path);
			auto templab=Label::create(v1.asString()+miaoshu,"",15);
			templab->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab,2);
			templineb++;
		}
		if(item->HP_shangxian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->HP_shangxian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,2,path);
			auto templab1=Label::create(v1.asString()+miaoshu,"",15);
			templab1->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab1,2);
			templineb++;
		}
		if(item->fang_yu_li!=0)
		{
			sprintf(miaoshu,":+%d",item->fang_yu_li);
			Value v1=CsvUtil::getInstance()->getValue(0,3,path);
			auto templab2=Label::create(v1.asString()+miaoshu,"",15);
			templab2->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab2,2);
			templineb++;
		}
		if(item->bao_ji_lv!=0)
		{
			sprintf(miaoshu,":+ %g%%",item->bao_ji_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,4,path);
			auto templab3=Label::create(v1.asString()+miaoshu,"",15);
			templab3->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab3,2);
			templineb++;
		}
		if(item->bao_ji_shang_hai!=0)
		{
			sprintf(miaoshu,":+%g%%",item->bao_ji_shang_hai*100);
			Value v1=CsvUtil::getInstance()->getValue(0,5,path);
			auto templab4=Label::create(v1.asString()+miaoshu,"",15);
			templab4->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab4,2);
			templineb++;
		}
		if(item->dan_yao_shang_xian!=0)
		{
			sprintf(miaoshu,":+%d",item->dan_yao_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,6,path);
			auto templab5=Label::create(v1.asString()+miaoshu,"",15);
			templab5->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab5,2);
			templineb++;
		}
		if(item->nai_jiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%d",item->nai_jiu_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,7,path);
			auto templab6=Label::create(v1.asString()+miaoshu,"",15);
			templab6->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab6,2);
			templineb++;
		}
		if(item->qiang_xuan_yun_gai_lv!=0)
		{
			sprintf(miaoshu,":+%g%%",item->qiang_xuan_yun_gai_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,8,path);
			auto templab7=Label::create(v1.asString()+miaoshu,"",15);
			templab7->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab7,2);
			templineb++;
		}
		if(item->shi_qu_xue_qiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->shi_qu_xue_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,9,path);
			auto templab8=Label::create(v1.asString()+miaoshu,"",15);
			templab8->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab8,2);
			templineb++;
		}
		if(item->shi_qu_neng_liang_qiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->shi_qu_neng_liang_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,10,path);
			auto templab9=Label::create(v1.asString()+miaoshu,"",15);
			templab9->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab9,2);
			templineb++;
		}
		if(item->shi_qu_dan_yao_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->shi_qu_dan_yao_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,11,path);
			auto templab10=Label::create(v1.asString()+miaoshu,"",15);
			templab10->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab10,2);
			templineb++;
		}
		if(item->wu_qi_xiang_qian!=0)
		{
			sprintf(miaoshu,":+ %d",item->wu_qi_xiang_qian);
			Value v1=CsvUtil::getInstance()->getValue(0,12,path);
			auto templab11=Label::create(v1.asString()+miaoshu,"",15);
			templab11->setPosition(ccp(260,370-15*templineb));
			Gamepanel::gamepanel->Layer_D->addChild(templab11,2);
			templineb++;
		}
}

void Hero::compareEquipment(Item *item)
{
	Gamepanel::gamepanel->Layer_B->removeChild(Gamepanel::gamepanel->Layer_C);
	Gamepanel::gamepanel->Layer_C=Node::create();
	Gamepanel::gamepanel->Layer_B->addChild(Gamepanel::gamepanel->Layer_C);

	auto leftpic=Sprite::create("wuqi1.png");
	leftpic->setPosition(ccp(270,430));
	Gamepanel::gamepanel->Layer_C->addChild(leftpic);

	auto rightlab=Label::createWithSystemFont("Sowrd level:3","fonts/arial.ttf",20);
	rightlab->setColor(Color3B::BLACK);
	rightlab->setPosition(ccp(350,430));
	Gamepanel::gamepanel->Layer_C->addChild(rightlab);

	char miaoshu[100];
	const char *path="pn.csv";
	CsvUtil::getInstance()->loadFile(path);
	Value v1=CsvUtil::getInstance()->getValue(0,0,path);
	auto lab1=Label::create(v1.asString(),"",12);
	lab1->setPosition(ccp(260,370));
	Gamepanel::gamepanel->Layer_C->addChild(lab1);
	int templine=1;
		if(Weapon1->gong_ji_li_jia_cheng!=0)
		{
			sprintf(miaoshu,":+%g%%",Weapon1->gong_ji_li_jia_cheng*100);
			Value v1=CsvUtil::getInstance()->getValue(0,1,path);
			auto templab=Label::create(v1.asString()+miaoshu,"",15);
			templab->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab,2);
			templine++;
		}
		if(Weapon1->HP_shangxian!=0)
		{
			sprintf(miaoshu,":+%g%%",Weapon1->HP_shangxian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,2,path);
			auto templab1=Label::create(v1.asString()+miaoshu,"",15);
			templab1->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab1,2);
			templine++;
		}
		if(Weapon1->fang_yu_li!=0)
		{
			sprintf(miaoshu,":+%d",Weapon1->fang_yu_li);
			Value v1=CsvUtil::getInstance()->getValue(0,3,path);
			auto templab2=Label::create(v1.asString()+miaoshu,"",15);
			templab2->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab2,2);
			templine++;
		}
		if(Weapon1->bao_ji_lv!=0)
		{
			sprintf(miaoshu,":+ %g%%",Weapon1->bao_ji_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,4,path);
			auto templab3=Label::create(v1.asString()+miaoshu,"",15);
			templab3->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab3,2);
			templine++;
		}
		if(Weapon1->bao_ji_shang_hai!=0)
		{
			sprintf(miaoshu,":+%g%%",Weapon1->bao_ji_shang_hai*100);
			Value v1=CsvUtil::getInstance()->getValue(0,5,path);
			auto templab4=Label::create(v1.asString()+miaoshu,"",15);
			templab4->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab4,2);
			templine++;
		}
		if(Weapon1->dan_yao_shang_xian!=0)
		{
			sprintf(miaoshu,":+%d",Weapon1->dan_yao_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,6,path);
			auto templab5=Label::create(v1.asString()+miaoshu,"",15);
			templab5->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab5,2);
			templine++;
		}
		if(Weapon1->nai_jiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%d",Weapon1->nai_jiu_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,7,path);
			auto templab6=Label::create(v1.asString()+miaoshu,"",15);
			templab6->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab6,2);
			templine++;
		}
		if(Weapon1->qiang_xuan_yun_gai_lv!=0)
		{
			sprintf(miaoshu,":+%g%%",Weapon1->qiang_xuan_yun_gai_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,8,path);
			auto templab7=Label::create(v1.asString()+miaoshu,"",15);
			templab7->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab7,2);
			templine++;
		}
		if(Weapon1->shi_qu_xue_qiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",Weapon1->shi_qu_xue_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,9,path);
			auto templab8=Label::create(v1.asString()+miaoshu,"",15);
			templab8->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab8,2);
			templine++;
		}
		if(Weapon1->shi_qu_neng_liang_qiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",Weapon1->shi_qu_neng_liang_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,10,path);
			auto templab9=Label::create(v1.asString()+miaoshu,"",15);
			templab9->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab9,2);
			templine++;
		}
		if(Weapon1->shi_qu_dan_yao_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",Weapon1->shi_qu_dan_yao_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,11,path);
			auto templab10=Label::create(v1.asString()+miaoshu,"",15);
			templab10->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab10,2);
			templine++;
		}
		if(Weapon1->wu_qi_xiang_qian!=0)
		{
			sprintf(miaoshu,":+ %d",Weapon1->wu_qi_xiang_qian);
			Value v1=CsvUtil::getInstance()->getValue(0,12,path);
			auto templab11=Label::create(v1.asString()+miaoshu,"",15);
			templab11->setPosition(ccp(260,370-15*templine));
			Gamepanel::gamepanel->Layer_C->addChild(templab11,2);
			templine++;
		}


	int templineb=1;
		if(item->gong_ji_li_jia_cheng!=0)
		{
			sprintf(miaoshu,":+%g%%",item->gong_ji_li_jia_cheng*100);
			Value v1=CsvUtil::getInstance()->getValue(0,1,path);
			auto templab=Label::create(v1.asString()+miaoshu,"",15);
			templab->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab,2);
			templineb++;
		}
		if(item->HP_shangxian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->HP_shangxian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,2,path);
			auto templab1=Label::create(v1.asString()+miaoshu,"",15);
			templab1->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab1,2);
			templineb++;
		}
		if(item->fang_yu_li!=0)
		{
			sprintf(miaoshu,":+%d",item->fang_yu_li);
			Value v1=CsvUtil::getInstance()->getValue(0,3,path);
			auto templab2=Label::create(v1.asString()+miaoshu,"",15);
			templab2->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab2,2);
			templineb++;
		}
		if(item->bao_ji_lv!=0)
		{
			sprintf(miaoshu,":+ %g%%",item->bao_ji_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,4,path);
			auto templab3=Label::create(v1.asString()+miaoshu,"",15);
			templab3->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab3,2);
			templineb++;
		}
		if(item->bao_ji_shang_hai!=0)
		{
			sprintf(miaoshu,":+%g%%",item->bao_ji_shang_hai*100);
			Value v1=CsvUtil::getInstance()->getValue(0,5,path);
			auto templab4=Label::create(v1.asString()+miaoshu,"",15);
			templab4->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab4,2);
			templineb++;
		}
		if(item->dan_yao_shang_xian!=0)
		{
			sprintf(miaoshu,":+%d",item->dan_yao_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,6,path);
			auto templab5=Label::create(v1.asString()+miaoshu,"",15);
			templab5->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab5,2);
			templineb++;
		}
		if(item->nai_jiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%d",item->nai_jiu_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,7,path);
			auto templab6=Label::create(v1.asString()+miaoshu,"",15);
			templab6->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab6,2);
			templineb++;
		}
		if(item->qiang_xuan_yun_gai_lv!=0)
		{
			sprintf(miaoshu,":+%g%%",item->qiang_xuan_yun_gai_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,8,path);
			auto templab7=Label::create(v1.asString()+miaoshu,"",15);
			templab7->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab7,2);
			templineb++;
		}
		if(item->shi_qu_xue_qiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->shi_qu_xue_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,9,path);
			auto templab8=Label::create(v1.asString()+miaoshu,"",15);
			templab8->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab8,2);
			templineb++;
		}
		if(item->shi_qu_neng_liang_qiu_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->shi_qu_neng_liang_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,10,path);
			auto templab9=Label::create(v1.asString()+miaoshu,"",15);
			templab9->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab9,2);
			templineb++;
		}
		if(item->shi_qu_dan_yao_shang_xian!=0)
		{
			sprintf(miaoshu,":+%g%%",item->shi_qu_dan_yao_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,11,path);
			auto templab10=Label::create(v1.asString()+miaoshu,"",15);
			templab10->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab10,2);
			templineb++;
		}
		if(item->wu_qi_xiang_qian!=0)
		{
			sprintf(miaoshu,":+ %d",item->wu_qi_xiang_qian);
			Value v1=CsvUtil::getInstance()->getValue(0,12,path);
			auto templab11=Label::create(v1.asString()+miaoshu,"",15);
			templab11->setPosition(ccp(400,370-15*templineb));
			Gamepanel::gamepanel->Layer_C->addChild(templab11,2);
			templineb++;
		}


	sprintf(miaoshu,"%.2f",Weapon1->ping_jun_gong_ji_li);
	auto lba1=Label::create(miaoshu,"",12);
	lba1->setPosition(ccp(350,370));
	Gamepanel::gamepanel->Layer_C->addChild(lba1);
	sprintf(miaoshu,"%.2f",item->ping_jun_gong_ji_li);
	auto lbb1=Label::create(miaoshu,"",12);
	lbb1->setPosition(ccp(450,370));
	Gamepanel::gamepanel->Layer_C->addChild(lbb1);
	if(Weapon1->ping_jun_gong_ji_li>item->ping_jun_gong_ji_li)
	{
		lba1->setColor(Color3B::GREEN);
	}
	else if(Weapon1->ping_jun_gong_ji_li<item->ping_jun_gong_ji_li)
	{
		lbb1->setColor(Color3B::GREEN);
	}
}

void Hero::equipe_item(int kind)
{
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{
		Item *temp=ItemData::getInstance()->Allbagitemvec.at(i);
		if(temp->isselect==1&&temp->isusing==0&&temp->kind==kind)
		{
			temp->isusing=1;
			temp->shiyongzhong=Sprite::create("ui/isusing.png");
			temp->shiyongzhong->setPosition(temp->pic->getContentSize().width/2,temp->pic->getContentSize().height/2);
			temp->pic->addChild(temp->shiyongzhong);
			Weapon1=temp;
		}
		if(temp->isselect==0&&temp->isusing==1&&temp->kind==kind)
		{
			temp->isusing=0;
			temp->pic->removeChild(temp->shiyongzhong);
		}
	}
	updateProperties();
}

void Hero::shuxingface()
{
	Gamepanel::TalentSystem=0;
	Gamepanel::gamepanel->Layer_C->removeAllChildren();
	auto lmrms=Sprite::createWithSpriteFrameName("lmrms.png");
	lmrms->setPosition(Vec2(1510*Gamepanel::scaleFactory,700*Gamepanel::scaleFactory));
	lmrms->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(lmrms);
	auto dixian=Sprite::createWithSpriteFrameName("jsht.png");
	dixian->setPosition(Vec2(1510*Gamepanel::scaleFactory,500*Gamepanel::scaleFactory));
	dixian->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(dixian);
	auto sxditu=Sprite::createWithSpriteFrameName("zsxdt.png");
	sxditu->setPosition(Vec2(1510*Gamepanel::scaleFactory,330*Gamepanel::scaleFactory));
	sxditu->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(sxditu);
	auto sxzitu=Sprite::createWithSpriteFrameName("sxmc.png");
	sxzitu->setPosition(Vec2(1350*Gamepanel::scaleFactory,330*Gamepanel::scaleFactory));
	sxzitu->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(sxzitu);
}

void Hero::jinengface()
{
	Gamepanel::TalentSystem=0;
	Gamepanel::gamepanel->Layer_C->removeAllChildren();
	auto zdjnzitu=Sprite::createWithSpriteFrameName("zdjn.png");
	zdjnzitu->setPosition(Vec2(Vec2(1250*Gamepanel::scaleFactory,800*Gamepanel::scaleFactory)));
	zdjnzitu->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(zdjnzitu);
}

void Hero::tianfuface()
{
	Gamepanel::TalentSystem=1;
	Gamepanel::gamepanel->Layer_C->removeAllChildren();
	Gamepanel::gamepanel->Layer_D=Node::create();//用于天赋弹出的小面板层
	Gamepanel::gamepanel->Layer_C->addChild(Gamepanel::gamepanel->Layer_D,5);

	auto tfdb=Sprite::createWithSpriteFrameName("tfdt.png");
	tfdb->setPosition(Vec2(1510*Gamepanel::scaleFactory,590*Gamepanel::scaleFactory));
	tfdb->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(tfdb);
	
	auto huatiaodi=Sprite::createWithSpriteFrameName("huatiaodi.png");
	huatiaodi->setPosition(Vec2(2000*Gamepanel::scaleFactory,590*Gamepanel::scaleFactory));
	huatiaodi->setScaleX(Gamepanel::scaleFactory);
	huatiaodi->setScaleY(Gamepanel::scaleFactory*1.6);
	Gamepanel::gamepanel->Layer_C->addChild(huatiaodi);

	huatiao=Sprite::createWithSpriteFrameName("huatiao.png");
	huatiao->setPosition(Vec2(2000*Gamepanel::scaleFactory,764*Gamepanel::scaleFactory));
	huatiao->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(huatiao);

	auto tfds=Sprite::createWithSpriteFrameName("tfds.png");
	tfds->setPosition(Vec2(1100*Gamepanel::scaleFactory,240*Gamepanel::scaleFactory));
	tfds->setScale(Gamepanel::scaleFactory);
	Gamepanel::gamepanel->Layer_C->addChild(tfds);

	char temp[5];
	sprintf(temp,"%d",skillpoint);
	skillpointlab=Label::create(temp,"",50*Gamepanel::scaleFactory);
	skillpointlab->setPosition(Vec2(1260*Gamepanel::scaleFactory,240*Gamepanel::scaleFactory));
	skillpointlab->setColor(Color3B::GREEN);
	Gamepanel::gamepanel->Layer_C->addChild(skillpointlab);

	auto chongzhi=MenuItemImage::create("","",CC_CALLBACK_1(Hero::buttoncallback,this));
	chongzhi->setNormalImage(Sprite::createWithSpriteFrameName("cztf.png"));
	chongzhi->setSelectedImage(Sprite::createWithSpriteFrameName("cztf.png"));
	chongzhi->setScale(Gamepanel::scaleFactory);
	chongzhi->setPosition(Vec2(1530*Gamepanel::scaleFactory,240*Gamepanel::scaleFactory));
	chongzhi->setTag(ButtonType_CHONGZHI);
	auto menu=Menu::create(chongzhi,NULL);
	menu->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->Layer_C->addChild(menu);

	Gamepanel::gamepanel->scrollView = extension::ScrollView::create();
	Gamepanel::gamepanel->continerLayer = Layer::create();
	Gamepanel::gamepanel->continerLayer->setAnchorPoint(Vec2(0,0));
	Gamepanel::gamepanel->continerLayer->setPosition(Vec2(0,0));
	Gamepanel::gamepanel->scrollView->setPosition(Vec2(986*Gamepanel::scaleFactory,340*Gamepanel::scaleFactory));

	Gamepanel::gamepanel->scrollView->setViewSize(Size(1046*Gamepanel::scaleFactory, 500*Gamepanel::scaleFactory));
	Gamepanel::gamepanel->continerLayer->setContentSize(Size(1046*Gamepanel::scaleFactory, 519*Gamepanel::scaleFactory+180*3*Gamepanel::scaleFactory));
	Gamepanel::gamepanel->continerLayer->setPosition(Vec2(0,-180*3*Gamepanel::scaleFactory));
	Gamepanel::gamepanel->scrollView->setContentSize(Gamepanel::gamepanel->continerLayer->getContentSize());
	Gamepanel::gamepanel->scrollView->setContainer(Gamepanel::gamepanel->continerLayer);
    
	Gamepanel::gamepanel->scrollView->setTouchEnabled(true);
	Gamepanel::gamepanel->scrollView->setDirection(extension::ScrollView::Direction::VERTICAL);
	Gamepanel::gamepanel->scrollView->setBounceable(true);
	Gamepanel::gamepanel->scrollView->setDelegate(Gamepanel::gamepanel);
	Gamepanel::gamepanel->Layer_C->addChild(Gamepanel::gamepanel->scrollView,1);

	Gamepanel::gamepanel->menuitem=Mymenu::create();
	Gamepanel::gamepanel->menuitem->setAnchorPoint(Vec2::ZERO);
	Gamepanel::gamepanel->menuitem->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->continerLayer->addChild(Gamepanel::gamepanel->menuitem,2);

	for(int i=0;i<TalentData.size();i++)
	{
		int x=i%4*130+60;
		int y=210-i/4*110;
		TalentPoint *tp=TalentData.at(i);
		tp->pic->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory));
		tp->pic->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->menuitem->addChild(tp->pic);

		auto kuangzi=Sprite::createWithSpriteFrameName("tfk.png");
		kuangzi->setScale(Gamepanel::scaleFactory);
		kuangzi->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory));
		Gamepanel::gamepanel->continerLayer->addChild(kuangzi,1);

		if(tp->needpoints==1)
		{
			if(tp->state==-1)
			{
				tp->qiu1=Sprite::createWithSpriteFrameName("hstfd.png");
				tp->qiu1->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu1->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu1,3);
			}
			else
			{
				tp->qiu1=Sprite::createWithSpriteFrameName("lstfd.png");
				tp->qiu1->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu1->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu1,3);
			}
		}
		else if(tp->needpoints==2)
		{
			if(tp->state==-1)
			{
				tp->qiu1=Sprite::createWithSpriteFrameName("hstfd.png");
				tp->qiu1->setPosition(ccp(x*2*Gamepanel::scaleFactory+18*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu1->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu1,3);
				tp->qiu2=Sprite::createWithSpriteFrameName("hstfd.png");
				tp->qiu2->setPosition(ccp(x*2*Gamepanel::scaleFactory-18*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu2->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu2,3);
			}
			else if(tp->state==0)
			{
				tp->qiu1=Sprite::createWithSpriteFrameName("hstfd.png");
				tp->qiu1->setPosition(ccp(x*2*Gamepanel::scaleFactory+18*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu1->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu1,3);
				tp->qiu2=Sprite::createWithSpriteFrameName("lstfd.png");
				tp->qiu2->setPosition(ccp(x*2*Gamepanel::scaleFactory-18*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu2->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu2,3);
			}
			else
			{
				tp->qiu1=Sprite::createWithSpriteFrameName("lstfd.png");
				tp->qiu1->setPosition(ccp(x*2*Gamepanel::scaleFactory+18*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu1->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu1,3);
				tp->qiu2=Sprite::createWithSpriteFrameName("lstfd.png");
				tp->qiu2->setPosition(ccp(x*2*Gamepanel::scaleFactory-18*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+3*180*Gamepanel::scaleFactory-57*Gamepanel::scaleFactory));
				tp->qiu2->setScale(Gamepanel::scaleFactory);
				Gamepanel::gamepanel->continerLayer->addChild(tp->qiu2,3);
			}
		}
	}
}

void Hero::initTalentData()
{
	const char *path="talent.csv";
	CsvUtil::getInstance()->loadFile(path);
	for(int i=0;i<20;i++)
	{
		Value v1=CsvUtil::getInstance()->getValue(i+1,0,path);
		Value v2=CsvUtil::getInstance()->getValue(i+1,1,path);
		Value v3=CsvUtil::getInstance()->getValue(i+1,2,path);
		Value v4=CsvUtil::getInstance()->getValue(i+1,3,path);
		Value v5=CsvUtil::getInstance()->getValue(i+1,4,path);
		Value v6=CsvUtil::getInstance()->getValue(i+1,5,path);

		TalentPoint *tp=new TalentPoint(v1.asInt(),v2.asString(),v3.asString(),v4.asInt(),v5.asFloat(),v6.asInt());
		TalentData.pushBack(tp);
	}
}

void Hero::resetTalent()
{
	for(int i=0;i<TalentData.size();i++)
	{
		if(TalentData.at(i)->needpoints==1&&TalentData.at(i)->state==1)
		{
			TalentData.at(i)->state=-1;
			TalentData.at(i)->currentpoints=1;
			skillpoint++;
		}
		else if(TalentData.at(i)->needpoints==2&&TalentData.at(i)->state==0)
		{
			TalentData.at(i)->state=-1;
			TalentData.at(i)->currentpoints=2;
			skillpoint++;
		}
		else if(TalentData.at(i)->needpoints==2&&TalentData.at(i)->state==1)
		{
			TalentData.at(i)->state=-1;
			TalentData.at(i)->currentpoints=2;
			skillpoint+=2;
		}
	}
}

void Hero::buttoncallback(Ref *pSender)
{
	MenuItemImage* pImage=(MenuItemImage*)pSender;
	int tag = pImage->getTag();
	switch(tag)
	{
	case ButtonType_ESCFACE:
		if(Gamepanel::LayerSwitch_B==0)
		{
			Gamepanel::gamepanel->Layer_A->removeAllChildren();
			Gamepanel::gamepanel->removeChild(Gamepanel::gamepanel->Layer_A);
			Gamepanel::LayerSwitch_A=0;
			Gamepanel::JueseSysytem=0;
			Gamepanel::TalentSystem=0;
			Gamepanel::gamepanel->Heroskeleton->setPosition(Point(Gamepanel::gamepanel->visibleSize.width / 2, Gamepanel::gamepanel->visibleSize.height / 2-400*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Heroskeleton->setZOrder(0);
			Gamepanel::gamepanel->Layer_C->removeAllChildren();
			Gamepanel::gamepanel->removeChild(Gamepanel::gamepanel->Layer_C);
			Gamepanel::LayerSwitch_C=0;
		}
		break;
	case ButtonType_ESCPANEL:
		if(Gamepanel::LayerSwitch_B==1)
		{
			Gamepanel::gamepanel->Layer_B->removeAllChildren();
			Gamepanel::LayerSwitch_B=0;
			Gamepanel::gamepanel->removeChild(Gamepanel::gamepanel->Layer_B);
			for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
			{
				Item *temp=ItemData::getInstance()->Allbagitemvec.at(i);
				if(temp->isselect==1)
				{
					temp->isselect=0;
					temp->pic->removeChild(temp->zhezhao);
				}
			}
		}
		break;
	case ButtonType_EQUIP:
		equipe_item(0);
		break;
	case ButtonType_NECKLACE:
		initEquipmentpanel(10);
		break;
	case ButtonType_EQUIPA:
		initEquipmentpanel(0);
		break;
	case ButtonType_SHUXING:
		shuxing->setEnabled(false);
		jineng->setEnabled(true);
		tianfu->setEnabled(true);
		Gamepanel::gamepanel->Layer_A->removeChild(di);
		di=Sprite::createWithSpriteFrameName("xyk1.png");
		di->setPosition(Vec2(1510*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		di->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(di);

		shuxingface();
		break;
	case ButtonType_JINENG:
		shuxing->setEnabled(true);
		jineng->setEnabled(false);
		tianfu->setEnabled(true);
		Gamepanel::gamepanel->Layer_A->removeChild(di);
		di=Sprite::createWithSpriteFrameName("yxk2.png");
		di->setPosition(Vec2(1510*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		di->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(di);

		jinengface();
		break;
	case ButtonType_TIANFU:
		shuxing->setEnabled(true);
		jineng->setEnabled(true);
		tianfu->setEnabled(false);
		di=Sprite::createWithSpriteFrameName("yxk3.png");
		di->setPosition(Vec2(1510*Gamepanel::scaleFactory,987*Gamepanel::scaleFactory));
		di->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(di);

		tianfuface();
		break;
	case ButtonType_CHONGZHI:
		resetTalent();
		tianfuface();
		break;
	}
}

void Hero::addMoney(int num)
{
	Money+=num;
}