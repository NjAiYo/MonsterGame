#include "ItemData.h"
#include "Item.h"
ItemData *ItemData::_bagsystem= nullptr;
ItemData *ItemData::getInstance()
{
	if(_bagsystem==nullptr)
	{
		_bagsystem=new ItemData();
	}
	return _bagsystem;
}

void ItemData::initrecorddata()
{

}

void ItemData::additem(Item *item)
{
	Allbagitemvec.pushBack(item);
}

void ItemData::deleteitem(const char *id)
{
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{
		Item *temp=ItemData::getInstance()->Allbagitemvec.at(i);
		if(id==temp->id)
		{
			if(temp->number<=0)
			{
				temp->releaseself();
				Allbagitemvec.erase(i);
				delete temp;
				temp=NULL;
			}
		}
	}
}
