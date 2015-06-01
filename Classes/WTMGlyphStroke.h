//
//  WTMGlyphStroke.h
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#ifndef __MonsterGame__WTMGlyphStroke__
#define __MonsterGame__WTMGlyphStroke__
#include "PointObject.h"
#include "cocos2d.h"

USING_NS_CC;

class WTMGlyphStroke : public cocos2d::Ref
{
private:
    Array *points;
public:
    Array* getPoints();
    
    WTMGlyphStroke();
    ~WTMGlyphStroke();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    //virtual bool init();
    
    // implement the "static create()" method manually
    //CREATE_FUNC(WTMGlyphStroke);
    
    bool initWithPoints(Array *ps);
    void addPoint(Vec2 p);
};

#endif /* defined(__MonsterGame__WTMGlyphStroke__) */
