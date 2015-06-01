//
//  Knife.h
//  BGT
//
//  Created by John Running on 15/3/14.
//
//

#ifndef __BGT__Knife__
#define __BGT__Knife__

#include "cocos2d.h"
#include "Weapon.h"
#include "Character.h"
#include "GeometricRecognizer.h"
#include "PathWriter.h"
#include "WTMGlyphDelegate.h"
#include "WTMGlyphDetector.h"

USING_NS_CC;
using namespace std;
using namespace DollarRecognizer;
class Knife : public Weapon, public WTMGlyphDelegate
{
private:
    //Sprite* star;
    MotionStreak* streak;
    Vec2 startTouchPosition;
    bool touchedForXuLi;
    double currentTouchTime;
    Layer *xuliLayer;

    ProgressTimer *xuliBar;
    Character *lastHitCharacter;
    float hitDistance;
    int hittime;
    GeometricRecognizer gm;
    WTMGlyphDetector *glyphDetector;
    MultiStrokeGesture path;
    std::vector<std::string> glyphNamesArray;
public:
    Knife();
    ~Knife();
    bool initWithWorld(BGTWorld *w);
    bool hittestPoint(Vec2 p);
//    bool isXuliStateDamage();
    
    //all subclasses can communicate using messages.
    bool  handleMessage(const Telegram& msg);
    //all entities must implement an update function
    void update(float dt);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
    
    
    void glyphDetected(WTMGlyph *glyph, float score);
    void glyphResults(Array* results);
    
    void clearDrawingIfTimeout();
    
    std::string getGlyphNamesString();
    void loadTemplatesWithNames(const char* firstTemplate, ...);
};

#endif /* defined(__BGT__Knife__) */
