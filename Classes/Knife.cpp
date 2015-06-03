//
//  Knife.cpp
//  BGT
//
//  Created by John Running on 15/3/14.
//
//

#include "Knife.h"
#include "BGTWorld.h"
#include "MessageDispatcher.h"
#include "AppDelegate.h"
#include <SimpleAudioEngine.h>

Knife::Knife()
{
    
}

Knife::~Knife()
{
    glyphDetector->release();
}

bool Knife::initWithWorld(BGTWorld *w)
{
    if (Weapon::initWithWorld(w)) {
        lastHitCharacter = nullptr;
        streak = MotionStreak::create(0.5f, 50, 30, Color3B::WHITE, "steak.png");
        //    streak = MotionStreak::create(0.5f, 1, 10, Color3B::RED, "steak.png");
        streak->setPosition(Vec2(-1000,-1000)); // …Ë÷√ÕœŒ≤streakµƒŒª÷√
        addChild(streak);
        type = WeaponTypeKnife;
        
        xuliLayer = Layer::create();
        addChild(xuliLayer);
        xuliLayer->setVisible(false);
        xuliBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("powerprobar.png"));

        xuliBar->setType(ProgressTimer::Type::RADIAL);
//        xuliBar->setMidpoint(cc.p(0,1));
//        xuliBar->setBarChangeRate(cc.p(1, 0));
        xuliBar->setPercentage(0);
        xuliLayer->addChild(xuliBar);
        xuliBar->setPosition(-1000,-1000);
        xuliTotalTime = 500;//2秒
        xuliTimePast = 0;
        origDamage = 10;
        durability = 100;
        damage = origDamage;
        isXuliDamage = false;
        
        
        glyphDetector = WTMGlyphDetector::detector();
        glyphDetector->delegate = this;
        glyphDetector->timeoutSeconds = 1;
        glyphDetector->retain();
        
        //loadTemplatesWithNames("C","X","Z", "T", "W", "V", "circle", "square", "triangle", NULL);
   
        loadTemplatesWithNames("V","X", "triangle", NULL);

//        gm.loadMultistrokeTemplates();
//        vector<string> MgestureList;
//        MgestureList.push_back("T");
//        MgestureList.push_back("X");
//        MgestureList.push_back("P");
//        MgestureList.push_back("D");
//        MgestureList.push_back("I");
//        MgestureList.push_back("N");
//        gm.activateMultiStrokesTemplates(MgestureList);

        
        
//        //
//        //single-stroke gesture recognition
//        //
//        GeometricRecognizer g;
//        g.loadTemplates();
//        
//        // Sub-list of templates to search inside, should end by a "0"
//        vector<string> gesturesList;
//        gesturesList.push_back("Circle");
//        gesturesList.push_back("Delete");
//        gesturesList.push_back("Arrow");
//        gesturesList.push_back("0");
//        g.activateTemplates(gesturesList);
//        
//        RecognitionResult r=g.recognize(getGestureArrow());
//        cout << "Recognized gesture: " << r.name << endl;
//        cout << "1$ Score:" << r.score << endl;
//        
//        RecognitionResult rp=g.recognize(getGestureArrow(), "protractor");
//        cout << "Recognized gesture: " << rp.name << endl;
//        cout << "Cosine Score:" << rp.score << endl;


        return true;
    }
    return false;
}

void Knife::loadTemplatesWithNames(const char* firstTemplate, ...)
{
    va_list args;
    va_start(args, firstTemplate);
    for (const char *glyphName = firstTemplate; glyphName != NULL; glyphName = va_arg(args, const char*))
    {
//        if (![glyphName isKindOfClass:[NSString class]])
//            continue;
        glyphNamesArray.push_back(glyphName);

        std::string jsonData = FileUtils::getInstance()->getStringFromFile(String::createWithFormat("%s.json",glyphName)->getCString());
        //log("%s",String::createWithFormat("%s.json",glyphName)->getCString());
        glyphDetector->addGlyphFromJSON(jsonData.c_str() ,glyphName);

    }
    va_end(args);
}

