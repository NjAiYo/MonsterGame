#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
USING_NS_CC;
class Hero:public Node
{
public :
	int level;
	int HP;
	int gong_ji_li;
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



	static Hero *getInstance();
	void initAllProperties();
	void getCurrentData(); 
private:
	static Hero* hero;
};
#endif