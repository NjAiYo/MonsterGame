//
//  BagLayer.cpp
//  MonsterGame
//
//  Created by 南京艾游网络文化有限公司 on 15/5/29.
//
//

#include "BagLayer.h"
#include "AppDelegate.h"
#include "ItemData.h"
#include "Item.h"
#include "Gamepanel.h"
#include "CsvUtil.h"
BagLayer::BagLayer()
:itemIconSprite(nullptr)
{
    
}

bool BagLayer::initWithGamePanel(Gamepanel *gs)
{
    if (!Node::init()) {
        return false;
    }
    numForSale = 0;
    totalSalePrice = 0;
    selectedItem = nullptr;
    gamepanel = gs;
    bagLayerSwitch_A=0;
    hero = GameManager::getInstance()->getPlayer();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    scaleFactory = app->scaleFactory;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto mask=Sprite::create("mask.png");
    mask->setScale(100);
    addChild(mask);
    
    auto bagbg=Sprite::create("beibaobeijing.png");
    bagbg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(bagbg);
    
    bagquanbu=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    bagquanbu->setNormalImage(Sprite::createWithSpriteFrameName("bagquanbu.png"));
    bagquanbu->setSelectedImage(Sprite::createWithSpriteFrameName("bagquanbu.png"));
    bagquanbu->setDisabledImage(Sprite::createWithSpriteFrameName("bagquanbu1.png"));
    bagquanbu->setTag(SHOWALL);
    bagquanbu->setPosition(Vec2(2060*scaleFactory,900*scaleFactory));
    bagquanbu->setEnabled(false);
    
    bagzhuangbei=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    bagzhuangbei->setNormalImage(Sprite::createWithSpriteFrameName("bagzhuangbei.png"));
    bagzhuangbei->setSelectedImage(Sprite::createWithSpriteFrameName("bagzhuangbei.png"));
    bagzhuangbei->setDisabledImage(Sprite::createWithSpriteFrameName("bagzhuangbei1.png"));
    bagzhuangbei->setTag(SHOWZHUANGBEI);
    bagzhuangbei->setPosition(Vec2(2060*scaleFactory,700*scaleFactory));
    
    bagcailiao=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    bagcailiao->setNormalImage(Sprite::createWithSpriteFrameName("bagcaoliao.png"));
    bagcailiao->setSelectedImage(Sprite::createWithSpriteFrameName("bagcaoliao.png"));
    bagcailiao->setDisabledImage(Sprite::createWithSpriteFrameName("bagcailiao1.png"));
    bagcailiao->setTag(SHOWCAILIAO);
    bagcailiao->setPosition(Vec2(2060*scaleFactory,500*scaleFactory));
    
    bagdaoju=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    bagdaoju->setNormalImage(Sprite::createWithSpriteFrameName("bagdaoju.png"));
    bagdaoju->setSelectedImage(Sprite::createWithSpriteFrameName("bagdaoju.png"));
    bagdaoju->setDisabledImage(Sprite::createWithSpriteFrameName("bagdaoju1.png"));
    bagdaoju->setTag(SHOWDAOJU);
    bagdaoju->setPosition(Vec2(2060*scaleFactory,300*scaleFactory));
    
    auto menubagmiddle=Menu::create(bagquanbu,bagzhuangbei,bagcailiao,bagdaoju,NULL);
    menubagmiddle->setPosition(Vec2::ZERO);
    addChild(menubagmiddle);
    
    
    
    auto bagmiddle=Sprite::create("bagmiddle.png");
    bagmiddle->setPosition(Vec2(visibleSize.width/2-60*scaleFactory,visibleSize.height/2));
    addChild(bagmiddle);
    

    auto bagtitle=Sprite::createWithSpriteFrameName("biaotibeijing.png");
    bagtitle->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+550*scaleFactory));
    auto bagtiletext=Sprite::createWithSpriteFrameName("chucangxiangbiaoti.png");
    bagtiletext->setPosition(Vec2(bagtitle->getContentSize().width/2,bagtitle->getContentSize().height/2));
    bagtitle->addChild(bagtiletext);
    addChild(bagtitle);
    
    auto di=Sprite::createWithSpriteFrameName("shuziditu.png");
    di->setPosition(Vec2(300*scaleFactory,500*scaleFactory));
    addChild(di);
    
    auto di1=Sprite::createWithSpriteFrameName("beibaojinbiditu.png");
    di1->setPosition(Vec2(460*scaleFactory,380*scaleFactory));
    auto di1jinbi=Sprite::createWithSpriteFrameName("beibaojinbi.png");
    di1jinbi->setPosition(Vec2(di1->getContentSize().width/2+230*scaleFactory,di1->getContentSize().height/2));
    di1->addChild(di1jinbi);
    addChild(di1);
    
    auto di2=Sprite::createWithSpriteFrameName("wupinminchenkuang.png");
    di2->setPosition(Vec2(285*2*scaleFactory,470*2*scaleFactory));
    addChild(di2);
    
    auto di3=Sprite::createWithSpriteFrameName("wupinmiaoshukuang.png");
    di3->setPosition(Vec2(230*2*scaleFactory,350*2*scaleFactory));
    addChild(di3);
    
    auto di4=Sprite::createWithSpriteFrameName("wupinkuang.png");
    di4->setPosition(Vec2(135*2*scaleFactory,470*2*scaleFactory));
    addChild(di4);
    
    
    
    auto bagclose=MenuItemSprite::create(Sprite::createWithSpriteFrameName("guanbi.png"), Sprite::createWithSpriteFrameName("guanbi.png"), CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    bagclose->setNormalImage(Sprite::createWithSpriteFrameName("guanbi.png"));
    bagclose->setSelectedImage(Sprite::createWithSpriteFrameName("guanbi.png"));
    bagclose->setPosition(Vec2(1020*2*scaleFactory,550*2*scaleFactory));
    bagclose->setTag(BAGCLOSEBTN);
    
    auto bagjian=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    bagjian->setNormalImage(Sprite::createWithSpriteFrameName("beibaojian.png"));
    bagjian->setSelectedImage(Sprite::createWithSpriteFrameName("beibaojian.png"));
    bagjian->setPosition(Vec2(100*2*scaleFactory,250*2*scaleFactory));
    bagjian->setTag(BAGJIAN);
    
    auto bagjia=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    bagjia->setNormalImage(Sprite::createWithSpriteFrameName("beibaojia.png"));
    bagjia->setSelectedImage(Sprite::createWithSpriteFrameName("beibaojia.png"));
    bagjia->setPosition(Vec2(210*2*scaleFactory,250*2*scaleFactory));
    bagjia->setTag(BAGJIA);
    
    auto sellall=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    sellall->setNormalImage(Sprite::createWithSpriteFrameName("quanbuanniu1.png"));
    sellall->setSelectedImage(Sprite::createWithSpriteFrameName("quanbuanniu2.png"));
    sellall->setPosition(Vec2(330*2*scaleFactory,250*2*scaleFactory));
    sellall->setTag(BAGALL);
    
    sellButton=MenuItemImage::create("","",CC_CALLBACK_1(BagLayer::allbuttoncallback,this));
    sellButton->setNormalImage(Sprite::createWithSpriteFrameName("chushou1.png"));
    sellButton->setSelectedImage(Sprite::createWithSpriteFrameName("chushou1.png"));
    sellButton->setDisabledImage(Sprite::createWithSpriteFrameName("bukechushou.png"));
    sellButton->setPosition(Vec2(230*2*scaleFactory,120*2*scaleFactory));
    sellButton->setTag(BAGSELL);
    
    auto menubag=Menu::create(bagclose,bagjian,bagjia,sellall,sellButton,NULL);
    menubag->setPosition(Vec2::ZERO);
    addChild(menubag);
    
    glowSprite = Sprite::createWithSpriteFrameName("jinengguang.png");
    glowSprite->setScale(1.2);

    ScrollView *scrollView = ScrollView::create();
    Layer *continerLayer = Layer::create();
    continerLayer->setAnchorPoint(Vec2(0,0));
    continerLayer->setPosition(Vec2(0,0));
    scrollView->setPosition(ccp(804*scaleFactory,188*scaleFactory));
    
    scrollView->setViewSize(Size(1104*scaleFactory, 887*scaleFactory));
    bagline=16;
    //if(ItemData::getInstance()->Allbagitemvec.size()<=20)
    //{
    //	continerLayer->setContentSize(Size(1094*scaleFactory, 887*scaleFactory));
    //}
    //else
    //{
    //bagline=(ItemData::getInstance()->Allbagitemvec.size()-20)%5==0? (ItemData::getInstance()->Allbagitemvec.size()-20)/5:(ItemData::getInstance()->Allbagitemvec.size()-20)/5+1;
    continerLayer->setContentSize(Size(1094*scaleFactory,887*scaleFactory+220*bagline*scaleFactory));
    continerLayer->setPosition(Vec2(0,-220*bagline*scaleFactory));
    //}
    scrollView->setContentSize(continerLayer->getContentSize());
    scrollView->setContainer(continerLayer);
    
    scrollView->setTouchEnabled(true);
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setBounceable(true);
    scrollView->setDelegate(this);
    addChild(scrollView);
    
    menuitem=Mymenu::create();
    menuitem->setAnchorPoint(Vec2::ZERO);
    menuitem->setPosition(Vec2::ZERO);
    continerLayer->addChild(menuitem,4);
    continerLayer->addChild(glowSprite);
    
    
    
    itemNameLabel = Label::createWithSystemFont("名称", "Arial Rounded MT Bold", 52);
    itemNameLabel->setColor(Color3B(255, 255, 255));
    itemNameLabel->setPosition(Vec2(550*scaleFactory ,1000*scaleFactory));
    itemNameLabel->setScale(scaleFactory);
    addChild(itemNameLabel);
    
    
    Label *numlabel = Label::createWithSystemFont("拥有数量:", "Arial Rounded MT Bold", 40);
    numlabel->setColor(Color3B(242, 221, 138));
    numlabel->setPosition(Vec2(500*scaleFactory ,940*scaleFactory));
    numlabel->setScale(scaleFactory);
    addChild(numlabel);
    
    Label *pricelabel = Label::createWithSystemFont("出售单价:", "Arial Rounded MT Bold", 40);
    pricelabel->setColor(Color3B(242, 221, 138));
    pricelabel->setPosition(Vec2(500*scaleFactory ,870*scaleFactory));
    pricelabel->setScale(scaleFactory);
    addChild(pricelabel);
    
    itemNumLabel = Label::createWithSystemFont("1", "Arial Rounded MT Bold", 40);
    itemNumLabel->setColor(Color3B(242, 221, 138));
    itemNumLabel->setAnchorPoint(Vec2(1,0.5));
    itemNumLabel->setAlignment(TextHAlignment::RIGHT);
    itemNumLabel->setPosition(Vec2(680*scaleFactory ,numlabel->getPositionY()));
    itemNumLabel->setScale(scaleFactory);
    addChild(itemNumLabel);
    
    itemPriceLabel = Label::createWithSystemFont("10", "Arial Rounded MT Bold", 40);
    itemPriceLabel->setColor(Color3B(242, 221, 138));
    itemPriceLabel->setAnchorPoint(Vec2(1,0.5));
    itemPriceLabel->setAlignment(TextHAlignment::RIGHT);
    itemPriceLabel->setPosition(Vec2(680*scaleFactory ,pricelabel->getPositionY()));
    itemPriceLabel->setScale(scaleFactory);
    addChild(itemPriceLabel);
    
    Sprite *s = Sprite::createWithSpriteFrameName("xiaojinbi.png");
    addChild(s);
    s->setPosition(715*scaleFactory, itemPriceLabel->getPositionY());
    
    itemDescriptionLabel = Label::createWithSystemFont(" IOS系统默认字体包,字体是图形用户界面显示文本的基础,对于开发者而言,快速的找到合适的字体库是提高工作效率的利器 IOS系统默认字体包,字体是图形用户界面显示文本的基础,对于开发者而言,快速的找到合适的字体库是提高工作效率的利器", "Arial Rounded MT Bold", 42,Size(490*scaleFactory,154*scaleFactory));
    itemDescriptionLabel->setColor(Color3B(242, 221, 138));
    itemDescriptionLabel->setPosition(Vec2(460*scaleFactory ,700*scaleFactory));
    itemDescriptionLabel->setScale(scaleFactory);
    addChild(itemDescriptionLabel);
    
    
    itemNumForSaleLabel = Label::createWithSystemFont("1", "Arial Rounded MT Bold", 52);
    itemNumForSaleLabel->setColor(Color3B(255, 255, 255));
    itemNumForSaleLabel->setPosition(Vec2(310*scaleFactory,500*scaleFactory));
    itemNumForSaleLabel->setScale(scaleFactory);
    addChild(itemNumForSaleLabel);
    
    
    totalSalePriceLabel = Label::createWithSystemFont("0", "Arial Rounded MT Bold", 52);
    totalSalePriceLabel->setAlignment(TextHAlignment::CENTER);
    totalSalePriceLabel->setColor(Color3B(255, 255, 255));
    totalSalePriceLabel->setPosition(Vec2(470*scaleFactory,380*scaleFactory));
    totalSalePriceLabel->setScale(scaleFactory);
    addChild(totalSalePriceLabel);
    
    

    
    for(int i=0;i<100;i++)
    {
        int x=i%5*110+60;
        int y=380-i/5*110;
        auto kuangzi=Sprite::createWithSpriteFrameName("wupinkuang.png");
        kuangzi->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
        continerLayer->addChild(kuangzi,1);
        if(i+1>hero->capacitance)
        {
            
            Lock *lk=ItemData::getInstance()->baglockvec.at(i-hero->capacitance);
            lk->lockpic->setPosition(ccp(x*2*Gamepanel::scaleFactory,y*2*Gamepanel::scaleFactory+16*220*Gamepanel::scaleFactory));
            menuitem->addChild(lk->lockpic);
        }
        
    }
    
    for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
    {
        int x=i%5*110+60;
        int y=380-i/5*110;
        Item *tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
        tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
        menuitem->addChild(tempbgt->pic);
        //log(tempbgt->id.c_str());
        if (i == 0) {
            showItemDetail(tempbgt);
        }
    }
    _eventDispatcher->addCustomEventListener("itemClicked", CC_CALLBACK_1(BagLayer::itemClickedHandler,this));
    _eventDispatcher->addCustomEventListener("openCase", CC_CALLBACK_1(BagLayer::openCaseHandler,this));
    _eventDispatcher->addCustomEventListener("itemAdded", CC_CALLBACK_1(BagLayer::updateItemsHandler,this));
    _eventDispatcher->addCustomEventListener("itemDeleted", CC_CALLBACK_1(BagLayer::updateItemsHandler,this));
    
    return true;
}