std::string Knife::getGlyphNamesString()
{
    if (glyphNamesArray.size() <= 0)
        return "";
    std::string res = "";
    for (int i = 0; i < glyphNamesArray.size(); i++) {
        res += glyphNamesArray.at(i)+",";
    }
    return res;
}

void Knife::glyphDetected(WTMGlyph *glyph, float score)
{
    //Simply forward it to my parent,show result
//    if ([self.delegate respondsToSelector:@selector(wtmGlyphDetectorView:glyphDetected:withScore:)])
//        [self.delegate wtmGlyphDetectorView:self glyphDetected:glyph withScore:score];
    {
        if (score < GESTURE_SCORE_THRESHOLD)
            return;
        
        std::string glyphNames = getGlyphNamesString();
        if (glyphNames.length() > 0){
            log("Loaded with %s templates.\n\n",glyphNames.c_str());
        }
        
        log("Last gesture detected: %s\nScore: %.3f",glyph->name.c_str(), score);
    }
    
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(Knife::clearDrawingIfTimeout,this));
    this->runAction(Sequence::create(DelayTime::create(1.0f),func, NULL));
}

void Knife::clearDrawingIfTimeout(){
//    if (!enableDrawing)
//        return;
//    
    bool hasTimeOut = glyphDetector->hasTimedOut();
    if (!hasTimeOut)
        return;
//
//    [self.myPath removeAllPoints];
//    
//    //This is not recommended for production, but it's ok here since we don't have a lot to draw
//    [self setNeedsDisplay];
}

void Knife::glyphResults(Array* results)
{
    //Raw results from the library?
    //Not sure what this delegate function is for, undocumented
}

//all subclasses can communicate using messages.
bool Knife::handleMessage(const Telegram& msg)
{
    return false;
}

//all entities must implement an update function
void Knife::update(float dt)
{
    if (touchedForXuLi) {
        double currentTime = millisecondNow();
        if (currentTime >= currentTouchTime + 300) {
            //进入蓄力状态
            xuliing = true;
            xuliLayer->setVisible(true);
            xuliTimePast = 0;
            xuliBar->setPosition(startTouchPosition);
            touchedForXuLi = false;
        }
    }
    if (xuliing) {
        //isXuliDamage = true;
        xuliTimePast += dt*1000;
        double percentage = xuliTimePast / xuliTotalTime;
        if (percentage >= 1) {
            percentage = 1;
            isXuliDamage = true;
        }
        xuliBar->setPercentage(percentage*100);
        origDamage = 10;
        damage = origDamage * (1+percentage);
    }
}

//bool Knife::isXuliStateDamage()
//{
//    return isXuliDamage;
//}

