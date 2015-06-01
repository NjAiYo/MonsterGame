//
//  WTMGlyphUtilities.h
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#ifndef __MonsterGame__WTMGlyphUtilities__
#define __MonsterGame__WTMGlyphUtilities__

#include "cocos2d.h"
#include "PointObject.h"

USING_NS_CC;

#define WTMGlyphDefaultTimeoutSeconds 2
#define WTMGlyphMinInflectionPointCount 10

#define WTMGlyphResolution 320
#define WTMGlyphResamplePointsCount 96
#define WTMGlyphStartAngleIndex 12

#define WTMGlyph1DThreshold 0.25

#define WTMGlyphMinPoints 10

typedef struct FloatArrayContainer {
    float * items;
    int itemCount;
    int allocatedCount;
} FloatArrayContainer;

Vec2 Centroid(Array* points);
Array* Resample(Array* points, int num);
Array* Scale(Array* points, int resolution, float threshold);
Rect BoundingBox(Array* points);
Array* Splice(Array* original, PointObject* newVal, int i);
float PathLength(Array* points);
float Distance(PointObject* point1, PointObject* point2);
float IndicativeAngle(Array* points);
Array* TranslateToOrigin(Array* points);
Vec2 CalcStartUnitVector(Array*, int count);
FloatArrayContainer Vectorize(Array* points);
float OptimalCosineDistance(FloatArrayContainer v1, FloatArrayContainer v2);

#endif /* defined(__MonsterGame__WTMGlyphUtilities__) */