void BagLayer::updateItemsHandler(EventCustom* event)
{
    menuitem->removeAllChildren();
    for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
    {
        int x=i%5*110+60;
        int y=380-i/5*110;
        Item *tempbgt=ItemData::getInstance()->Allbagitemvec.at(i);
        tempbgt->pic->setPosition(ccp(x*2*scaleFactory,y*2*scaleFactory+bagline*220*scaleFactory));
        menuitem->addChild(tempbgt->pic);
        //log(tempbgt->id.c_str());
        if (i == 0) {
            showItemDetail(tempbgt);
        }
    }
}

void BagLayer::openCaseHandler(EventCustom* event)
{
    Item *item = (Item*)event->getUserData();
    kaixiangzi(item);
}

void BagLayer::itemClickedHandler(EventCustom* event)
{
    Item *item = (Item*)event->getUserData();
    showItemDetail(item);
}

//显示物品信息
void BagLayer::showItemDetail(Item* item)
{
    selectedItem = item;
    glowSprite->setPosition(item->pic->getPosition());
    if (itemIconSprite) {
        itemIconSprite->removeFromParent();
        itemIconSprite = nullptr;
    }
    if (item->isusing || !item->issale) {
        sellButton->setEnabled(false);
    }else{
        sellButton->setEnabled(true);
    }
    if (item->kind < 5) {
        itemIconSprite = Sprite::createWithSpriteFrameName(String::createWithFormat("k%d_l%d_r%d.png",item->kind,item->level,item->rarerate)->getCString());
    }else{
        itemIconSprite = Sprite::createWithSpriteFrameName(item->picname);
    }
    
    addChild(itemIconSprite);
    itemIconSprite->setPosition(Vec2(136*2*scaleFactory,470*2*scaleFactory));
    //现实名称
    itemNameLabel->setString(item->name);
    //显示数量,jiage
    itemNumLabel->setString(String::createWithFormat("%d",item->number)->getCString());
    itemPriceLabel->setString(String::createWithFormat("%d",item->salegold)->getCString());
    //描述
    if(item->kind>5)
    {
        itemDescriptionLabel->setString(item->detail);
        this->removeChild(bagLayer_B);
    }
    else if(item->isopen)
    {
        itemDescriptionLabel->setString("");
        const char *path="pn.csv";
        CsvUtil::getInstance()->loadFile(path);
        Value v1=CsvUtil::getInstance()->getValue(0,0,path);
        this->removeChild(bagLayer_B);
        bagLayer_B=Node::create();
        this->addChild(bagLayer_B,2);
        char temp[20];
        sprintf(temp,":%.2f-%.2f",item->xia_xian_gong_ji_li,item->shang_xian_gong_ji_li);
        auto lab1=Label::create(v1.asString()+temp,"",15);
        lab1->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory));
        int templine=1;
        if(item->gong_ji_li_jia_cheng!=0)
        {
            sprintf(temp,":+%g%%",item->gong_ji_li_jia_cheng*100);
            Value v1=CsvUtil::getInstance()->getValue(0,1,path);
            auto templab=Label::create(v1.asString()+temp,"",15);
            templab->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab,2);
            templine++;
        }
        if(item->HP_shangxian!=0)
        {
            sprintf(temp,":+%g%%",item->HP_shangxian*100);
            Value v1=CsvUtil::getInstance()->getValue(0,2,path);
            auto templab1=Label::create(v1.asString()+temp,"",15);
            templab1->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab1,2);
            templine++;
        }
        if(item->fang_yu_li!=0)
        {
            sprintf(temp,":+%d",item->fang_yu_li);
            Value v1=CsvUtil::getInstance()->getValue(0,3,path);
            auto templab2=Label::create(v1.asString()+temp,"",15);
            templab2->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab2,2);
            templine++;
        }
        if(item->bao_ji_lv!=0)
        {
            sprintf(temp,":+ %g%%",item->bao_ji_lv*100);
            Value v1=CsvUtil::getInstance()->getValue(0,4,path);
            auto templab3=Label::create(v1.asString()+temp,"",15);
            templab3->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab3,2);
            templine++;
        }
        if(item->bao_ji_shang_hai!=0)
        {
            sprintf(temp,":+%g%%",item->bao_ji_shang_hai*100);
            Value v1=CsvUtil::getInstance()->getValue(0,5,path);
            auto templab4=Label::create(v1.asString()+temp,"",15);
            templab4->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab4,2);
            templine++;
        }
        if(item->dan_yao_shang_xian!=0)
        {
            sprintf(temp,":+%d",item->dan_yao_shang_xian);
            Value v1=CsvUtil::getInstance()->getValue(0,6,path);
            auto templab5=Label::create(v1.asString()+temp,"",15);
            templab5->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab5,2);
            templine++;
        }
        if(item->nai_jiu_shang_xian!=0)
        {
            sprintf(temp,":+%d",item->nai_jiu_shang_xian);
            Value v1=CsvUtil::getInstance()->getValue(0,7,path);
            auto templab6=Label::create(v1.asString()+temp,"",15);
            templab6->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab6,2);
            templine++;
        }
        if(item->qiang_xuan_yun_gai_lv!=0)
        {
            sprintf(temp,":+%g%%",item->qiang_xuan_yun_gai_lv*100);
            Value v1=CsvUtil::getInstance()->getValue(0,8,path);
            auto templab7=Label::create(v1.asString()+temp,"",15);
            templab7->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab7,2);
            templine++;
        }
        if(item->shi_qu_xue_qiu_shang_xian!=0)
        {
            sprintf(temp,":+%g%%",item->shi_qu_xue_qiu_shang_xian*100);
            Value v1=CsvUtil::getInstance()->getValue(0,9,path);
            auto templab8=Label::create(v1.asString()+temp,"",15);
            templab8->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab8,2);
            templine++;
        }
        if(item->shi_qu_neng_liang_qiu_shang_xian!=0)
        {
            sprintf(temp,":+%g%%",item->shi_qu_neng_liang_qiu_shang_xian*100);
            Value v1=CsvUtil::getInstance()->getValue(0,10,path);
            auto templab9=Label::create(v1.asString()+temp,"",15);
            templab9->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab9,2);
            templine++;
        }
        if(item->shi_qu_dan_yao_shang_xian!=0)
        {
            sprintf(temp,":+%g%%",item->shi_qu_dan_yao_shang_xian*100);
            Value v1=CsvUtil::getInstance()->getValue(0,11,path);
            auto templab10=Label::create(v1.asString()+temp,"",15);
            templab10->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab10,2);
            templine++;
        }
        if(item->wu_qi_xiang_qian!=0)
        {
            sprintf(temp,":+ %d",item->wu_qi_xiang_qian);
            Value v1=CsvUtil::getInstance()->getValue(0,12,path);
            auto templab11=Label::create(v1.asString()+temp,"",15);
            templab11->setPosition(ccp(250*2*scaleFactory,400*2*scaleFactory-20*templine*2*scaleFactory));
            bagLayer_B->addChild(templab11,2);
            templine++;
        }
        bagLayer_B->addChild(lab1);
    }
    numForSale = 1;
    totalSalePrice = numForSale * item->salegold;
    itemNumForSaleLabel->setString(String::createWithFormat("%d",numForSale)->getCString());
    totalSalePriceLabel->setString(String::createWithFormat("%d",totalSalePrice)->getCString());
    
}

