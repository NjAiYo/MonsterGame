#include "ItemData.h"
#include "Item.h"
ItemData *ItemData::_bagsystem= nullptr;
ItemData *ItemData::getInstance()
{
	if(_bagsystem==nullptr)
	{
		_bagsystem=new ItemData();
        if(_bagsystem&&_bagsystem->init())
        {
            _bagsystem->autorelease();
            _bagsystem->retain();
        }
        else
        {
            CC_SAFE_DELETE(_bagsystem);
            _bagsystem=nullptr;
        }
	}
	return _bagsystem;
}
bool ItemData::init()
{
    return true;
}
void ItemData::initrecorddata()
{

}

void ItemData::additem(Item *item)
{
	Allbagitemvec.pushBack(item);
    EventCustom event("itemAdded");
    event.setUserData(item);
    _eventDispatcher->dispatchEvent(&event);
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
				temp=NULL;
                EventCustom event("itemDeleted");
                event.setUserData((void*)id);
                _eventDispatcher->dispatchEvent(&event);
			}
		}
	}
}
