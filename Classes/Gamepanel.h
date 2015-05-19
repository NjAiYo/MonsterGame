#ifndef __GAMEPANEL_H__
#define __GAMEPANEL_H__

#include "cocos2d.h"
#include "Mymenu.h"
#include "cocos-ext.h"
#include <spine/spine-cocos2dx.h>
using namespace spine;
USING_NS_CC;
class Item;
class Gamepanel : public cocos2d::Layer,public extension::ScrollViewDelegate
{
public:
	static int Money;
	static Gamepanel *gamepanel;
	static int LayerSwitch_A,LayerSwitch_B,LayerSwitch_C,LayerSwitch_D;//AΪ������߰�ť����ʾ�ĵ�һ�㿪�ر�ʾ��BΪ��a�������ֵ����µİ�ť������һ��Ŀ��ر�ʾ��
	static int JueseSysytem,DuanzaoSystem,BagSystem;//�ڲ�ͬϵͳ�е��߰�ť��Ӧ��ͬ�Ĳ���
	static float scaleFactory;
	Label *moneylab,*zuanshilab,*tililab;
	//��ʽ���漰�������
	void initMainFace();
	void initdata();
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
	//��ݲ˵���ر���������
	int barY,barFlag;
	Sprite *bar;
	Size visibleSize;
	MenuItemImage *dropbtn,*bag;	
	Menu *menu;
	void showbarorhidebar();
	//�����������
	int capacitance;
	int bagonoff;
	int bagline;
	MenuItemImage *bagquanbu,*bagzhuangbei,*bagcailiao,*bagdaoju;

	Node *Layer_A;//������ߺ���Ӧ�Ĳ�
	Node *Layer_B;//������Ӧ�������е��۳���ť��ʾ�Ĳ�
	Mymenu *menuitem;
	Item *bgt;
	extension::ScrollView *scrollView;
	Layer *continerLayer;
	
	void showbag();
	void initbag();
	void closebag();
	void additem();
	void deleteitem();
	void showall();
	void showequipments();
	void showitems();
	//���﹦�����
	Node *Layer_C;
	Node *Layer_D;
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
	//��ʾ��ȫ
#define DROPBTN 0
#define BAGBTN 1
#define BAGCLOSEBTN 2
#define CHONGWU 3
#define MISSION 4
#define JUESE 10
#define SHOWALL 20
#define SHOWCAILIAO 21
#define SHOWZHUANGBEI 22
#define SHOWDAOJU 23
};

#endif // __HELLOWORLD_SCENE_H__
