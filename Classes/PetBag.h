#ifndef __PETBAG_H__
#define __PETBAG_H__
#include "cocos2d.h"
USING_NS_CC;



class Pet;
class Lock;
class PetBag:public Node
{
public:
	int petBagcapacitance;
	Vector<Pet *>petbagVec;
	Vector<Lock *>petbaglockvec;
	static PetBag *getInstance();
    virtual bool init();
	void initPetFace();
	void initPetBagData();
	void addPet(std::string id);
	void addBagNum();
	void allbuttoncallback(Ref* pSender);
	Sprite *anniudi;
	MenuItemImage *shuxing,*jineng,*jinjie;
	Pet *currentPet;
	void setCurrentPet(Pet *pet);
	void shuxingface();
	void jinengface();
	void jinjieface();
	int isshuxingface,isjinengface,isjinjieface;
	void addqiyue();
	void cancelqiyue();

	void jiesuoBag();
	void Buycell();

private:
	static PetBag *petbag;
};
#endif