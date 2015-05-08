#ifndef __GAMEPANEL_H__
#define __GAMEPANEL_H__

#include "cocos2d.h"
#include "Item.h"
#include "Mymenu.h"
#include "cocos-ext.h"

USING_NS_CC;
class Gamepanel : public cocos2d::Layer,public extension::ScrollViewDelegate
{
public:
	static int Money;
	static Gamepanel *gamepanel;
	static int LayerSwitch_A,LayerSwitch_B,LayerSwitch_C,LayerSwitch_D;//A为点击道具按钮后显示的第一层开关标示，B为在a基础上又点了新的按钮弹出的一层的开关标示。
	int Bagopen;
	Label *moneylab;
	//正式界面设计
	void initMainFace();
	Sprite *MainFaceBg;
	Menu *MainFaceMenu;
	MenuItemImage *Jewel;
	MenuItemImage *Vitality;
	MenuItemImage *RankList;
	MenuItemImage *Pets;
	MenuItemImage *Forge;
	MenuItemImage *Shop;
	MenuItemImage *Store;
	MenuItemImage *Mission;

	DrawNode *drawnode;
	//快捷菜单相关变量及方法
	int barY,barFlag;
	Sprite *bar;
	Size visibleSize;
	MenuItemImage *dropbtn,*bag;	
	Menu *menu;
	void showbarorhidebar();
	//背包功能相关
	int bagonoff;
	Node *bagitemshowpanel;//点击道具后响应的层
	Node *itemsellshow;//道具响应后点击其中的售出按钮显示的层
	Sprite *bagbg;
	MenuItemImage *bagclose;
	Mymenu *menuitem;
	Item *bgt;
	extension::ScrollView *scrollView;
	Layer *continerLayer;
	Vector<Item *>ALLbagitemvec; 
	void showbag();
	void initbag();
	void closebag();
	void additem();
	void deleteitem();
	void showall();
	void showequipments();
	void showitems();

	//基本功能相关 
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void allbuttoncallback(Ref* pSender);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
    CREATE_FUNC(Gamepanel);


    virtual void scrollViewDidScroll(extension::ScrollView* view);
    virtual void scrollViewDidZoom(extension::ScrollView* view);
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
    void playCallback(Ref* sender);
	//标示大全
#define DROPBTN 0
#define BAGBTN 1
#define BAGCLOSEBTN 2
};

#endif // __HELLOWORLD_SCENE_H__
