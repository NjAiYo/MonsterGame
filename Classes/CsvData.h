#ifndef __CSVDATA_H__
#define __CSVDATA_H__
#include "cocos2d.h"
class CsvData:public cocos2d::Ref
{
public:
	CREATE_FUNC(CsvData);
	virtual bool init();
	void addLineData(cocos2d::ValueVector lineData);
	cocos2d::ValueVector getSingleLineData(int iLine);
	cocos2d::Size getRowColNum();
private:
	cocos2d::ValueVector m_allLinesVec;
	int m_iColNum;
};
#endif