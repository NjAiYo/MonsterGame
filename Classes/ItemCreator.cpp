#include "ItemCreator.h"
#include "Item.h"
#include "ItemData.h"
#include "Gamepanel.h"
#include "GameManager.h"

ItemCreator *ItemCreator::_itemcreator=nullptr;
ItemCreator *ItemCreator::getInstance()
{
	if(_itemcreator==nullptr)
	{
		_itemcreator=new ItemCreator();
        if(_itemcreator&&_itemcreator->init())
        {
            _itemcreator->autorelease();
            _itemcreator->retain();
        }
        else
        {
            CC_SAFE_DELETE(_itemcreator);
            _itemcreator=nullptr;
        }
	}
	return _itemcreator;
}

bool ItemCreator::init()
{
    return true;
}

bool ItemCreator::createItem_normal(const char *id)
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
        Hero *hero = GameManager::getInstance()->getPlayer();
		if(ItemData::getInstance()->Allbagitemvec.size()>=hero->capacitance)
		{
			//�����������㣬������
			log("no capacitance!!!!!!!");
			return false;
		}
        Item *item = new Item(id);
		ItemData::getInstance()->additem(item);
        item->release();
	}
    return true;
}

bool ItemCreator::createItem_unique(int level,int kind,int rarerate)
{
    Hero *hero = GameManager::getInstance()->getPlayer();
	if(ItemData::getInstance()->Allbagitemvec.size()>=hero->capacitance)
	{
		//�����������㣬������
		log("no capacitance!!!!!!!");
		return false;
	}
    Item *item = new Item(level,kind,rarerate);
	ItemData::getInstance()->additem(item);
    item->release();
    return true;
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