void BagLayer::kaixiangzi(Item *item)
{
    if(bagLayerSwitch_A==1)
        return;
    selectedItem=item;
    item->isopen=1;
    item->randomgetitemdata(item->kind, item->rarerate);
    bagLayer_A=Node::create();
    bagLayerSwitch_A=1;
    this->addChild(bagLayer_A,2);
    auto mask=Sprite::create("mask.png");
    mask->setScale(100);
    auto kaijiangtiao=Sprite::create("tiao.png");
    kaijiangtiao->setPosition(ccp(Director::getInstance()->getVisibleSize().width/2-250, Director::getInstance()->getVisibleSize().height/2));
    kaijiangtiao->setAnchorPoint(ccp(0,0));
    kaijiangtiao->setScaleX(0);
    FiniteTimeAction* action = Sequence::create(ScaleTo::create(3.0f,1.0f,1.0f),CCCallFuncND::create(this, callfuncND_selector(BagLayer::xianshijp), (void*)true), NULL);
    kaijiangtiao->runAction(action);
    
    bagLayer_A->addChild(mask,1);
    bagLayer_A->addChild(kaijiangtiao,1);
}

void BagLayer::xianshijp(CCNode* pSender, void* data)
{
    bagLayer_A->removeAllChildrenWithCleanup(true);
    auto mask=Sprite::create("mask.png");
    mask->setScale(100);
    
    auto wuqi=Sprite::create("wuqi1.png");
    wuqi->setScale(5);
    wuqi->setPosition(ccp(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2));
    ScaleTo *s1=ScaleTo::create(1.0,4.0,4.0);
    ScaleTo *s2=ScaleTo::create(1.0,5.0,5.0);
    Sequence *seq=Sequence::create(s1,s2,s1,s2,s1,s2,NULL);
    wuqi->runAction(seq);
    
    auto guanbi=MenuItemImage::create("xx.png","xx.png", CC_CALLBACK_1(BagLayer::allbuttoncallback, this));
    guanbi->setTag(AFTEROPENCASE);
    guanbi->setPosition(ccp(Director::getInstance()->getVisibleSize().width/2-300, Director::getInstance()->getVisibleSize().height/2));
    auto menu=Menu::create(guanbi,NULL);
    menu->setPosition(ccp(0,0));
    bagLayer_A->addChild(mask,1);
    bagLayer_A->addChild(wuqi,1);
    bagLayer_A->addChild(menu,1);
}

