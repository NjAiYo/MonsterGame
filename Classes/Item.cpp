#include "Item.h"
#include "Gamepanel.h"
#include "CsvUtil.h"
#include "ItemData.h"
#include "Hero.h"
USING_NS_CC;
int Item::randomforproperty=0;
Item::Item(std::string id)
{
	const char *path="test.csv";
	CsvUtil::getInstance()->loadFile(path);
	int line=CsvUtil::getInstance()->findValueInWithLine(id.c_str(),0,path);
	
	Value t1=CsvUtil::getInstance()->getValue(line,1,path);
	Value t2=CsvUtil::getInstance()->getValue(line,2,path);
	Value t3=CsvUtil::getInstance()->getValue(line,3,path);
	Value t4=CsvUtil::getInstance()->getValue(line,4,path);
	Value t5=CsvUtil::getInstance()->getValue(line,5,path);
	Value t6=CsvUtil::getInstance()->getValue(line,6,path);
	Value t7=CsvUtil::getInstance()->getValue(line,7,path);
	Value t10=CsvUtil::getInstance()->getValue(line,10,path);
	this->id=id;
	this->kind=t1.asInt();	
	this->number=1;
	this->rarerate=t4.asInt();	
	this->effection=t5.asInt();	
	this->salegold=t6.asInt();
	this->name=t2.asString();
	this->picname=t3.asString();
	this->cd=t7.asInt();
	this->detail=t10.asString();
	this->issale=1;
	this->isusing=0;
	this->isselect=0;
	pic=MenuItemImage::create(this->picname,this->picname, CC_CALLBACK_1(Item::buttoncallback, this));
	pic->retain();
}
Item::Item(int level,int kind,int rarerate)
{
	this->level=level;
	this->kind=kind;
	this->rarerate=rarerate;
	this->number=1;
	this->salegold=100;
	this->isusing=0;
	this->issale=1;
	this->isselect=0;
	randuniqueid();
	pic=MenuItemImage::create("xx.png","xx.png", CC_CALLBACK_1(Item::buttoncallback, this));
	pic->retain();
	isopen=0;
	if(kind==1)
	{
		ping_jun_gong_ji_li=10*pow(1.15,level);
		switch(rarerate)
		{
		case 1:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.12;
			break;
		case 2:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.24;
			break;
		case 3:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.36;
			break;
		case 4:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.48;
			break;
		case 5:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.60;
			break;
		}
	}
	else if(kind==0)
	{
		ping_jun_gong_ji_li=12*pow(1.15,level);
		switch(rarerate)
		{
		case 1:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.12;
			break;
		case 2:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.24;
			break;
		case 3:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.36;
			break;
		case 4:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.48;
			break;
		case 5:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.60;
			break;
		}
	}
	shang_xian_gong_ji_li=ping_jun_gong_ji_li*1.1;
	xia_xian_gong_ji_li=ping_jun_gong_ji_li*0.9;

	gong_ji_li_jia_cheng=0;
	HP_shangxian=0;
	fang_yu_li=0;
	bao_ji_lv=0;
	bao_ji_shang_hai=0;
	dan_yao_shang_xian=0;
	nai_jiu_shang_xian=0;
	qiang_xuan_yun_gai_lv=0;
	shi_qu_xue_qiu_shang_xian=0;
	shi_qu_neng_liang_qiu_shang_xian=0;
	shi_qu_dan_yao_shang_xian=0;
	wu_qi_xiang_qian=0;

	jin_bi_huo_de_ti_gao=0;
	jin_yan_huo_de_ti_gao=0;
	xin_yun_zhi_ti_gao=0;

	ming_zhong_lv=0;
	shan_bi_lv=0;
	neng_liang_huo_de_su_du=0;
	lian_ji_shu=0;
	te_shu_ji_xiao_hao_jian_di=0;
	xi_xue_gai_lv=0;

	randomforproperty=rand()%100;
	gailva=0;
	gailvb=0;


}

