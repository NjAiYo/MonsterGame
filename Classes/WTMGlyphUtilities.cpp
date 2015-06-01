//
//  WTMGlyphUtilities.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#include "WTMGlyphUtilities.h"

//vector<Vec2*> *newArray = new vector<Vec2*>();
//vector<Vec2*>::iterator iter;
//for (iter = _controlPoints->begin(); iter != _controlPoints->end(); ++iter)
//{
//    newArray->push_back(new Vec2((*iter)->x, (*iter)->y));
//}
//
//PointArray *points = new (std::nothrow) PointArray();
//points->initWithCapacity(10);
//points->setControlPoints(newArray);
//
//points->autorelease();
//return points;

Array* Resample(Array* points, int num)
{
    Array* workingPoints = Array::createWithArray(points);
    Array* newPoints = Array::create(points->getObjectAtIndex(0), NULL);
    
    float I = PathLength(points) / (num -1);
    float D = 0.0;
    int i;
    PointObject* p1;
    PointObject* p2;
    PointObject* newPoint;

    
    for ( i=1; i<workingPoints->count(); i++ ) {
        p1 = (PointObject*)workingPoints->getObjectAtIndex(i-1);
        p2 = (PointObject*)workingPoints->getObjectAtIndex(i);

        float d = Distance(p1, p2);
        
        if ((D + d) >= I) {
            float x = p1->x + ((I-D) / d) * (p2->x - p1->x);
            float y = p1->y + ((I-D) / d) * (p2->y - p1->y);
            newPoint = PointObject::create(x, y);
            newPoints->addObject(newPoint);
            workingPoints = Splice(workingPoints, newPoint, i);
            D = 0.0;
        } else {
            D += d;
        }
    }
    
    // rounding error handling
    if ( newPoints->count() < num ) {
        PointObject* finalValue = (PointObject*)points->getObjectAtIndex(points->count()-1);
        
        for (int j = 0; j < (num-newPoints->count()); j++) {
            newPoints->addObject(finalValue);
        }
    }
    
    return newPoints;
}

Array* Scale(Array* points, int resolution, float threshold)
{
    Array* scaled = Array::create();
    
    Rect bb = BoundingBox(points);
    
    bool is1D = MIN(bb.size.width / bb.size.height, bb.size.height / bb.size.width) <= threshold;
    
    for (int i = 0; i < points->count(); i++) {
        PointObject* p = (PointObject*)points->getObjectAtIndex(i);
        float qx;
        float qy;
        float scale;
        
        if (is1D) {
            scale = (resolution / MAX(bb.size.width, bb.size.height));
            qx = p->x * scale;
            qy = p->y * scale;
        } else {
            qx = p->x * (resolution / bb.size.width);
            qy = p->y * (resolution / bb.size.height);
        }
        scaled->addObject(PointObject::create(qx, qy));
    }
    
    return scaled;
}

Rect BoundingBox(Array* points)
{
    float minX = FLT_MAX;
    float maxX = -FLT_MAX;
    float minY = FLT_MAX;
    float maxY = -FLT_MAX;
    
    for (int i = 0; i < points->count(); i++) {
        PointObject* pt = (PointObject*)points->getObjectAtIndex(i);
        if( pt->x < minX )
            minX = pt->x;
        if( pt->y < minY )
            minY = pt->y;
        if( pt->x > maxX )
            maxX = pt->x;
        if( pt->y > maxY )
            maxY = pt->y;
    }
    
    return Rect(minX, minY, (maxX-minX), (maxY-minY));
}

Array* Splice(Array* original, PointObject* newVal, int i)
{
    Array* spliced = Array::createWithArray(original);
    spliced->insertObject(newVal, i);
    return spliced;
}

float PathLength(Array* points)
{
    float d = 0.0;
    PointObject* p1;
    PointObject* p2;
    int i;
    
    for ( i=1; i<points->count(); i++ ) {
        p1 = (PointObject*)points->getObjectAtIndex(i-1);
        p2 = (PointObject*)points->getObjectAtIndex(i);
        
        d += Distance(p1, p2);
    }
    return d;
}

float Distance(PointObject* point1, PointObject* point2)
{
    int dX = point2->x - point1->x;
    int dY = point2->y - point1->y;
    float dist = sqrt( dX * dX + dY * dY );
    return dist;
}

Vec2 Centroid(Array* points) {
    float x = 0.0;
    float y = 0.0;
    
    for (int i = 0; i < points->count(); i++) {
        PointObject* point = (PointObject*)points->getObjectAtIndex(i);
        x += point->x;
        y += point->y;
    }
    
    x /= points->count();
    y /= points->count();
    
    return Vec2(x, y);
}

float IndicativeAngle(Array* points)
{
    Vec2 centroid = Centroid(points);
    PointObject* firstPoint = (PointObject*)points->getObjectAtIndex(0);
    float x = (centroid.x - firstPoint->x);
    float y = (centroid.y - firstPoint->y);
    
    return atan2f(y, x);
}

Array* TranslateToOrigin(Array* points)
{
    Array* translated = Array::create();
    Vec2 centroid = Centroid(points);
    float qx;
    float qy;
    
    for (int i = 0; i < points->count(); i++) {
        PointObject* point = (PointObject*)points->getObjectAtIndex(i);
        qx = point->x - centroid.x;
        qy = point->y - centroid.y;
        translated->addObject(PointObject::create(qx, qy));
    }
    return translated;
}

Vec2 CalcStartUnitVector(Array* points, int count)
{
    PointObject* pointAtIndex = (PointObject*)points->getObjectAtIndex(count);
    PointObject* firstPoint = (PointObject*)points->getObjectAtIndex(0);
    
    Vec2 v = Vec2(pointAtIndex->x - firstPoint->x, pointAtIndex->y - firstPoint->y);
    float len = sqrtf(v.x * v.x + v.y * v.y);
    
    return Vec2((v.x / len), (v.y / len));
}

FloatArrayContainer Vectorize(Array* points)
{
    FloatArrayContainer v;
    v.itemCount = 0;
    v.allocatedCount = static_cast<int>(points->count()) * 2 + 1;
    v.items = (float*)malloc(v.allocatedCount * sizeof(float));
    
    float cos = 1.0;
    float sin = 0.0;
    float sum = 0;
    PointObject* point;
    
    for (int i = 0; i < points->count(); i++) {
        point = (PointObject*)points->getObjectAtIndex(i);
        float newX = point->x * cos - point->y * sin;
        float newY = point->y * cos + point->x * sin;
        v.items[i*2] = newX;
        v.items[i*2 + 1] = newY;
        v.itemCount += 2;
        sum += newX * newX + newY * newY;
    }
    
    float magnitude = sqrtf(sum);
    for (int i = 0; i < v.itemCount; i++)
        v.items[i] /= magnitude;
    
    return v;
}

float OptimalCosineDistance(FloatArrayContainer v1, FloatArrayContainer v2)
{
    float a = 0.0;
    float b = 0.0;
    float angle;
    float score;
    
    int mincount = (v1.itemCount < v2.itemCount ? v1.itemCount : v2.itemCount);
    
    for (int ii = 0; ii < mincount; ii+=2) {
        a += v1.items[ii] * v2.items[ii] + v1.items[ii+1] * v2.items[ii+1];
        b += v1.items[ii] * v2.items[ii+1] - v1.items[ii+1] * v2.items[ii];
    }
    
    angle = atanf( b / a );
    score = acosf(a * cos(angle) + b * sin(angle));
    log("OptimalCosineDistance:%f",score);
    return score;
}
