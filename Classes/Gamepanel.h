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
	static int LayerSwitch_A,LayerSwitch_B,LayerSwitch_C,LayerSwitch_D;//AΪ������߰�ť����ʾ�ĵ�һ�㿪�ر�ʾ��BΪ��a�������ֵ����µİ�ť������һ��Ŀ��ر�ʾ��
	int Bagopen;
	Label *moneylab;
	//��ʽ�������
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
	//��ݲ˵���ر���������
	int barY,barFlag;
	Sprite *bar;
	Size visibleSize;
	MenuItemImage *dropbtn,*bag;	
	Menu *menu;
	void showbarorhidebar();
	//�����������
	int bagonoff;
	Node *bagitemshowpanel;//������ߺ���Ӧ�Ĳ�
	Node *itemsellshow;//������Ӧ�������е��۳���ť��ʾ�Ĳ�
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

	//����������� 
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
	//��ʾ��ȫ
#define DROPBTN 0
#define BAGBTN 1
#define BAGCLOSEBTN 2
};

#endif // __HELLOWORLD_SCENE_H__
