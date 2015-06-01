//
//  WTMGlyphTemplate.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#include "WTMGlyphTemplate.h"

WTMGlyphTemplate::WTMGlyphTemplate()
:normalizedPoints(NULL)
{
    
}

WTMGlyphTemplate::~WTMGlyphTemplate()
{
    points->release();
    free(vector.items);
    CC_SAFE_RELEASE_NULL(normalizedPoints);
}

bool WTMGlyphTemplate::initWithName(const char* _name,Array* ps)
{
    name = _name;
    points = new Array();
    points->init();
    points->addObjectsFromArray(ps);

    normalize();
    return true;
}

void WTMGlyphTemplate::normalize()
{
    // Resample the points
    Array* resampled = Resample(points, WTMGlyphResamplePointsCount);
    for (int i = 0; i <resampled->count(); i++) {
        PointObject *p = (PointObject*)resampled->getObjectAtIndex(i);
        //log("resampled:%f,%f",p->x,p->y);
    }
    //DebugLog(@"Resampled points %@", resampled);
    
    // Calculate indicative angle (radians)
    //    float radians = IndicativeAngle(resampled);
    //    DebugLog(@"Indicative angle %f", radians);
    
    // Scale points to the desired resolution
    Array* scaled = Scale(resampled, WTMGlyphResolution, WTMGlyph1DThreshold);
    //DebugLog(@"Scaled points %@", scaled);
    
    // Translate points to 0,0
    Array* translated = TranslateToOrigin(scaled);
    //DebugLog(@"Translated points %@", translated);
    
    normalizedPoints = translated;
    normalizedPoints->retain();
    
    // Calculate start unit vector
    startUnitVector = CalcStartUnitVector(translated, WTMGlyphStartAngleIndex);
    
    // Vectorize
    vector = Vectorize(normalizedPoints);
}