void BagLayer::afteropencase(Item *item)
{
    bagLayer_A->removeAllChildrenWithCleanup(true);
    bagLayerSwitch_A=0;
    auto pp=Sprite::createWithSpriteFrameName(String::createWithFormat("k%d_l%d_r%d.png",item->kind,item->level,item->rarerate)->getCString());
    pp->setPosition(ccp(item->pic->getContentSize().width/2,item->pic->getContentSize().height/2));
    item->pic->addChild(pp);
}

void BagLayer::allbuttoncallback(Ref *button)
{
    Node *item = (Node*)button;
    int tag = item->getTag();
    
    switch (item->getTag()) {
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
        case BAGCLOSEBTN:
            this->setVisible(false);
            break;
        case BAGJIA:
        {
            int num = numForSale + 1;
            if (num > selectedItem->number) {
                num = selectedItem->number;
            }
            numForSale = num;
            totalSalePrice = numForSale * selectedItem->salegold;
            itemNumForSaleLabel->setString(String::createWithFormat("%d",numForSale)->getCString());
            totalSalePriceLabel->setString(String::createWithFormat("%d",totalSalePrice)->getCString());
        }
            break;
        case BAGJIAN:
        {
            int num = numForSale - 1;
            if (num < 1) {
                num = 1;
            }
            numForSale = num;
            totalSalePrice = numForSale * selectedItem->salegold;
            itemNumForSaleLabel->setString(String::createWithFormat("%d",numForSale)->getCString());
            totalSalePriceLabel->setString(String::createWithFormat("%d",totalSalePrice)->getCString());
        }
            break;
        case BAGALL:
            numForSale = selectedItem->number;
            totalSalePrice = numForSale * selectedItem->salegold;
            itemNumForSaleLabel->setString(String::createWithFormat("%d",numForSale)->getCString());
            totalSalePriceLabel->setString(String::createWithFormat("%d",totalSalePrice)->getCString());
            break;
        case BAGSELL:
            Hero::getInstance()->Money+=totalSalePrice;
            char a[8];
            sprintf(a,"%d",Hero::getInstance()->Money);
            gamepanel->moneylab->setString(a);
            selectedItem->useitem(numForSale);
            break;
        case AFTEROPENCASE:
            afteropencase(selectedItem);
        default:
            break;
    }
}

void BagLayer::showall()
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

void BagLayer::showequipments()
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

void BagLayer::showitems()
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

void BagLayer::scrollViewDidScroll(extension::ScrollView* view)
{
    
}

void BagLayer::scrollViewDidZoom(extension::ScrollView* view)
{
    
}

