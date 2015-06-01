//
//  WTMGlyphDetector.h
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#ifndef __MonsterGame__WTMGlyphDetector__
#define __MonsterGame__WTMGlyphDetector__

#include "cocos2d.h"
#include "WTMGlyph.h"
#include "WTMGlyphDelegate.h"
#include "WTMDetectionResult.h"
#include "WTMGlyph.h"

USING_NS_CC;


class WTMGlyphDetector : public cocos2d::Ref
{
public:
    WTMGlyphDetector();
    ~WTMGlyphDetector();
    WTMGlyphDelegate *delegate;
    
    Array* points;
    Array* glyphs;
    
    int timeoutSeconds;
    double lastPointTime;
    
    
    static WTMGlyphDetector* detector();
    static WTMGlyphDetector* defaultDetector();
    bool init();
    bool initWithGlyphs(Array* _glyphs);
    bool initWithDefaultGlyphs();
    
    void addGlyph(WTMGlyph *glyph);
    void addGlyphFromJSON(const char *jsonData ,const char* name);
    void removeGlyphByName(const char* name);
    
    void addPoint(PointObject* point);
    void removeAllPoints();
    void removeAllGlyphs();
    
    WTMDetectionResult* detectGlyph();
    
    Array* resample(Array* _points);
    Array* translate(Array* _points);
    Array* vectorize(Array* _points);
    
    void detectIfTimedOut();
    void resetIfTimedOut();
    void reset();
    bool hasTimedOut();
    bool hasEnoughPoints();
    
    static bool compareScore(CCObject *m1, CCObject *m2);
};

#endif /* defined(__MonsterGame__WTMGlyphDetector__) */
