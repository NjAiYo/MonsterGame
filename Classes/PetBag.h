#ifndef __PETBAG_H__
#define __PETBAG_H__
#include "cocos2d.h"
USING_NS_CC;
class Pet;
class PetBag:public Node
{
public :
	int petBagcapacitance;
	//Vector<Pet *>petbagVec;

	static PetBag *getInstance();
	void initPetFace();
	void addPet();
	void addBagNum();

private:
	static PetBag *petbag;

};
#endif