Item::Item(std::string id,int nothing)
{
	const char *path="test.csv";
	CsvUtil::getInstance()->loadFile(path);
	int line=CsvUtil::getInstance()->findValueInWithLine(id.c_str(),0,path);
	
	Value t1=CsvUtil::getInstance()->getValue(line,1,path);
	Value t2=CsvUtil::getInstance()->getValue(line,2,path);
	Value t3=CsvUtil::getInstance()->getValue(line,3,path);
	Value t4=CsvUtil::getInstance()->getValue(line,4,path);
	Value t5=CsvUtil::getInstance()->getValue(line,5,path);
	Value t6=CsvUtil::getInstance()->getValue(line,6,path);
	Value t7=CsvUtil::getInstance()->getValue(line,7,path);
	Value t10=CsvUtil::getInstance()->getValue(line,10,path);
	this->id=id;
	this->kind=t1.asInt();	
	this->number=1;
	this->rarerate=t4.asInt();	
	this->effection=t5.asInt();	
	this->salegold=t6.asInt();
	this->name=t2.asString();
	this->picname=t3.asString();
	this->cd=t7.asInt();
	this->detail=t10.asString();
	this->level=1;
	this->isusing=1;
	this->issale=0;
	this->isselect=0;
	pic=MenuItemImage::create(this->picname,this->picname, CC_CALLBACK_1(Item::buttoncallback, this));
	pic->retain();
	shiyongzhong=Sprite::create("ui/isusing.png");
	shiyongzhong->setPosition(pic->getContentSize().width/2,pic->getContentSize().height/2);
	pic->addChild(shiyongzhong);
	isopen=1;
	if(kind==1)
	{
		ping_jun_gong_ji_li=10*pow(1.15,level);
		switch(rarerate)
		{
		case 1:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.12;
			break;
		case 2:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.24;
			break;
		case 3:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.36;
			break;
		case 4:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.48;
			break;
		case 5:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.60;
			break;
		}
	}
	else if(kind==0)
	{
		ping_jun_gong_ji_li=12*pow(1.15,level);
		switch(rarerate)
		{
		case 1:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.12;
			break;
		case 2:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.24;
			break;
		case 3:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.36;
			break;
		case 4:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.48;
			break;
		case 5:
			ping_jun_gong_ji_li=ping_jun_gong_ji_li*1.60;
			break;
		}
	}
	shang_xian_gong_ji_li=ping_jun_gong_ji_li*1.1;
	xia_xian_gong_ji_li=ping_jun_gong_ji_li*0.9;

	gong_ji_li_jia_cheng=0;
	HP_shangxian=0;
	fang_yu_li=0;
	bao_ji_lv=0;
	bao_ji_shang_hai=0;
	dan_yao_shang_xian=0;
	nai_jiu_shang_xian=0;
	qiang_xuan_yun_gai_lv=0;
	shi_qu_xue_qiu_shang_xian=0;
	shi_qu_neng_liang_qiu_shang_xian=0;
	shi_qu_dan_yao_shang_xian=0;
	wu_qi_xiang_qian=0;

	jin_bi_huo_de_ti_gao=0;
	jin_yan_huo_de_ti_gao=0;
	xin_yun_zhi_ti_gao=0;

	ming_zhong_lv=0;
	shan_bi_lv=0;
	neng_liang_huo_de_su_du=0;
	lian_ji_shu=0;
	te_shu_ji_xiao_hao_jian_di=0;
	xi_xue_gai_lv=0;
}

void Item::buttoncallback(Ref* pSender)
{
	if(Gamepanel::JueseSysytem==1)
	{
		for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
		{
			Item *temp=ItemData::getInstance()->Allbagitemvec.at(i);
			if(temp->isselect==1)
			{
				temp->isselect=0;
				temp->pic->removeChild(temp->zhezhao);
			}
		}
		isselect=1;
		zhezhao=Sprite::create("selected.png");
		zhezhao->setOpacity(60);
		zhezhao->setPosition(pic->getContentSize().width/2,pic->getContentSize().height/2);
		pic->addChild(zhezhao);
		Hero::getInstance()->compareEquipment(this);
	}
	else if(Gamepanel::DuanzaoSystem==1)
	{

	}
	else if(Gamepanel::BagSystem==1)
	{
		if((kind==0||kind==1)&&isopen==0&&Gamepanel::gamepanel->LayerSwitch_C==0)
		{
			randomgetitemdata(kind,rarerate);
			kaixiangzi();
		}
		else if(Gamepanel::gamepanel->LayerSwitch_C==0)
		{
			if(kind==0||kind==1)
			showdetail(0);
			else
			showdetail(1);
		}
	}
	
}

