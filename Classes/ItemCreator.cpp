#include "ItemCreator.h"
#include "Item.h"
#include "ItemData.h"
ItemCreator *ItemCreator::_itemcreator=nullptr;
ItemCreator *ItemCreator::getInstance()
{
	if(_itemcreator==nullptr)
	{
		_itemcreator=new ItemCreator();
	}
	return _itemcreator;
}
void ItemCreator::createItem_normal(const char *id)
{
	//����id��item���������Ƿ���ڲ����ھ����´��������ھ�
	//���Ӹ�item��number
	if(ishave(id))
	{
		for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
		{
			Item *temp=ItemData::getInstance()->Allbagitemvec.at(i);
			if(id==temp->id)
			{
				temp->addnumber();
			}
		}
	}
	else
	{
		ItemData::getInstance()->additem(new Item(id));
	}
	
}

void ItemCreator::createItem_unique(int level,int kind,int rarerate)
{
	ItemData::getInstance()->additem(new Item(level,kind,rarerate));
}

bool ItemCreator::ishave(const char *id)
{
	for(int i=0;i<ItemData::getInstance()->Allbagitemvec.size();i++)
	{
		Item *temp=ItemData::getInstance()->Allbagitemvec.at(i);
		if(id==temp->id)
			return true;
	}
	return false;
}