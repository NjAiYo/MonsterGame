#include "PetBag.h"
#include "Gamepanel.h"

PetBag *PetBag::petbag=nullptr;
PetBag *PetBag::getInstance()
{
	if(petbag==nullptr)
	{
		petbag==new PetBag();
	}
	return petbag;
}

void PetBag::initPetFace()
{
	if(Gamepanel::LayerSwitch_A==0)
	{
		Gamepanel::LayerSwitch_A=1;
		Gamepanel::gamepanel->Layer_A=Node::create();
		Gamepanel::gamepanel->addChild(Gamepanel::gamepanel->Layer_A);

		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto mask=Sprite::create("mask.png");
		mask->setScale(100);
        Gamepanel::gamepanel->Layer_A->addChild(mask);

		auto petbg=Sprite::createWithSpriteFrameName("ditu2.png");
		petbg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
		petbg->setScale(Gamepanel::scaleFactory);
		Gamepanel::gamepanel->Layer_A->addChild(petbg);
        
        
	}
}