//bool Knife::onTouchBegan(Touch* touch, Event* event)
//{
//    Weapon::m_attackID++;
//    CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
//    //log("Knife::onTouchBegan");
//    Vec2 pos = touch->getLocation();
//    //this->getChildByTag(111)->setPosition(Vec2(t->getLocation().x,t->getLocation().y));
//    lastHitCharacter = nullptr;
//    isXuliDamage = false;
//    streak->setPosition(pos);
//    
//    streak->reset();
//    startTouchPosition = pos;
//    touchedForXuLi = true;
//    currentTouchTime = millisecondNow();
//    hitDistance = 301;
////    path.push_back(Point2D(pos.x,pos.y));
//    
//    
//    //gesture
//    //This is basically the content of resetIfTimeout
//    bool hasTimeOut = glyphDetector->hasTimedOut();
//    if (hasTimeOut) {
//        log("Gesture detector reset");
//        glyphDetector->reset();
//        
////        if (self.enableDrawing) {
////            [self.myPath removeAllPoints];
////            //This is not recommended for production, but it's ok here since we don't have a lot to draw
////            [self setNeedsDisplay];
////        }
//    }
//    Size size = Director::getInstance()->getWinSize();
//    glyphDetector->addPoint(PointObject::create(pos.x, size.height-pos.y));
//    
////    glyphDetector->addPoint(PointObject::create(125, 378));
////glyphDetector->addPoint(PointObject::create(129, 382));
////glyphDetector->addPoint(PointObject::create(131, 392));
////glyphDetector->addPoint(PointObject::create(135, 403));
////glyphDetector->addPoint(PointObject::create(139, 416));
////glyphDetector->addPoint(PointObject::create(143, 429));
////glyphDetector->addPoint(PointObject::create(145, 439));
////glyphDetector->addPoint(PointObject::create(147, 450));
////glyphDetector->addPoint(PointObject::create(151, 469));
////glyphDetector->addPoint(PointObject::create(153, 476));
////glyphDetector->addPoint(PointObject::create(154, 480));
////glyphDetector->addPoint(PointObject::create(155, 482));
////glyphDetector->addPoint(PointObject::create(156, 482));
////glyphDetector->addPoint(PointObject::create(156, 483));
////glyphDetector->addPoint(PointObject::create(157, 483));
////glyphDetector->addPoint(PointObject::create(157, 480));
////    glyphDetector->addPoint(PointObject::create(159, 470));
////glyphDetector->addPoint(PointObject::create(163, 457));
////glyphDetector->addPoint(PointObject::create(169, 439));
////glyphDetector->addPoint(PointObject::create(174, 422));
////glyphDetector->addPoint(PointObject::create(180, 406));
////glyphDetector->addPoint(PointObject::create(184, 395));
////glyphDetector->addPoint(PointObject::create(187, 388));
////glyphDetector->addPoint(PointObject::create(188, 384));
////glyphDetector->addPoint(PointObject::create(189, 381));
////glyphDetector->addPoint(PointObject::create(190, 380));
////glyphDetector->addPoint(PointObject::create(190, 378));
////glyphDetector->addPoint(PointObject::create(190, 372));
////glyphDetector->detectGlyph();
//    return true;
//}
//
//void Knife::onTouchMoved(Touch* touch, Event* event)
//{
//    //log("Knife::onTouchMoved");
//    // If it weren't for the TouchDispatcher, you would need to keep a reference
//    // to the touch from touchBegan and check that the current touch is the same
//    // as that one.
//    // Actually, it would be even more complicated since in the Cocos dispatcher
//    // you get Sets instead of 1 UITouch, so you'd need to loop through the set
//    // in each touchXXX method.
//    
//    //CCLOG("Paddle::onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
//
//    Vec2 delta = touch->getDelta();
//    Vec2 lastPos = touch->getPreviousLocation();
//    Vec2 pos = touch->getLocation();
////    path.push_back(Point2D(pos.x,pos.y));
//    
//    Size size = Director::getInstance()->getWinSize();
//    glyphDetector->addPoint(PointObject::create(pos.x, size.height-pos.y));
//    
//    float ddx = pos.x - lastPos.x;
//    float ddy = pos.y - lastPos.y;
//    float moveDistance = sqrtf(ddx*ddx+ddy*ddy);
//    //log("moveDistance:%f",moveDistance);
//    //float moveDistance = pos.distance(lastPos);
//    
//    float dx = pos.x - startTouchPosition.x;
//    float dy = pos.y - startTouchPosition.y;
//    float dist = sqrtf(dx*dx+dy*dy);
//    
//    
//    //    star->setPosition(star->getPosition() + delta);
//    //    streak->setPosition(star->getPosition());
//    AppDelegate *app = (AppDelegate*)Application::getInstance();
//    float scaleFactory = app->scaleFactory;
//    if (dist > 100*scaleFactory){
//        touchedForXuLi = false;
//    }
//    if (xuliing){
//        xuliBar->setPosition(pos);
//    }
//    
////    if (xuliing) {
////        float xulibarradius = 300 * scaleFactory;
////
////        if (dist > xulibarradius) {
////            //如果手指出了蓄力槽范围
////            xuliing = false;
////            xuliLayer->setVisible(false);
////        }
////    }
//
//    
//    
//    streak->setPosition(pos);
//    //刀的判断
////    dist = pos.distance(startTouchPosition);
//
//    //if (dist > 50) {
//        dx = pos.x - lastPos.x;
//        dy = pos.y - lastPos.y;
//        float angle2 = atan2f(dy, dx)*180/M_PI;
//        //log("angle1:%f,angle2:%f",angle1,angle2);
//        
//        KnifeAttackDirection direction;
//        
//        if(angle2 <= 135 && angle2 >= 45){
//            //往上划
//            direction = KnifeAttackDirectionUp;
//        }else if(angle2 <= -45 && angle2 >= -135){
//            //往下划
//            direction = KnifeAttackDirectionDown;
//        }else if (angle2 <= 45 && angle2 >= -45) {
//            //往右划
//            direction = KnifeAttackDirectionRight;
//        }else{
//            //往左划
//            direction = KnifeAttackDirectionLeft;
//        }
//        
//        //hit test monster
//        for (Character *agent : world->getMonsters()) {
//            if (!agent->isVisible() || agent->isDieState()) {
//                continue;
//            }
//            bool hit = agent->hittestPoint(pos);
//            if (hit) {
//                //log("hit:%d",agent->getID());
//                //startTouchPosition = pos;
//                if (agent != lastHitCharacter) {
//                    hitDistance = 301;
//                }else{
//                    hitDistance+=moveDistance;
//                }
//                
//                lastHitCharacter = agent;
//                if (hitDistance > 300) {
//                    hitDistance = 0;
//                    //log("damage hit:%d,%f",agent->getID(),moveDistance);
//                    if (isXuliDamage) {
//                        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
//                                                                          getID(),           //sender ID
//                                                                          agent->getID(),           //receiver ID
//                                                                          Msg_AttackedByXuLiWeapon,        //msg
//                                                                          &direction);
//                    }else{
//                        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
//                                                                          getID(),           //sender ID
//                                                                          agent->getID(),           //receiver ID
//                                                                          Msg_AttackedByWeapon,        //msg
//                                                                          &direction);
//                    }
//                    
//                    if (xuliing) {
//                        xuliing = false;
//                        xuliLayer->setVisible(false);
//                    }
//                    isXuliDamage = false;
//                    
//                }
//                return;
//            }
//        }
//    //}
//    //如果没有碰到任何怪
//    lastHitCharacter = nullptr;
//    hitDistance = 301;
//    //log("not hit");
//}
//
//void Knife::onTouchEnded(Touch* touch, Event* event)
//{
//    Vec2 delta = touch->getDelta();
//    touchedForXuLi = false;
//    xuliing = false;
//    xuliLayer->setVisible(false);
//    damage = origDamage;
//    isXuliDamage = false;
//    //    star->setPosition(star->getPosition() + delta);
//    //    streak->setPosition(star->getPosition());
//    
//    Vec2 pos = touch->getLocation();
////    path.push_back(Point2D(pos.x,pos.y));
//    
//    
//    Size size = Director::getInstance()->getWinSize();
//    glyphDetector->addPoint(PointObject::create(pos.x, size.height-pos.y));
//    glyphDetector->detectGlyph();
//    
//    streak->setPosition(pos);
//    
//    float dx = pos.x - startTouchPosition.x;
//    float dy = pos.y - startTouchPosition.y;
//    float dist = sqrtf(dx*dx+dy*dy);
//    if(dist > 100){
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
//    }
//    
////    cout<< "Results" <<endl;
////    RecognitionResult rpm=gm.Multirecognize(getGestureP(),"normal");
////    cout << "$N Recognized gesture: " << rpm.name << endl;
////    cout << "$N Score:" << rpm.score << endl;
//}
//
//void Knife::onTouchCancelled(Touch *touch, Event *unused_event)
//{
//    touchedForXuLi = false;
//    xuliing = false;
//    xuliLayer->setVisible(false);
//    damage = origDamage;
//    isXuliDamage = false;
//    
//    Vec2 pos = touch->getLocation();
//}


