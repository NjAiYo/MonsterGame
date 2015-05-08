#ifndef __BAGITEM_H__
#define __BAGITEM_H__

#include "cocos2d.h"

USING_NS_CC;
class Item:public Node
{
public:
	std::string id;
	int kind;
	int number;
	int rarerate;
	int effection;//普通道具的功能，特殊道具为自己随机产生多个功能，不在文件中描述
	int salegold;
	int cd;
	std::string name;
	std::string picname;
	std::string detail;
	int x,y;
	int sellnum;
	MenuItemImage *pic;
	Label *numlab;
	Label *sellnumlab;
	//特殊属性随机生成不由外部文件描述
	int level;

	float ping_jun_gong_ji_li;
	float shang_xian_gong_ji_li;
	float xia_xian_gong_ji_li;

	float gong_ji_li_jia_cheng;
	float HP_shangxian;
	int  fang_yu_li;
	float bao_ji_lv;
	float bao_ji_shang_hai;
	int dan_yao_shang_xian;
	int nai_jiu_shang_xian;
	float qiang_xuan_yun_gai_lv;
	float shi_qu_xue_qiu_shang_xian;
	float shi_qu_neng_liang_qiu_shang_xian;
	float shi_qu_dan_yao_shang_xian;
	int wu_qi_xiang_qian;

	float jin_bi_huo_de_ti_gao;
	float jin_yan_huo_de_ti_gao;
	int xin_yun_zhi_ti_gao;

	float ming_zhong_lv;
	float shan_bi_lv;
	int neng_liang_huo_de_su_du;
	int lian_ji_shu;
	int te_shu_ji_xiao_hao_jian_di;
	float xi_xue_gai_lv;

	static int randomforproperty;
	int gailva,gailvb;//参与概率处理

	Item(std::string id);
	Item(int level,int kind,int rarerate);
	void addnumber();
	void useitem(int num);//使用并且删除如果number为0那么删除该道具
	void releaseself();//用于立即清除，比如扔掉道具等的
	void showdetail(int kind);
	void buttoncallback(Ref* pSender);
	void operationcallback(Ref* pSender);
	void shownumber(int num);
	void showsellpanel();

	void randomgetitemdata(int kind,int rarerate);
	void setweapon_knife(int rarerate);
	void setweapon_gun(int rarerate);
	void setnecklace(int rarerate);
	void setring(int rarerate);
	void randproperty_knife(int num);
	void randproperty_gun(int num);
	void randproperty_necklace(int num);
	void randproperty_ring(int num);

	void randuniqueid();

	void kaixiangzi();//开武器装备等的效果处理
	int isopen;//随机生成的道具用的标示，0标示未开启，可以开；1标示开启过了，可以查看详细可以卖。
	void xianshijp(CCNode* pSender, void* data);//显示奖品的方法
};
#endif