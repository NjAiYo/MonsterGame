//
//  PointObject.h
//  MonsterGame
//
//  Created by John Running on 15/5/22.
//
//

#ifndef __MonsterGame__PointObject__
#define __MonsterGame__PointObject__

#include "cocos2d.h"

USING_NS_CC;

class PointObject : public cocos2d::Ref, public Clonable
{
public:
    float x,y;
    
    PointObject();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    //virtual bool init();
    
    // implement the "static create()" method manually
    //CREATE_FUNC(WTMGlyphStroke);
    
    bool initWithXY(float x,float y);
    
    static PointObject* create(float x, float y);
    
    PointObject* clone() const;
};

#endif /* defined(__MonsterGame__PointObject__) */
