//
//  BGTMap.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTMap.h"

#include "Gamepanel.h"
BGTMap::BGTMap()
:currentLevel(0)
{
    
}

bool BGTMap::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    
    return true;
}

void BGTMap::gotoMainScene()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1, Gamepanel::createScene()));
}

