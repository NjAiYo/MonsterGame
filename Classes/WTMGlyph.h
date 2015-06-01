//
//  WTMGlyph.h
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#ifndef __MonsterGame__WTMGlyph__
#define __MonsterGame__WTMGlyph__

#include "cocos2d.h"
#include "WTMGlyphStroke.h"
#include "WTMGlyphTemplate.h"
#include "PointObject.h"

USING_NS_CC;

class WTMGlyph : public cocos2d::Ref
{
    Array* strokeOrders;
    Array* permutedStrokeOrders;
    //std::vector<Vector<PointObject*>>  unistrokes;
    Array *unistrokes;
    WTMGlyphStroke *currentStroke;
    
public:
    WTMGlyph();
    ~WTMGlyph();
    std::string name;
    Array* templates;
    
    Array* strokes;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    //virtual bool init();
    
    // implement the "static create()" method manually
    //CREATE_FUNC(WTMGlyphStroke);
    
    bool init();
    bool initWithName(const char *_name ,const Vector<WTMGlyphStroke*>& strokes);
    bool initWithName(const char *_name ,const char *jsonData);
    
    void createTemplates();
    void createTemplatesFromJSONData(const char *jsonData);
    void permuteStrokeOrders(int count);
    void createUnistrokes();
    
    float recognize(WTMGlyphTemplate *_template);
    
    void addPoint(Vec2 point);
    void startStroke();
    void endStroke();
};

#endif /* defined(__MonsterGame__WTMGlyph__) */
