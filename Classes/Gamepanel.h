#ifndef __GAMEPANEL_H__
#define __GAMEPANEL_H__

#include "cocos2d.h"
#include "Mymenu.h"
#include "cocos-ext.h"
#include "Hero.h"
#include "GamepanelHeader.h"


#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)

#include "spine\spine.h"//win,android
#include "spine\spine-cocos2dx.h"//win,android
#else
#include <spine/spine-cocos2dx.h>
#endif




using namespace spine;
USING_NS_CC;
class Item;
class BagLayer;
class Gamepanel : public cocos2d::Layer,public extension::ScrollViewDelegate
{
public:
    static Gamepanel *gamepanel;
    static short LayerSwitch_A;
    static short LayerSwitch_B;
    static short LayerSwitch_C;
    static short LayerSwitch_D;
    static short JueseSysytem;
    static short DuanzaoSystem;
    static short BagSystem;
    static short TalentSystem;
    static short EquipSystem;
    static float scaleFactory;
    
	Label *moneylab,*zuanshilab,*tililab;
    BagLayer *bagLayer;
    Hero *hero;
    
	Sprite *MainFaceBg;
	Menu *MainFaceMenu;
	MenuItemImage *RankList;
	MenuItemImage *Pets;
	MenuItemImage *Forge;
	MenuItemImage *Shop;
	MenuItemImage *Store;
	MenuItemImage *Mission;
	MenuItemImage *GYM;

	SkeletonAnimation* Heroskeleton;
	DrawNode *drawnode;


	Size visibleSize;
	MenuItemImage *dropbtn,*bag;	
	Menu *menu;

	int bagonoff;
	int bagline;
	MenuItemImage *bagquanbu,*bagzhuangbei,*bagcailiao,*bagdaoju;

	Node *Layer_A;
	Node *Layer_B;
	Mymenu *menuitem,*menuitem1;
	Item *bgt;
	extension::ScrollView *scrollView,*scrollView1;
	Layer *continerLayer,*continerLayer1;
    
    void initMainFace();
    void initdata();

    void jiesuoBag();
    void buyCell();
    
    
	void showbag();
	void initbag();
	void closebag();
	void additem();
	void deleteitem();
	void showall();
	void showequipments();
	void showitems();

	Node *Layer_C;
	Node *Layer_D;


    void allbuttoncallback(Ref* pSender);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);



    virtual void scrollViewDidScroll(extension::ScrollView* view);
    virtual void scrollViewDidZoom(extension::ScrollView* view);
	void update(float dt);
    
    

    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Gamepanel);

};

#endif // __HELLOWORLD_SCENE_H__
