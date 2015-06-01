//
//  WTMGlyph.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#include "WTMGlyph.h"
#include "json.h"

WTMGlyph::WTMGlyph()
{
    
}

WTMGlyph::~WTMGlyph()
{
    unistrokes->release();
    templates->release();
    strokes->release();
    strokeOrders->release();
    permutedStrokeOrders->release();
}

bool WTMGlyph::init()
{
    unistrokes = new Array();
    unistrokes->init();
    
    templates = new Array();
    templates->init();
    
    strokes = new Array();
    strokes->init();
    
    strokeOrders = new Array();
    strokeOrders->init();
    
    permutedStrokeOrders = new Array();
    permutedStrokeOrders->init();
    return true;
}

bool WTMGlyph::initWithName(const char *_name ,const Vector<WTMGlyphStroke*>& strokes)
{
    if (!init()) {
        return false;
    }
    name = _name;
    createTemplates();
    return true;
}

bool WTMGlyph::initWithName(const char *_name ,const char *jsonData)
{
    if (!init()) {
        return false;
    }
    name = _name;
    createTemplatesFromJSONData(jsonData);
    return true;
}

void WTMGlyph::createTemplates()
{
    // permute over all possible directions (heapPermute)
    permuteStrokeOrders(static_cast<int>(strokeOrders->count()));
    //DebugLog(@"Permuted stroke orders %@", permutedStrokeOrders);
    
    // create WTMGlyphTemplates from all unistrokes
    createUnistrokes();
    //DebugLog(@"Unistrokes %@", unistrokes);
    
    // actually create the templates from unistrokes
    for (int i = 0; i < unistrokes->count(); i++) {
        WTMGlyphTemplate *newTemplate = new WTMGlyphTemplate();
        newTemplate->initWithName(name.c_str(),(Array*)unistrokes->getObjectAtIndex(i));
        templates->addObject(newTemplate);
        newTemplate->release();
    }
//    DebugLog(@"Templates %@", self.templates);
//    DebugLog(@"Template count %i", [self.templates count]);
}

void WTMGlyph::createTemplatesFromJSONData(const char *jsonData)
{
    Json::Value value;
    Json::Reader reader;
    if (!reader.parse(jsonData, value)){
        CCLOG("jsonData():%s",jsonData);
        CCLOGERROR("Json::Reader failed: %s", reader.getFormattedErrorMessages().c_str());
    } else {
        //        if (value.isObject() && value.isMember("ticket")) m_ticket = value["ticket"].asInt();
        //        res = true;
    }
    //std::string okString = value["result"].asString();
    //int expired = jsonValue["expired"].asInt();
    
    
    for (int i=0; i < value.size();i++)
    {
        WTMGlyphStroke *stroke = new WTMGlyphStroke();

        Json::Value strokePoints = value[i];
        
        for (int j = 0; j < strokePoints.size(); j++) {
            Json::Value pointArray = strokePoints[j];
            stroke->addPoint(Vec2(pointArray[0].asFloat(),pointArray[1].asFloat()));
        }
        
        strokes->addObject(stroke);
        stroke->release();
        strokeOrders->addObject(Integer::create(i));
        i++;
    }
    
    //DebugLog(@"Strokes %@", self.strokes);
    //DebugLog(@"Initial stroke orders %@", strokeOrders);
    
    createTemplates();
}

void WTMGlyph::permuteStrokeOrders(int count)
{
    if (count == 1) {
        permutedStrokeOrders->addObject(strokeOrders->clone());
    } else {
        for (int i = 0; i < count; i++) {
            permuteStrokeOrders(count-1);
            
            int last = ((Integer*)strokeOrders->getObjectAtIndex(count - 1))->getValue();
            if (count % 2 == 1) {
                int first = ((Integer*)strokeOrders->getObjectAtIndex(0))->getValue();
                strokeOrders->replaceObjectAtIndex(0, Integer::create(last));
                strokeOrders->replaceObjectAtIndex(count-1, Integer::create(first));
            } else {
                int next = ((Integer*)strokeOrders->getObjectAtIndex(i))->getValue();
                strokeOrders->replaceObjectAtIndex(i, Integer::create(last));
                strokeOrders->replaceObjectAtIndex(count-1, Integer::create(next));
            }
        }
    }
}

void WTMGlyph::createUnistrokes()
{
    Array* points;
    Array*  unistroke;
    Array* strokeOrder;
    WTMGlyphStroke *stroke;
    Array* copyOfStrokePoints = Array::create();
    
    for (int r = 0; r < permutedStrokeOrders->count(); r++) {
        
        strokeOrder = (Array*)permutedStrokeOrders->getObjectAtIndex(r);
        
        for (int b = 0; b < pow(2, strokeOrder->count()); b++) {
            
            unistroke = Array::create();
            
            for (int i = 0; i < strokeOrders->count(); i++) {
                
                int strokeIndex = ((Integer*)strokeOrder->getObjectAtIndex(i))->getValue();
                stroke = (WTMGlyphStroke*)strokes->getObjectAtIndex(strokeIndex);
                copyOfStrokePoints = stroke->getPoints()->clone();
                
                if (((b >> i) & 1) == 1) {
                    copyOfStrokePoints->reverseObjects();
                    points = copyOfStrokePoints;
                } else {
                    points = copyOfStrokePoints;
                }
                
                for (int p = 0; p < points->count(); p++) {
                    unistroke->addObject(points->getObjectAtIndex(p));
                }
                
            }
            unistrokes->addObject(unistroke);
        }
    }
}

float WTMGlyph::recognize(WTMGlyphTemplate *input)
{
    float lowestDistance = FLT_MAX;
    float distance = FLT_MAX;
    
    for (int i = 0; i < templates->count(); i++) {
        WTMGlyphTemplate *atemplate = (WTMGlyphTemplate*)templates->getObjectAtIndex(i);
        distance = OptimalCosineDistance(atemplate->vector, input->vector);
        
        if (distance < lowestDistance) {
            lowestDistance = distance;
        }
    }
    //log("lowestDistance:%f",lowestDistance);
    return lowestDistance;
}

void WTMGlyph::addPoint(Vec2 point)
{
    
}

void WTMGlyph::startStroke()
{
    
}

void WTMGlyph::endStroke()
{
    
}
