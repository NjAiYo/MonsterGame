//
//  WTMGlyphDetector.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/21.
//
//

#include "WTMGlyphDetector.h"
#include "WTMGlyphTemplate.h"
#include "Utils.h"
#include <algorithm>
using namespace std;

WTMGlyphDetector::WTMGlyphDetector()
{
    
}

WTMGlyphDetector::~WTMGlyphDetector()
{
    points->release();
    glyphs->release();
}

WTMGlyphDetector* WTMGlyphDetector::detector()
{
    WTMGlyphDetector *pRet = new WTMGlyphDetector();
    
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    
    return pRet;
}

WTMGlyphDetector* WTMGlyphDetector::defaultDetector()
{
    WTMGlyphDetector *pRet = new WTMGlyphDetector();
    
    if (pRet && pRet->initWithDefaultGlyphs())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    
    return pRet;
}

bool WTMGlyphDetector::init()
{
    timeoutSeconds = WTMGlyphDefaultTimeoutSeconds;
    lastPointTime = millisecondNow();
    points = new Array();
    points->init();
    
    glyphs = new Array();
    glyphs->init();
    return true;
}

bool WTMGlyphDetector::initWithGlyphs(Array* _glyphs)
{
    if (!init()) {
        return false;
    }
    glyphs->addObjectsFromArray(_glyphs);
    return true;
}

bool WTMGlyphDetector::initWithDefaultGlyphs()
{
    if (!init()) {
        return false;
    }
    std::string jsonData;
   
    std::string fileNames[4] = {"D","T","N","P"};
    
    for (int i = 0; i < 4; i++) {
        std::string name = fileNames[i];
        jsonData = FileUtils::getInstance()->getStringFromFile(String::createWithFormat("%s.json",name.c_str())->getCString());
        addGlyphFromJSON(jsonData.c_str(),name.c_str());
    }
    return true;
}

void WTMGlyphDetector::addGlyph(WTMGlyph *glyph)
{
    glyphs->addObject(glyph);
}

void WTMGlyphDetector::addGlyphFromJSON(const char *jsonData ,const char* name)
{
    WTMGlyph *t = new WTMGlyph();
    t->initWithName(name, jsonData);
    addGlyph(t);
    t->release();
}

void WTMGlyphDetector::removeGlyphByName(const char* name)
{
    WTMGlyph *glyph;
    int index = -1;
    for (int i = 0; i < glyphs->count(); i++) {
        glyph = (WTMGlyph*)glyphs->getObjectAtIndex(i);
        if (strcmp(glyph->name.c_str(), name)==0) {
            index = i;
            //glyphs.eraseObject(glyph);
        }
    }
    if (index != -1) {
        glyphs->removeObjectAtIndex(index);
    }
}

void WTMGlyphDetector::addPoint(PointObject* point)
{
    //DebugLog(@"Adding point to detector: %@", [NSValue valueWithCGPoint:point]);
    
    lastPointTime = millisecondNow();
    points->addObject(point);
}

void WTMGlyphDetector::removeAllPoints()
{
    points->removeAllObjects();
}
void WTMGlyphDetector::removeAllGlyphs()
{
    glyphs->removeAllObjects();
}

bool WTMGlyphDetector::compareScore(CCObject *m1, CCObject *m2) {
    Dictionary *a = dynamic_cast<Dictionary*>(m1);
    Dictionary *b = dynamic_cast<Dictionary*>(m2);
    Float *fa = (Float*)a->objectForKey("score");
    Float *fb = (Float*)b->objectForKey("score");
    //    Node *n2 = (Node*)m2;
    return fa->getValue() >= fb->getValue();
}

WTMDetectionResult* WTMGlyphDetector::detectGlyph()
{
    // Take the captured points and make a Template
    // Compare the template against existing templates and find the best match.
    // If the best match is within a threshold, consider it a true match.
    WTMDetectionResult * d = new WTMDetectionResult();
    d->autorelease();
    if (!hasEnoughPoints()) {
        log("do not have enough points:%zd",points->count());
        d->success = false;
        return d;
    }
    
    if (glyphs->count() < 1) {
        log("glyphs->count() < 1");
        d->success = false;
        return d;
    }
    
    WTMGlyphTemplate *inputTemplate = new WTMGlyphTemplate();
    inputTemplate->initWithName("Input" ,points);
    WTMGlyph *glyph = nullptr;
    
    WTMGlyph *bestMatch = nullptr;
    float highestScore = 0;
    Array* results = Array::create();
    Dictionary *result;
    for (int i = 0; i < glyphs->count(); i++) {
        glyph = (WTMGlyph*)glyphs->getObjectAtIndex(i);
        float score = 1 / glyph->recognize(inputTemplate);
        log("Glyph: %s Score: %f", glyph->name.c_str(), score);
        result = Dictionary::create();
        result->setObject(String::create(glyph->name), "name");
        result->setObject(Float::create(score), "score");
        results->addObject(result);

        if (score > highestScore) {
            highestScore = score;
            bestMatch = glyph;
        }
    }
    
    sort(results->data->arr,results->data->arr+results->count(),compareScore);
    
    log("Best Glyph: %s with a Score of: %f", bestMatch->name.c_str(), highestScore);
//    std::sort(results.begin(), results.end(), [](Dictionary* a, Dictionary* b){
//        Float *fa = (Float*)a->objectForKey("score");
//        Float *fb = (Float*)b->objectForKey("score");
//        return fa->getValue() >= fb->getValue();
//    });
    
//    NSSortDescriptor *sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"score" ascending:NO];
//    NSArray *sortedResults = [results sortedArrayUsingDescriptors:[NSArray arrayWithObjects:sortDescriptor, nil]];
    
    d->success = true;
    d->setAllScores(results);
    d->setBestMatch(bestMatch);
    d->bestScore = highestScore;
    
    delegate->glyphDetected(bestMatch, highestScore);
    delegate->glyphResults(results);
//    if ([delegate respondsToSelector: @selector(glyphDetected:withScore:)])
//        [delegate glyphDetected:bestMatch withScore:highestScore];
//    if ([delegate respondsToSelector:@selector(glyphResults:)])
//        [delegate glyphResults:sortedResults];
    
    inputTemplate->release();
    return d;
}



Array* WTMGlyphDetector::resample(Array* _points)
{
    // todo: resample!
    return points;
}

Array* WTMGlyphDetector::translate(Array* _points)
{
    // todo: translate!
    return points;
}

Array* WTMGlyphDetector::vectorize(Array* _points)
{
    // todo: vectorize!
    return points;
}

void WTMGlyphDetector::detectIfTimedOut()
{
    if (hasTimedOut()) {
        //DebugLog(@"Running detection");
        detectGlyph();
    }
}

void WTMGlyphDetector::resetIfTimedOut()
{
    if (hasTimedOut())
        reset();
}

void WTMGlyphDetector::reset()
{
    points->removeAllObjects();
}

bool WTMGlyphDetector::hasTimedOut()
{
    if (points->count() < 1) {
        return false;
    }
    double now = millisecondNow();
    double elapsed = now - lastPointTime;
//    NSTimeInterval now = [[NSDate date] timeIntervalSince1970];
//    NSInteger elapsed = now - lastPointTime;
    
    //DebugLog(@"Elapsed time since last point is: %i", elapsed);
    if (elapsed >= timeoutSeconds) {
        //DebugLog(@"Timeout detected");
        return true;
    }
    
    return false;
}

bool WTMGlyphDetector::hasEnoughPoints()
{
    return points->count() >= WTMGlyphMinPoints;
}
