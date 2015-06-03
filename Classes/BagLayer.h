//
//  BagLayer.h
//  MonsterGame
//
//  Created by 南京艾游网络文化有限公司 on 15/5/29.
//
//

#ifndef __MonsterGame__BagLayer__
#define __MonsterGame__BagLayer__

#include "cocos2d.h"
#include "GameManager.h"
#include "cocos-ext.h"
#include "Hero.h"
#include "Mymenu.h"
USING_NS_CC;

USING_NS_CC_EXT;
class Gamepanel;
class Item;
class BagLayer : public cocos2d::Layer,public extension::ScrollViewDelegate
{
private:
    Gamepanel* gamepanel;
    Hero *hero;
    Node *bagLayer_A,*bagLayer_B;//a用于开箱子，b用于显示武器装备数据
    int bagLayerSwitch_A,bagLayerSwitch_B;
    MenuItemImage *bagquanbu;
    MenuItemImage *bagzhuangbei;
    MenuItemImage *bagcailiao;
    MenuItemImage *bagdaoju;
    float scaleFactory;
    Mymenu *menuitem;
    Sprite *itemIconSprite;
    
    Sprite *glowSprite;
    
    MenuItemImage *sellButton;
    
    Label *itemNameLabel;
    Label *itemPriceLabel;
    Label *itemNumLabel;
    Label *itemDescriptionLabel;
    
    Label *itemNumForSaleLabel;
    Label *totalSalePriceLabel;
    Item *selectedItem;
    int numForSale;
    int totalSalePrice;
public:
    BagLayer();
    int bagline;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithGamePanel(Gamepanel *gs);

    void allbuttoncallback(Ref *button);
    
    virtual void scrollViewDidScroll(extension::ScrollView* view);
    virtual void scrollViewDidZoom(extension::ScrollView* view);
    
    void itemClickedHandler(EventCustom* event);
    void openCaseHandler(EventCustom* event);
    void updateItemsHandler(EventCustom* event);
    void showall();
    void showequipments();
    void showitems();
    //显示物品信息
    void showItemDetail(Item* item);
    //开箱子
    void kaixiangzi(Item *item);
    void xianshijp(CCNode* pSender, void* data);
    void afteropencase(Item *item);
};

#endif /* defined(__MonsterGame__BagLayer__) */
