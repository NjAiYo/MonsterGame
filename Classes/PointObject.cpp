//
//  PointObject.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/22.
//
//

#include "PointObject.h"

PointObject::PointObject()
:x(0)
,y(0)
{
    
}

PointObject* PointObject::clone() const
{
    return PointObject::create(x, y);
}

bool PointObject::initWithXY(float xv,float yv)
{
    x = xv;
    y = yv;
    return true;
}

PointObject* PointObject::create(float xv, float yv)
{
    PointObject *pRet = new PointObject();
    
    if (pRet && pRet->initWithXY(xv,yv))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    
    return pRet;
}
