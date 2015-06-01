//
//  WTMGlyphDelegate.h
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#ifndef __MonsterGame__WTMGlyphDelegate__
#define __MonsterGame__WTMGlyphDelegate__

#include "cocos2d.h"

USING_NS_CC;

class WTMGlyph;

class WTMGlyphDelegate
{
public:
    virtual void glyphDetected(WTMGlyph *glyph, float score){};
    virtual void glyphResults(Array* results){};
};

#endif /* defined(__MonsterGame__WTMGlyphDelegate__) */