void Item::operationcallback(Ref* pSender)
{
	MenuItemImage* pImage=(MenuItemImage*)pSender;
	int flag = pImage->getTag();
	switch(flag)
	{
	case 1:

	
		break;
	case 2:
		Gamepanel::gamepanel->Layer_B->removeAllChildren();
		Gamepanel::LayerSwitch_B=0;
		Gamepanel::gamepanel->scrollView->setTouchEnabled(true);
		break;
	case 3:
		if(sellnum<number)
		{
			sellnum++;
			char a[4];
			sprintf(a,"%d",sellnum);
			sellnumlab->setString(a);
			char b[20];
			sprintf(b,"%d",sellnum*this->salegold);
			selltotalmoneylab->setString(b);
		}
		break;
	case 4:
		if(sellnum>0)
		{
			sellnum--;
			char a[4];
			sprintf(a,"%d",sellnum);
			sellnumlab->setString(a);
			char b[20];
			sprintf(b,"%d",sellnum*this->salegold);
			selltotalmoneylab->setString(b);
		}
		break;
	case 5:
		if(number>0&&sellnum<=number)
		{
			Gamepanel::Money+=sellnum*salegold;
			char a[8];
			sprintf(a,"%d",Gamepanel::Money);
			Gamepanel::gamepanel->moneylab->setString(a);
			useitem(sellnum);
		}
		break;
	case 6:
		if(number>0&&number!=NULL)
		{
			sellnum=number;
			char a[4];
			sprintf(a,"%d",sellnum);
			sellnumlab->setString(a);
			char b[20];
			sprintf(b,"%d",sellnum*this->salegold);
			selltotalmoneylab->setString(b);
		}
		break;
	case 7:
		Gamepanel::gamepanel->Layer_C->removeAllChildrenWithCleanup(true);
		Gamepanel::gamepanel->LayerSwitch_C=0;
		auto pp=Sprite::create("wuqi1.png");
		pp->setPosition(ccp(pic->getContentSize().width/2,pic->getContentSize().height/2));
		pic->addChild(pp);
		break;
	}
}

