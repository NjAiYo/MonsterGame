#ifndef __STRINGUTIL_H__
#define __STRINGUTIL_H__
#include "cocos2d.h"
class StringUtil:public cocos2d::Ref
{
public:
	static StringUtil *getInstance();
	virtual bool init();
	cocos2d::ValueVector split(const char *srcStr,const char *sSep);
private:
	static StringUtil *m_StringUtil;
};
#endif