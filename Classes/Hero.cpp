#include "Hero.h"
Hero *Hero::hero=nullptr;
Hero *Hero::getInstance()
{
	if(hero==nullptr)
	{
		hero=new Hero();
	} 
	return hero;
}

void Hero::initAllProperties()
{
	level=1;
	HP=(int)(100*level*1.1);
	gong_ji_li=0;
	fang_yu_li=5;
	bao_ji=0.05;
	bao_ji_shang_hai=1;
	shan_bi_lv=0;
	ming_zhong_lv=0.75;
	xing_yun_zhi=10;
	dan_yao_zhi=100;
	nai_jiu_zhi=100;
	neng_liang_zhi=100;
	qiang_xuan_yun_ji_lv=0.05;
	jin_bi_e_wai_diao_luo_lv=0;
	xue_qiu_shi_qu_liang=0;
	neng_liang_qiu_shi_qu_liang=0;
	dan_yao_shi_qu_liang=0;
	jin_yan_zhi=0;
	jin_yan_zhi_huo_de_liang=0;
	neng_liang_huo_de=0;
	lian_ji_shu=0;
	te_shu_ji_xiao_hao_jian_di=0;
	xi_xue_gai_lv=0;
	xi_xue_liang=0;
	gong_ji_li_bai_fen_bi=0;
	HP_bai_fen_bi=0;
	wu_qi_xiang_kong=0;
}

