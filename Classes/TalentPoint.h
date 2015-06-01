#ifndef __TP_H__
#define __TP_H__
#include "cocos2d.h"
class TalentPoint:public cocos2d::Node
{
public:
	TalentPoint(int id,std::string talentdetail,std::string talentpicname,int needpoints,float addvalue,int uselevel);
	int id;
	int state;//-1表示未激活，0表示激活一个点，1表示完全激活
	std::string talentdetail;
	std::string talentpicname;
	int needpoints;
	int currentpoints;
	float addvalue;
	int uselevel;
	cocos2d::MenuItemImage *pic;
	cocos2d::Sprite *qiu1,*qiu2;
	void buttoncallback(cocos2d::Ref *pSender);
	void opentalent(cocos2d::Ref *pSender);
};
#endif