#ifndef __CSVUTIL_H__
#define __CSVUTIL_H__
#include "cocos2d.h"
#include "CsvData.h"
using namespace std;
using namespace cocos2d;
class CsvUtil:public Ref
{
public:
	static CsvUtil *getInstance();
	virtual bool init();
	void loadFile(const char *filePath);
	Value getValue(int Row,int Col, const char *filePath);
	const string get(int Row,int Col,const char *filePath);
	const int getInt(int Row,int Col,const char *filePath);
	const Size getFileRowColNum(const char *filePath);

	const int findValueInWithLine(const char *chValue,int iValueCol,const char *csvFilePath);
private:
	static CsvUtil *m_CsvUtil;
	Map<string,CsvData*>mCsvMap;
};
#endif