void Item::showdetail(int kind)
{
	if(kind==0)
	{
		const char *path="pn.csv";
		CsvUtil::getInstance()->loadFile(path);
		Value v1=CsvUtil::getInstance()->getValue(0,0,path);
		Gamepanel::gamepanel->Layer_A->removeChild(Gamepanel::gamepanel->Layer_B);
		Gamepanel::gamepanel->Layer_B=Node::create();
		Gamepanel::gamepanel->Layer_A->addChild(Gamepanel::gamepanel->Layer_B,2);
		Sprite *itempic1;
		if(rarerate==1)
		{
			if(this->kind==1)
				itempic1=Sprite::create("chujijian.png");
			else 
				itempic1=Sprite::create("chujiqiang.png");
		}
		else
		{
			itempic1=Sprite::create("wuqi1.png");
		}
		
		itempic1->setPosition(ccp(150*2*Gamepanel::scaleFactory,470*2*Gamepanel::scaleFactory));
		char temp[20];
		sprintf(temp,":%.2f-%.2f",xia_xian_gong_ji_li,shang_xian_gong_ji_li);
		auto lab1=Label::create(v1.asString()+temp,"",15);
        lab1->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory));
		int templine=1;
		if(gong_ji_li_jia_cheng!=0)
		{
			sprintf(temp,":+%g%%",gong_ji_li_jia_cheng*100);
			Value v1=CsvUtil::getInstance()->getValue(0,1,path);
			auto templab=Label::create(v1.asString()+temp,"",15);
			templab->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab,2);
			templine++;
		}
		if(HP_shangxian!=0)
		{
			sprintf(temp,":+%g%%",HP_shangxian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,2,path);
			auto templab1=Label::create(v1.asString()+temp,"",15);
			templab1->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab1,2);
			templine++;
		}
		if(fang_yu_li!=0)
		{
			sprintf(temp,":+%d",fang_yu_li);
			Value v1=CsvUtil::getInstance()->getValue(0,3,path);
			auto templab2=Label::create(v1.asString()+temp,"",15);
			templab2->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab2,2);
			templine++;
		}
		if(bao_ji_lv!=0)
		{
			sprintf(temp,":+ %g%%",bao_ji_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,4,path);
			auto templab3=Label::create(v1.asString()+temp,"",15);
			templab3->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab3,2);
			templine++;
		}
		if(bao_ji_shang_hai!=0)
		{
			sprintf(temp,":+%g%%",bao_ji_shang_hai*100);
			Value v1=CsvUtil::getInstance()->getValue(0,5,path);
			auto templab4=Label::create(v1.asString()+temp,"",15);
			templab4->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab4,2);
			templine++;
		}
		if(dan_yao_shang_xian!=0)
		{
			sprintf(temp,":+%d",dan_yao_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,6,path);
			auto templab5=Label::create(v1.asString()+temp,"",15);
			templab5->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab5,2);
			templine++;
		}
		if(nai_jiu_shang_xian!=0)
		{
			sprintf(temp,":+%d",nai_jiu_shang_xian);
			Value v1=CsvUtil::getInstance()->getValue(0,7,path);
			auto templab6=Label::create(v1.asString()+temp,"",15);
			templab6->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab6,2);
			templine++;
		}
		if(qiang_xuan_yun_gai_lv!=0)
		{
			sprintf(temp,":+%g%%",qiang_xuan_yun_gai_lv*100);
			Value v1=CsvUtil::getInstance()->getValue(0,8,path);
			auto templab7=Label::create(v1.asString()+temp,"",15);
			templab7->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab7,2);
			templine++;
		}
		if(shi_qu_xue_qiu_shang_xian!=0)
		{
			sprintf(temp,":+%g%%",shi_qu_xue_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,9,path);
			auto templab8=Label::create(v1.asString()+temp,"",15);
			templab8->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab8,2);
			templine++;
		}
		if(shi_qu_neng_liang_qiu_shang_xian!=0)
		{
			sprintf(temp,":+%g%%",shi_qu_neng_liang_qiu_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,10,path);
			auto templab9=Label::create(v1.asString()+temp,"",15);
			templab9->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab9,2);
			templine++;
		}
		if(shi_qu_dan_yao_shang_xian!=0)
		{
			sprintf(temp,":+%g%%",shi_qu_dan_yao_shang_xian*100);
			Value v1=CsvUtil::getInstance()->getValue(0,11,path);
			auto templab10=Label::create(v1.asString()+temp,"",15);
			templab10->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab10,2);
			templine++;
		}
		if(wu_qi_xiang_qian!=0)
		{
			sprintf(temp,":+ %d",wu_qi_xiang_qian);
			Value v1=CsvUtil::getInstance()->getValue(0,12,path);
			auto templab11=Label::create(v1.asString()+temp,"",15);
			templab11->setPosition(ccp(250*2*Gamepanel::scaleFactory,400*2*Gamepanel::scaleFactory-20*templine*2*Gamepanel::scaleFactory));
			Gamepanel::gamepanel->Layer_B->addChild(templab11,2);
			templine++;
		}
		
		Gamepanel::gamepanel->Layer_B->addChild(itempic1,1);
		Gamepanel::gamepanel->Layer_B->addChild(lab1,1);
		showsellpanel();
	}
	if(kind!=0)
	{
		Gamepanel::gamepanel->Layer_A->removeChild(Gamepanel::gamepanel->Layer_B);
		Gamepanel::gamepanel->Layer_B=Node::create();
		Gamepanel::gamepanel->Layer_A->addChild(Gamepanel::gamepanel->Layer_B,2);

		auto itempic=Sprite::create(picname);
		itempic->setPosition(Vec2(150*2*Gamepanel::scaleFactory,470*2*Gamepanel::scaleFactory));
		auto namelab=Label::create(name,"",12);
		namelab->setPosition(Vec2(315*2*Gamepanel::scaleFactory,480*2*Gamepanel::scaleFactory));
		auto itemdetail=Label::create(detail,"",15);
		itemdetail->setPosition(Vec2(260*2*Gamepanel::scaleFactory,350*2*Gamepanel::scaleFactory));
		auto menuA=Menu::create();
		menuA->setPosition(ccp(0,0));
		auto sell=MenuItemImage::create("xx.png","xx.png", CC_CALLBACK_1(Item::operationcallback, this));
		sell->setPosition(ccp(130*2*Gamepanel::scaleFactory,150*2*Gamepanel::scaleFactory));
		sell->setTag(1);
		auto showdetail=MenuItemImage::create("xx.png","xx.png", CC_CALLBACK_1(Item::operationcallback, this));
		showdetail->setPosition(ccp(260*2*Gamepanel::scaleFactory,150*2*Gamepanel::scaleFactory));
		menuA->addChild(sell);
		menuA->addChild(showdetail);

		Gamepanel::gamepanel->Layer_B->addChild(itempic,1);
		Gamepanel::gamepanel->Layer_B->addChild(namelab,1);
		Gamepanel::gamepanel->Layer_B->addChild(itemdetail,1);
		showsellpanel();
	}
	

}