void Knife::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch *touch = touches.at(0);
    Weapon::m_attackID++;
    CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    //log("Knife::onTouchBegan");
    Vec2 pos = touch->getLocation();
    //this->getChildByTag(111)->setPosition(Vec2(t->getLocation().x,t->getLocation().y));
    lastHitCharacter = nullptr;
    isXuliDamage = false;
    streak->setPosition(pos);
    
    streak->reset();
    startTouchPosition = pos;
    touchedForXuLi = true;
    currentTouchTime = millisecondNow();
    hitDistance = 301;
    //    path.push_back(Point2D(pos.x,pos.y));
    
    
    //gesture
    //This is basically the content of resetIfTimeout
    bool hasTimeOut = glyphDetector->hasTimedOut();
    if (hasTimeOut) {
        log("Gesture detector reset");
        glyphDetector->reset();
        
        //        if (self.enableDrawing) {
        //            [self.myPath removeAllPoints];
        //            //This is not recommended for production, but it's ok here since we don't have a lot to draw
        //            [self setNeedsDisplay];
        //        }
    }
    Size size = Director::getInstance()->getWinSize();
    glyphDetector->addPoint(PointObject::create(pos.x, size.height-pos.y));
    
    //    glyphDetector->addPoint(PointObject::create(125, 378));
    //glyphDetector->addPoint(PointObject::create(129, 382));
    //glyphDetector->addPoint(PointObject::create(131, 392));
    //glyphDetector->addPoint(PointObject::create(135, 403));
    //glyphDetector->addPoint(PointObject::create(139, 416));
    //glyphDetector->addPoint(PointObject::create(143, 429));
    //glyphDetector->addPoint(PointObject::create(145, 439));
    //glyphDetector->addPoint(PointObject::create(147, 450));
    //glyphDetector->addPoint(PointObject::create(151, 469));
    //glyphDetector->addPoint(PointObject::create(153, 476));
    //glyphDetector->addPoint(PointObject::create(154, 480));
    //glyphDetector->addPoint(PointObject::create(155, 482));
    //glyphDetector->addPoint(PointObject::create(156, 482));
    //glyphDetector->addPoint(PointObject::create(156, 483));
    //glyphDetector->addPoint(PointObject::create(157, 483));
    //glyphDetector->addPoint(PointObject::create(157, 480));
    //    glyphDetector->addPoint(PointObject::create(159, 470));
    //glyphDetector->addPoint(PointObject::create(163, 457));
    //glyphDetector->addPoint(PointObject::create(169, 439));
    //glyphDetector->addPoint(PointObject::create(174, 422));
    //glyphDetector->addPoint(PointObject::create(180, 406));
    //glyphDetector->addPoint(PointObject::create(184, 395));
    //glyphDetector->addPoint(PointObject::create(187, 388));
    //glyphDetector->addPoint(PointObject::create(188, 384));
    //glyphDetector->addPoint(PointObject::create(189, 381));
    //glyphDetector->addPoint(PointObject::create(190, 380));
    //glyphDetector->addPoint(PointObject::create(190, 378));
    //glyphDetector->addPoint(PointObject::create(190, 372));
    //glyphDetector->detectGlyph();
}

