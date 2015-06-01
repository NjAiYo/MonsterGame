//
//  WTMGlyphTemplate.h
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#ifndef __MonsterGame__WTMGlyphTemplate__
#define __MonsterGame__WTMGlyphTemplate__

#include "cocos2d.h"
#include "WTMGlyphUtilities.h"
#include "PointObject.h"

USING_NS_CC;

class WTMGlyphTemplate : public cocos2d::Ref
{
public:
    std::string name;
    Array* points;
    Array* normalizedPoints;
    Vec2 startUnitVector;
    FloatArrayContainer vector;
    
    WTMGlyphTemplate();
    ~WTMGlyphTemplate();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    //virtual bool init();
    
    // implement the "static create()" method manually
    //CREATE_FUNC(WTMGlyphStroke);
    
    bool initWithName(const char* _name,Array* ps);
    void normalize();
};

#endif /* defined(__MonsterGame__WTMGlyphTemplate__) */
