//
//  WTMDetectionResult.h
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#ifndef __MonsterGame__WTMDetectionResult__
#define __MonsterGame__WTMDetectionResult__

#include "cocos2d.h"

USING_NS_CC;

class WTMGlyph;

class WTMDetectionResult : public cocos2d::Ref
{
    Array* allScores;
    WTMGlyph *bestMatch;
public:
    WTMDetectionResult();
    ~WTMDetectionResult();
    
    void setBestMatch(WTMGlyph *bestMatch);
    WTMGlyph* getBestMatch();
    
    float bestScore;
    void setAllScores(Array* as);
    Array* getAllScores();
    bool success;
};

#endif /* defined(__MonsterGame__WTMDetectionResult__) */