void Item::addnumber()
{
	this->number++;
	shownumber(number);
}

void Item::useitem(int num)
{
	number-=num;
	shownumber(number);
	if(number>0&&number<=1)
	{
		pic->removeChild(numlab);
	}
	if(number<=0)
	{
		ItemData::getInstance()->deleteitem(id.c_str());
	}
}

void Item::randomgetitemdata(int kind,int rarerate)
{
	switch(kind)
	{
	case 0:
		setweapon_gun(rarerate);
		break;
	case 1:
		setweapon_knife(rarerate);
		break;
	case 10:
		setring(rarerate);
		break;
	case 11:
		setnecklace(rarerate);
		break;
	}
}

void Item::setweapon_knife(int rarerate)
{
	switch(rarerate)
	{
	case 1:
		randproperty_knife(1);
		break;
	case 2:
		randproperty_knife(2);
		break;
	case 3:
		randproperty_knife(3);
		break;
	case 4:
		randproperty_knife(4);
		break;
	case 5:
		randproperty_knife(5);
		break;
	}
}
void Item::setweapon_gun(int rarerate)
{
	switch(rarerate)
	{
	case 1:
		randproperty_gun(1);
		break;
	case 2:
		randproperty_gun(2);
		break;
	case 3:
		randproperty_gun(3);
		break;
	case 4:
		randproperty_gun(4);
		break;
	case 5:
		randproperty_gun(5);
		break;
	}
}
void Item::setnecklace(int rarerate)
{
	switch(rarerate)
	{
	case 1:
		
		break;
	case 2:
		randproperty_necklace(1);
		break;
	case 3:
		randproperty_necklace(2);
		break;
	case 4:
		randproperty_necklace(2);
		break;
	case 5:
		randproperty_necklace(3);
		break;
	}
}
void Item::setring(int rarerate)
{
	switch(rarerate)
	{
	case 1:
		break;
	case 2:
		randproperty_ring(1);
		break;
	case 3:
		randproperty_ring(2);
		break;
	case 4:
		randproperty_ring(2);
		break;
	case 5:
		randproperty_ring(3);
		break;
	}
}

void Item::randproperty_knife(int num)
{
	if(num>0)
	{
		if(randomforproperty>=0&&randomforproperty<9&&gong_ji_li_jia_cheng==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%6;
				gailvb=rand()%11;
			}
			gong_ji_li_jia_cheng=(float)(rarerate<=2?gailva+5:gailvb+10)/100;
			num--;
		}
		else if(randomforproperty>=9&&randomforproperty<18&&HP_shangxian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%11;
				gailvb=rand()%15;
			}
			HP_shangxian=(float)(rarerate<=2?gailva+5:gailvb+16)/100;
			num--;
		}
		else if(randomforproperty>=18&&randomforproperty<27&&fang_yu_li==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%6;
				gailvb=rand()%10;
			}
			fang_yu_li=rarerate<=2?gailva+5:gailvb+11;
			num--;
		}
		else if(randomforproperty>=27&&randomforproperty<36&&bao_ji_lv==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%5;
				gailvb=rand()%5;
			}
			bao_ji_lv=(float)(rarerate<=2?gailva+1:gailvb+6)/100;
			num--;
		}
		else if(randomforproperty>=36&&randomforproperty<45&&bao_ji_shang_hai==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%46;
				gailvb=rand()%46;
			}
			bao_ji_shang_hai=(float)(rarerate<=2?gailva+5:gailvb+55)/100;
			num--;
		}
		else if(randomforproperty>=45&&randomforproperty<54&&nai_jiu_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%31;
				gailvb=rand()%50;
			}
			nai_jiu_shang_xian=rarerate<=2?gailva+20:gailvb+51;
			num--;
		}
		else if(randomforproperty>=63&&randomforproperty<72&&shi_qu_xue_qiu_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%41;
				gailvb=rand()%50;
			}
			shi_qu_xue_qiu_shang_xian=(float)(rarerate<=2?gailva+10:gailvb+51)/100;
			num--;
		}
		else if(randomforproperty>=72&&randomforproperty<81&&shi_qu_neng_liang_qiu_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%41;
				gailvb=rand()%50;
			}
			shi_qu_neng_liang_qiu_shang_xian=(float)(rarerate<=2?gailva+10:gailvb+51)/100;
			num--;
		}
		else if(randomforproperty>=81&&randomforproperty<90&&shi_qu_dan_yao_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%41;
				gailvb=rand()%50;
			}
			shi_qu_dan_yao_shang_xian=(float)(rarerate<=2?gailva+10:gailvb+51)/100;
			num--;
		}
		else if(randomforproperty>=90&&randomforproperty<=99&&wu_qi_xiang_qian==0)
		{
			wu_qi_xiang_qian=1;
			num--;
		}
		randomforproperty=rand()%100;
	}
	if(num>0)
		randproperty_knife(num);
}

