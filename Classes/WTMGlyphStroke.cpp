//
//  WTMGlyphStroke.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#include "WTMGlyphStroke.h"

WTMGlyphStroke::WTMGlyphStroke()
{
    points = new Array();
    points->init();
}

WTMGlyphStroke::~WTMGlyphStroke()
{
    points->release();
}

Array* WTMGlyphStroke::getPoints()
{
    return points;
}

bool WTMGlyphStroke::initWithPoints(Array* ps)
{

    points->addObjectsFromArray(ps);

    return true;
}

void WTMGlyphStroke::addPoint(Vec2 p)
{
    points->addObject(PointObject::create(p.x, p.y));
}
