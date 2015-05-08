#include "CsvUtil.h"
#include "StringUtil.h"
CsvUtil *CsvUtil::m_CsvUtil=NULL;
CsvUtil *CsvUtil::getInstance()
{
	if(m_CsvUtil==NULL)
	{
		m_CsvUtil=new CsvUtil();
		if(m_CsvUtil&&m_CsvUtil->init())
		{
			m_CsvUtil->autorelease();
			m_CsvUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_CsvUtil);
			m_CsvUtil=NULL;
		}
	}
	return m_CsvUtil;
}

bool CsvUtil::init()
{
	return true;
}

void CsvUtil::loadFile(const char *filePath)
{
	CsvData *csvdata=CsvData::create();
	string str=FileUtils::getInstance()->getStringFromFile(filePath);
	ValueVector linesList =StringUtil::getInstance()->split(str.c_str(),"\n");
	for(auto value:linesList)
	{
		ValueVector temp=StringUtil::getInstance()->split(value.asString().c_str(),",");
		csvdata->addLineData(temp);
	}
	mCsvMap.insert(filePath,csvdata);
}

Value CsvUtil::getValue(int Row,int Col, const char *filePath)
{
	auto csvData=mCsvMap.at(filePath);
	if(csvData==nullptr)
	{
		loadFile(filePath);
		csvData=mCsvMap.at(filePath);
	}
	ValueVector rowVector=csvData->getSingleLineData(Row);
	Value colValue=rowVector.at(Col);
	return colValue;
}

const string CsvUtil::get(int Row,int Col,const char *filePath)
{
	Value colvalue=getValue(Row,Col,filePath);
	return colvalue.asString();
}

const int CsvUtil::getInt(int Row,int Col,const char *filePath)
{
	Value value=getValue(Row,Col,filePath);
	return value.asInt();
}

const Size CsvUtil::getFileRowColNum(const char *filePath)
{
	auto csvData=mCsvMap.at(filePath);
	if(csvData==nullptr)
	{
		loadFile(filePath);
		csvData=mCsvMap.at(filePath);
	}
	Size size=csvData->getRowColNum();
	return size;
}

const int CsvUtil::findValueInWithLine( const char* chValue, int iValueCol, const char* csvFilePath )
{
    Size csvSize = getFileRowColNum(csvFilePath);
	
    int iLine = -1;
    for(int i = 0; i < (int)csvSize.width; i++)
	{
        string ID = get(i, iValueCol, csvFilePath);
        if(Value(ID).asString().compare(chValue) == 0)
		{
            iLine = i;
            break;
        }
    }
	
    return iLine;
}