void Item::randproperty_gun(int num)
{
	if(num>0)
	{
		if(randomforproperty>=0&&randomforproperty<9&&gong_ji_li_jia_cheng==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%6;
				gailvb=rand()%11;
			}
			gong_ji_li_jia_cheng=(float)(rarerate<=2?gailva+5:gailvb+10)/100;
			num--;
		}
		else if(randomforproperty>=9&&randomforproperty<18&&HP_shangxian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%11;
				gailvb=rand()%15;
			}
			HP_shangxian=(float)(rarerate<=2?gailva+5:gailvb+16)/100;
			num--;
		}
		else if(randomforproperty>=18&&randomforproperty<27&&fang_yu_li==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%6;
				gailvb=rand()%10;
			}
			fang_yu_li=rarerate<=2?gailva+5:gailvb+11;
			num--;
		}
		else if(randomforproperty>=27&&randomforproperty<36&&bao_ji_lv==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%5;
				gailvb=rand()%5;
			}
			bao_ji_lv=(float)(rarerate<=2?gailva+1:gailvb+6)/100;
			num--;
		}
		else if(randomforproperty>=36&&randomforproperty<45&&bao_ji_shang_hai==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%46;
				gailvb=rand()%46;
			}
			bao_ji_shang_hai=(float)(rarerate<=2?gailva+5:gailvb+55)/100;
			num--;
		}
		else if(randomforproperty>=45&&randomforproperty<54&&dan_yao_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%31;
				gailvb=rand()%50;
			}
			dan_yao_shang_xian=rarerate<=2?gailva+20:gailvb+51;
			num--;
		}
		else if(randomforproperty>=54&&randomforproperty<63&&qiang_xuan_yun_gai_lv==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%3;
				gailvb=rand()%3;
			}
			qiang_xuan_yun_gai_lv=(float)(rarerate<=2?gailva+1:gailvb+4)/100;
			num--;
		}
		else if(randomforproperty>=63&&randomforproperty<72&&shi_qu_xue_qiu_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%41;
				gailvb=rand()%50;
			}
			shi_qu_xue_qiu_shang_xian=(float)(rarerate<=2?gailva+10:gailvb+51)/100;
			num--;
		}
		else if(randomforproperty>=72&&randomforproperty<81&&shi_qu_neng_liang_qiu_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%41;
				gailvb=rand()%50;
			}
			shi_qu_neng_liang_qiu_shang_xian=(float)(rarerate<=2?gailva+10:gailvb+51)/100;
			num--;
		}
		else if(randomforproperty>=81&&randomforproperty<90&&shi_qu_dan_yao_shang_xian==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%41;
				gailvb=rand()%50;
			}
			shi_qu_dan_yao_shang_xian=(float)(rarerate<=2?gailva+10:gailvb+51)/100;
			num--;
		}
		else if(randomforproperty>=90&&randomforproperty<=99&&wu_qi_xiang_qian==0)
		{
			wu_qi_xiang_qian=1;
			num--;
		}
		randomforproperty=rand()%100;
	}
	if(num>0)
		randproperty_gun(num);
}