void Knife::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch *touch = touches.at(0);
    //log("Knife::onTouchMoved");
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get Sets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
    
    //CCLOG("Paddle::onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    Vec2 delta = touch->getDelta();
    Vec2 lastPos = touch->getPreviousLocation();
    Vec2 pos = touch->getLocation();
    //    path.push_back(Point2D(pos.x,pos.y));
    
    Size size = Director::getInstance()->getWinSize();
    glyphDetector->addPoint(PointObject::create(pos.x, size.height-pos.y));
    
    float ddx = pos.x - lastPos.x;
    float ddy = pos.y - lastPos.y;
    float moveDistance = sqrtf(ddx*ddx+ddy*ddy);
    //log("moveDistance:%f",moveDistance);
    //float moveDistance = pos.distance(lastPos);
    
    float dx = pos.x - startTouchPosition.x;
    float dy = pos.y - startTouchPosition.y;
    float dist = sqrtf(dx*dx+dy*dy);
    
    
    //    star->setPosition(star->getPosition() + delta);
    //    streak->setPosition(star->getPosition());
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    if (dist > 100*scaleFactory){
        touchedForXuLi = false;
    }
    if (xuliing){
        xuliBar->setPosition(pos);
    }
    
    //    if (xuliing) {
    //        float xulibarradius = 300 * scaleFactory;
    //
    //        if (dist > xulibarradius) {
    //            //如果手指出了蓄力槽范围
    //            xuliing = false;
    //            xuliLayer->setVisible(false);
    //        }
    //    }
    
    
    
    streak->setPosition(pos);
    //刀的判断
    //    dist = pos.distance(startTouchPosition);
    
    //if (dist > 50) {
    dx = pos.x - lastPos.x;
    dy = pos.y - lastPos.y;
    float angle2 = atan2f(dy, dx)*180/M_PI;
    //log("angle1:%f,angle2:%f",angle1,angle2);
    
    KnifeAttackDirection direction;
    
    if(angle2 <= 135 && angle2 >= 45){
        //往上划
        direction = KnifeAttackDirectionUp;
    }else if(angle2 <= -45 && angle2 >= -135){
        //往下划
        direction = KnifeAttackDirectionDown;
    }else if (angle2 <= 45 && angle2 >= -45) {
        //往右划
        direction = KnifeAttackDirectionRight;
    }else{
        //往左划
        direction = KnifeAttackDirectionLeft;
    }
    
    //hit test monster
    for (Character *agent : world->getMonsters()) {
        if (!agent->isVisible() || agent->isDieState()) {
            continue;
        }
        bool hit = agent->hittestPoint(pos);
        if (hit) {
            //log("hit:%d",agent->getID());
            //startTouchPosition = pos;
            if (agent != lastHitCharacter) {
                hitDistance = 301;
            }else{
                hitDistance+=moveDistance;
            }
            
            lastHitCharacter = agent;
            if (hitDistance > 300) {
                hitDistance = 0;
                //log("damage hit:%d,%f",agent->getID(),moveDistance);
                if (isXuliDamage) {
                    MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                                      getID(),           //sender ID
                                                                      agent->getID(),           //receiver ID
                                                                      Msg_AttackedByXuLiWeapon,        //msg
                                                                      &direction);
                }else{
                    MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                                      getID(),           //sender ID
                                                                      agent->getID(),           //receiver ID
                                                                      Msg_AttackedByWeapon,        //msg
                                                                      &direction);
                }
                
                if (xuliing) {
                    xuliing = false;
                    xuliLayer->setVisible(false);
                }
                isXuliDamage = false;
                
            }
            return;
        }
    }
    //}
    //如果没有碰到任何怪
    lastHitCharacter = nullptr;
    hitDistance = 301;
    //log("not hit");
}

void Knife::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    Touch *touch = touches.at(0);
    Vec2 delta = touch->getDelta();
    touchedForXuLi = false;
    xuliing = false;
    xuliLayer->setVisible(false);
    damage = origDamage;
    isXuliDamage = false;
    //    star->setPosition(star->getPosition() + delta);
    //    streak->setPosition(star->getPosition());
    
    Vec2 pos = touch->getLocation();
    //    path.push_back(Point2D(pos.x,pos.y));
    
    
    Size size = Director::getInstance()->getWinSize();
    glyphDetector->addPoint(PointObject::create(pos.x, size.height-pos.y));
    glyphDetector->detectGlyph();
    
    streak->setPosition(pos);
    
    float dx = pos.x - startTouchPosition.x;
    float dy = pos.y - startTouchPosition.y;
    float dist = sqrtf(dx*dx+dy*dy);
    if(dist > 100){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
    }
}

void Knife::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
    Touch *touch = touches.at(0);
    touchedForXuLi = false;
    xuliing = false;
    xuliLayer->setVisible(false);
    damage = origDamage;
    isXuliDamage = false;
    
    Vec2 pos = touch->getLocation();
}

bool Knife::hittestPoint(Vec2 p)
{
    return false;
}
