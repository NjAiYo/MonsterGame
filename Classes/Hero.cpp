#include "Hero.h"
#include "Gamepanel.h"
#include "ItemData.h"
#include "Item.h"
#include "CsvUtil.h"
Hero *Hero::hero=nullptr;
Hero *Hero::getInstance()
{
	if(hero==nullptr)
	{
		hero=new Hero();
	} 
	return hero;
}

void Hero::initAllProperties()
{
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
}

void Hero::updateProperties()
{
	level=log10(1.29*Exp/1000)/log10(1.29);
	HP=(int)(100*level*1.1);
	gong_ji_li_dao=Weapon1->ping_jun_gong_ji_li;
	gong_ji_li_qiang=Weapon2->ping_jun_gong_ji_li;
	fang_yu_li=Weapon1->fang_yu_li+Weapon2->fang_yu_li+(NeckLace==nullptr?0:NeckLace->fang_yu_li)+(Ring1==nullptr?0:Ring1->fang_yu_li)+(Ring2==nullptr?0:Ring2->fang_yu_li);

}

void Hero::initJueseFace()
{
	if(Gamepanel::LayerSwitch_A==0)
	{
		Gamepanel::gamepanel->Layer_A=Node::create();
		Gamepanel::gamepanel->addChild(Gamepanel::gamepanel->Layer_A,3);

		auto juesebg=Sprite::create("ui/22.png");
		juesebg->setPosition(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2);
		Gamepanel::gamepanel->Layer_A->addChild(juesebg);

		auto escface=MenuItemImage::create("ui/1.png","ui/1.png",CC_CALLBACK_1(Hero::buttoncallback,this));
		escface->setPosition(ccp(1050,500));
		escface->setTag(ESCFACE);

		auto necklace=MenuItemImage::create("ui/2.png","ui/2.png",CC_CALLBACK_1(Hero::buttoncallback,this));
		necklace->setPosition(ccp(100,450));
		necklace->setTag(NECKLACE);

		auto ringa=MenuItemImage::create("ui/3.png","ui/3.png",CC_CALLBACK_1(Hero::buttoncallback,this));
		ringa->setPosition(ccp(100,350));
		ringa->setTag(RINGA);

		auto ringb=MenuItemImage::create("ui/4.png","ui/4.png",CC_CALLBACK_1(Hero::buttoncallback,this));
		ringb->setPosition(ccp(100,250));
		ringb->setTag(RINGB);

		auto equipa=MenuItemImage::create("ui/5.png","ui/5.png",CC_CALLBACK_1(Hero::buttoncallback,this));
		equipa->setPosition(ccp(100,150));
		equipa->setTag(EQUIPA);

		auto menuA=Menu::create(escface,necklace,ringa,ringb,equipa,NULL);
		menuA->setPosition (Vec2::ZERO);

		Gamepanel::gamepanel->Layer_A->addChild(menuA);
		Gamepanel::LayerSwitch_A=1;
		Gamepanel::JueseSysytem=1;
	}

}


void Hero::initEquipmentpanel(int kind)
{
	Gamepanel::LayerSwitch_B=1;
	Gamepanel::gamepanel->Layer_B=Node::create();
	Gamepanel::gamepanel->addChild(Gamepanel::gamepanel->Layer_B,4);

	auto bg=Sprite::create("ui/33.png");
	bg->setPosition(Gamepanel::gamepanel->visibleSize.width/2,Gamepanel::gamepanel->visibleSize.height/2);
	Gamepanel::gamepanel->Layer_B->addChild(bg);

	auto zuojiemian=Sprite::create("jm.png");
	zuojiemian->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2-200,Gamepanel::gamepanel->visibleSize.height/2));
	Gamepanel::gamepanel->Layer_B->addChild(zuojiemian);

	auto escpanel=MenuItemImage::create("ui/1.png","ui/1.png",CC_CALLBACK_1(Hero::buttoncallback,this));
	escpanel->setPosition(1050,500);
	escpanel->setTag(ESCPANEL);

	auto equip=MenuItemImage::create("zhuangbei.png","zhuangbei.png",CC_CALLBACK_1(Hero::buttoncallback,this));
	equip->setPosition(Vec2(Gamepanel::gamepanel->visibleSize.width/2-260,Gamepanel::gamepanel->visibleSize.height/2-140));
	equip->setTag(EQUIP);

	auto menuB=Menu::create(escpanel,equip,NULL);
	menuB->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->Layer_B->addChild(menuB);

	Gamepanel::gamepanel->scrollView = extension::ScrollView::create();
	Gamepanel::gamepanel->continerLayer = Layer::create();
    Gamepanel::gamepanel->continerLayer->setAnchorPoint(Vec2(0,0));
    Gamepanel::gamepanel->continerLayer->setPosition(Vec2(0,0));
	Gamepanel::gamepanel->scrollView->setPosition(ccp(Gamepanel::gamepanel->visibleSize.width/2-50,Gamepanel::gamepanel->visibleSize.height/2-250));
    
    Gamepanel::gamepanel->scrollView->setViewSize(Size(360, 400));
    Gamepanel::gamepanel->continerLayer->setContentSize(Size(400, 400));
	Gamepanel::gamepanel->scrollView->setContentSize(Gamepanel::gamepanel->continerLayer->getContentSize());
    Gamepanel::gamepanel->scrollView->setContainer(Gamepanel::gamepanel->continerLayer);
    
    Gamepanel::gamepanel->scrollView->setTouchEnabled(true);
	Gamepanel::gamepanel->scrollView->setDirection(extension::ScrollView::Direction::VERTICAL);
	Gamepanel::gamepanel->scrollView->setBounceable(true);
    Gamepanel::gamepanel->scrollView->setDelegate(Gamepanel::gamepanel);
	Gamepanel::gamepanel->Layer_B->addChild(Gamepanel::gamepanel->scrollView,1);

	Gamepanel::gamepanel->menuitem=Mymenu::create();
	Gamepanel::gamepanel->menuitem->setAnchorPoint(Vec2::ZERO);
	Gamepanel::gamepanel->menuitem->setPosition(Vec2::ZERO);
	Gamepanel::gamepanel->continerLayer->addChild(Gamepanel::gamepanel->menuitem);

	Gamepanel::gamepanel->menuitem->removeAllChildren();
	int tempi=0;
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{			
		auto tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
		if(tempbgt->kind==kind&&tempbgt->isopen==1)
		{
			int x=tempi%4*80+40;
			int y=330-tempi/4*80;
			tempbgt->pic->setPosition(ccp(x,y));
			Gamepanel::gamepanel->menuitem->addChild(tempbgt->pic);
			tempi++;
		}
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

void Hero::buttoncallback(Ref *pSender)
{
	MenuItemImage* pImage=(MenuItemImage*)pSender;
	int tag = pImage->getTag();
	switch(tag)
	{
	case ESCFACE:
		if(Gamepanel::LayerSwitch_B==0)
		{
			Gamepanel::gamepanel->Layer_A->removeAllChildren();
			Gamepanel::LayerSwitch_A=0;
			Gamepanel::JueseSysytem=0;
		}
		break;
	case ESCPANEL:
		if(Gamepanel::LayerSwitch_B==1)
		{
			Gamepanel::gamepanel->Layer_B->removeAllChildren();
			Gamepanel::LayerSwitch_B=0;
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
	case EQUIP:	
		equipe_item(0);
		break;
	case NECKLACE:
		initEquipmentpanel(10);
		break;
	case EQUIPA:
		initEquipmentpanel(0);
		break;
	}
}