void Item::randproperty_necklace(int num)
{
	if(num>0)
	{
		if(randomforproperty>=0&&randomforproperty<16&&ming_zhong_lv==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%5;
				gailvb=rand()%5;
			}
			ming_zhong_lv=(float)(rarerate<=2?gailva+1:gailvb+6)/100;
			num--;
		}
		else if(randomforproperty>=16&&randomforproperty<32&&shan_bi_lv==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%6;
				gailvb=rand()%5;
			}
			shan_bi_lv=(float)(rarerate<=2?gailva+5:gailvb+11)/100;
			num--;
		}
		else if(randomforproperty>=32&&randomforproperty<48&&neng_liang_huo_de_su_du==0)
		{
			neng_liang_huo_de_su_du=rarerate<=2?1:2;
			num--;
		}
		else if(randomforproperty>=48&&randomforproperty<64&&lian_ji_shu==0)
		{
			lian_ji_shu=rarerate<=2?1:2;
			num--;
		}
		else if(randomforproperty>=64&&randomforproperty<80&&te_shu_ji_xiao_hao_jian_di==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%3;
				gailvb=rand()%3;
			}
			te_shu_ji_xiao_hao_jian_di=rarerate<=2?gailva+1:gailvb+4;
			num--;
		}
		else if(randomforproperty>=80&&randomforproperty<99&&xi_xue_gai_lv==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%11;
				gailvb=rand()%21;
			}
			xi_xue_gai_lv=(float)(rarerate<=2?gailva+5:gailvb+10)/100;
			num--;
		}
		randomforproperty=rand()%100;
	}
	if(num>0)
		randproperty_necklace(num);
}

void Item::randproperty_ring(int num)
{
	if(num>0)
	{
		if(randomforproperty>=0&&randomforproperty<33&&jin_bi_huo_de_ti_gao==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%41;
				gailvb=rand()%50;
			}
			jin_bi_huo_de_ti_gao=(float)(rarerate<=2?gailva+10:gailvb+51)/100;
			num--;
		}
		else if(randomforproperty>=33&&randomforproperty<66&&jin_yan_huo_de_ti_gao==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%21;
				gailvb=rand()%25;
			}
			jin_yan_huo_de_ti_gao=(float)(rarerate<=2?gailva+5:gailvb+26)/100;
			num--;
		}
		else if(randomforproperty>=33&&randomforproperty<66&&xin_yun_zhi_ti_gao==0)
		{
			for(int i=0;i<randomforproperty;i++)
			{
				gailva=rand()%10;
				gailvb=rand()%10;
			}
			xin_yun_zhi_ti_gao=rarerate<=2?gailva+1:gailvb+11;
			num--;
		}
		randomforproperty=rand()%100;
	}
	if(num>0)
		randproperty_necklace(num);
}

void Item::shownumber(int num)
{
	if(number>1)
	{
		pic->removeChild(numlab);
		numlab=Label::createWithCharMap("num.png",30,30,'0');
		char cc[4];
		sprintf(cc,"%d",num);
		numlab->setString(cc);
		pic->addChild(numlab);
	}
}

void Item::showsellpanel()
{
		sellnum=1;
		auto menuB=Menu::create();
		menuB->setPosition(ccp(0,0));
		auto zengjia=MenuItemImage::create("","", CC_CALLBACK_1(Item::operationcallback, this));
		zengjia->setNormalImage(Sprite::createWithSpriteFrameName("beibaojia.png"));
		zengjia->setSelectedImage(Sprite::createWithSpriteFrameName("beibaojia.png"));
		zengjia->setTag(3);
		zengjia->setScale(Gamepanel::scaleFactory);
		zengjia->setPosition(ccp(210*2*Gamepanel::scaleFactory,250*2*Gamepanel::scaleFactory));

		auto jianshao=MenuItemImage::create("","", CC_CALLBACK_1(Item::operationcallback, this));
		jianshao->setNormalImage(Sprite::createWithSpriteFrameName("beibaojian.png"));
		jianshao->setSelectedImage(Sprite::createWithSpriteFrameName("beibaojian.png"));
		jianshao->setTag(4);
		jianshao->setScale(Gamepanel::scaleFactory);
		jianshao->setPosition(ccp(100*2*Gamepanel::scaleFactory,250*2*Gamepanel::scaleFactory));
		menuB->addChild(zengjia);
		menuB->addChild(jianshao);

		sellit=MenuItemImage::create("","", CC_CALLBACK_1(Item::operationcallback, this));
		sellit->setNormalImage(Sprite::createWithSpriteFrameName("chushou1.png"));
		sellit->setSelectedImage(Sprite::createWithSpriteFrameName("chushou2.png"));
		sellit->setDisabledImage(Sprite::createWithSpriteFrameName("bukechushou.png"));
		sellit->setPosition(ccp(230*2*Gamepanel::scaleFactory,120*2*Gamepanel::scaleFactory));
		sellit->setTag(5);
		sellit->setScale(Gamepanel::scaleFactory);
		menuB->addChild(sellit);

		auto sellall=MenuItemImage::create("","", CC_CALLBACK_1(Item::operationcallback, this));
		sellall->setNormalImage(Sprite::createWithSpriteFrameName("quanbuanniu1.png"));
		sellall->setSelectedImage(Sprite::createWithSpriteFrameName("quanbuanniu2.png"));
		sellall->setPosition(ccp(330*2*Gamepanel::scaleFactory,250*2*Gamepanel::scaleFactory));
		sellall->setTag(6);
		sellall->setScale(Gamepanel::scaleFactory);
		menuB->addChild(sellall);

		sellnumlab=Label::createWithCharMap("num.png",30,30,'0');
		sellnumlab->setString("1");
		sellnumlab->setScale(Gamepanel::scaleFactory);
		sellnumlab->setPosition(ccp(150*2*Gamepanel::scaleFactory,250*2*Gamepanel::scaleFactory));

		selltotalmoneylab=Label::createWithCharMap("num.png",30,30,'0');
		char tempmoney[10];
		sprintf(tempmoney,"%d",this->salegold);
		selltotalmoneylab->setString(tempmoney);
		selltotalmoneylab->setScale(Gamepanel::scaleFactory);
		selltotalmoneylab->setPosition(ccp(230*2*Gamepanel::scaleFactory,190*2*Gamepanel::scaleFactory));

		if(issale==0||isusing==1)
			sellit->setEnabled(false);
		Gamepanel::gamepanel->Layer_B->addChild(menuB);
		Gamepanel::gamepanel->Layer_B->addChild(sellnumlab);
		Gamepanel::gamepanel->Layer_B->addChild(selltotalmoneylab);
}

