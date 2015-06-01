//
//  WTMDetectionResult.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#include "WTMDetectionResult.h"
#include "WTMGlyph.h"

WTMDetectionResult::WTMDetectionResult()
:allScores(nullptr)
,bestMatch(nullptr)
{
    
}

void WTMDetectionResult::setBestMatch(WTMGlyph *bm)
{
    CC_SAFE_RELEASE_NULL(bestMatch);
    bestMatch = bm;
    bestMatch->retain();
}

WTMGlyph* WTMDetectionResult::getBestMatch()
{
    return bestMatch;
}

WTMDetectionResult::~WTMDetectionResult()
{
    CC_SAFE_RELEASE_NULL(allScores);
    CC_SAFE_RELEASE_NULL(bestMatch);
}

void WTMDetectionResult::setAllScores(Array* as)
{
    CC_SAFE_RELEASE_NULL(allScores);
    allScores = as;
    allScores->retain();
}

Array* WTMDetectionResult::getAllScores()
{
    return allScores;
}
