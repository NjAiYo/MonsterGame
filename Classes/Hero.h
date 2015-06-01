#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
#include "TalentPoint.h"
USING_NS_CC;
class Item;
//class TalentPoint;
class Hero:public Node
{
public :
	int Money;
	int skillpoint;
	float Exp;
	int level;
	int HP;
	int gong_ji_li_dao;
	int gong_ji_li_qiang;
	int fang_yu_li;
	float bao_ji;
	float bao_ji_shang_hai;
	float shan_bi_lv;
	float ming_zhong_lv;
	float xing_yun_zhi;
	int dan_yao_zhi;
	int nai_jiu_zhi;
	int neng_liang_zhi;
	float qiang_xuan_yun_ji_lv;
	float jin_bi_e_wai_diao_luo_lv;
	float xue_qiu_shi_qu_liang;
	float neng_liang_qiu_shi_qu_liang;
	float dan_yao_shi_qu_liang;
	float jin_yan_zhi;
	float jin_yan_zhi_huo_de_liang;
	float neng_liang_huo_de;
	int lian_ji_shu;
	int te_shu_ji_xiao_hao_jian_di;
	float xi_xue_gai_lv;
	float xi_xue_liang;
	float gong_ji_li_bai_fen_bi;
	float HP_bai_fen_bi;
	int wu_qi_xiang_kong;
    int capacitance;

	static Hero *getInstance();
    virtual bool init();
	void initAllProperties();
	void updateProperties();
	void getCurrentData();
	void initJueseFace();
	void buttoncallback(Ref *pSender);

	void initEquipmentpanel(int kind);

	void compareEquipment(Item *item);//暂时不用
	void shouEquipmentdata(Item *item);

	void equipe_item(int kind);
	
	void shuxingface();
	void jinengface();
	void tianfuface();

	Item *NeckLace;
	Item *Ring1;
	Item *Ring2;
	Item *Weapon1;
	Item *Weapon2;
	Item *Pet1;
	Item *Pet2;
	Item *Pet3;
	Sprite *di,*huatiao;
	Label *skillpointlab;
	MenuItemImage *shuxing,*jineng,*tianfu;

	Vector<TalentPoint *>TalentData;
	void initTalentData();
	void resetTalent();

	int isEquip[12];//用于装备道具的使用状态判断等处理
	Sprite *showpic[12];//显示装备中的道具及装备等对应上面的下标

	void addMoney(int num);


private:
	static Hero* hero;
};
#endif