void Item::kaixiangzi()
{
	isopen=1;
	Gamepanel::gamepanel->LayerSwitch_C=1;
	Gamepanel::gamepanel->Layer_A->removeChild(Gamepanel::gamepanel->Layer_C);
	Gamepanel::gamepanel->Layer_C=Node::create();
	Gamepanel::gamepanel->Layer_A->addChild(Gamepanel::gamepanel->Layer_C,3);
	auto mask=Sprite::create("mask.png");
	mask->setScale(100);
	auto kaijiangtiao=Sprite::create("tiao.png");
	kaijiangtiao->setPosition(ccp(Director::getInstance()->getVisibleSize().width/2-250, Director::getInstance()->getVisibleSize().height/2));
	kaijiangtiao->setAnchorPoint(ccp(0,0));
	kaijiangtiao->setScaleX(0);
	FiniteTimeAction* action = Sequence::create(ScaleTo::create(3.0f,1.0f,1.0f),CCCallFuncND::create(this, callfuncND_selector(Item::xianshijp), (void*)true), NULL);
	kaijiangtiao->runAction(action);

	Gamepanel::gamepanel->Layer_C->addChild(mask,1);
	Gamepanel::gamepanel->Layer_C->addChild(kaijiangtiao,1);
}

void Item::xianshijp(CCNode* pSender, void* data)
{
	Gamepanel::gamepanel->Layer_C->removeAllChildrenWithCleanup(true);
	auto mask=Sprite::create("mask.png");
	mask->setScale(100);

	auto wuqi=Sprite::create("wuqi1.png");
	wuqi->setScale(5);
	wuqi->setPosition(ccp(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2));
	ScaleTo *s1=ScaleTo::create(1.0,4.0,4.0);
	ScaleTo *s2=ScaleTo::create(1.0,5.0,5.0);
	Sequence *seq=Sequence::create(s1,s2,s1,s2,s1,s2,NULL);
	wuqi->runAction(seq);

	auto guanbi=MenuItemImage::create("xx.png","xx.png", CC_CALLBACK_1(Item::operationcallback, this));
	guanbi->setTag(7);
	guanbi->setPosition(ccp(Director::getInstance()->getVisibleSize().width/2-300, Director::getInstance()->getVisibleSize().height/2));
	auto menu=Menu::create(guanbi,NULL);
	menu->setPosition(ccp(0,0));
	Gamepanel::gamepanel->Layer_C->addChild(mask,1);
	Gamepanel::gamepanel->Layer_C->addChild(wuqi,1);
	Gamepanel::gamepanel->Layer_C->addChild(menu,1);
}

void Item::randuniqueid()
{
	int randid=rand()%1000;
	char tempid[10];
	sprintf(tempid,"%d",randid);
	id=tempid;
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{
		if(ItemData::getInstance()->Allbagitemvec.at(i)->id==id)
			randuniqueid();
		else 
			return;
		break;
	}

}

void Item::releaseself()
{
	pic->removeFromParent();
	pic->release();
}