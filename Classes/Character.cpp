//
//  Character.cpp
//  BGT
//
//  Created by John Running on 15/3/4.
//
//

#include "Character.h"
#include "AppDelegate.h"
#include "BGTWall.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include <SimpleAudioEngine.h>


Character::Character()
:skeletonNode(NULL)
,floor(0)
,paused(false)
,currentTimeScale(1)
,characterScaleFactor(1)
,showLifeBarTime(0)
,monsterData(nullptr)
,hitPolygon(nullptr)
,hitRectNode(nullptr)
,lastAttackedId(-1)
{

}

Character::~Character()
{
    m_pStateMachine->release();
    standState->release();
    attackState->release();
    fallDownState->release();
    dizzyState->release();
    standUpState->release();
    stiffState->release();
    rollBackState->release();
    dieState->release();
    moveState->release();
    lieDownState->release();
    flowState->release();
    defenseState->release();
    skillState->release();
    if (monsterData) {
        monsterData->release();
    }
    
    CC_SAFE_DELETE_ARRAY(hitPolygon);
}

bool Character::initWithWorldAndType(BGTWorld *w,CharacterType t)
{
    if (!GameEntity::initWithWorld(w)) {
        return false;
    }
    characterScaleFactor = 1;
    lastAttackedId = -1;
    currentTimeScale = 1;
    lifeBar = Sprite::createWithSpriteFrameName("lifeBarFrame.png");
    lifeBar->setPosition(0,0);
    addChild(lifeBar);
    lifeBar->setVisible(false);
    
    progressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifeBar.png"));
    
    progressBar->setType(ProgressTimer::Type::BAR);
    progressBar->setMidpoint(Vec2(0,1));
    progressBar->setBarChangeRate(Vec2(1, 0));
    progressBar->setPercentage(100);
    progressBar->setPosition(lifeBar->getContentSize().width/2,lifeBar->getContentSize().height/2);
    lifeBar->addChild(progressBar);
    

    dispatcher = MessageDispatcher::getInstance();
    //set up state machine
    m_pStateMachine = new StateMachine<Character>(this);
    
    standState = new StandState();
    attackState = new AttackState();
    fallDownState = new FallDownState();
    dizzyState = new DizzyState();
    standUpState = new StandUpState();
    stiffState = new StiffState();
    rollBackState = new RollBackState();
    dieState = new DieState();
    moveState = new MoveState();
    lieDownState = new LieDownState();
    flowState = new FlowState();
    defenseState = new DefenseState();
    skillState = new SkillState();
    
    
    hitRectNode = DrawNode::create();
    addChild(hitRectNode,100000);
    
    
    wall = world->getWall();
    setType(t);
    reset();
    
    
    for (int i = 0; i < 3; i++) {
        Label *label = Label::createWithBMFont("gameSceneKouLifeLabel.fnt", "-0");
        addChild(label);
        label->setVisible(false);
        damageLabels.pushBack(label);
        
        label = Label::createWithBMFont("gameSceneBaoJiLabel.fnt", "暴击\n0");
        addChild(label);
        label->setVisible(false);
        baoDamageLabels.pushBack(label);
        
        label = Label::createWithBMFont("gameSceneMissLabel.fnt", "Miss!");
        addChild(label);
        label->setVisible(false);
        missLabels.pushBack(label);
    }
    particleSystem = ParticleSystemQuad::create("blood.plist");
    addChild(particleSystem,1);
    return true;
}

bool Character::isSkilled()
{
    return skilled;
}

void Character::skill(){
    skilled = true;
    m_pStateMachine->changeState(skillState);
}

Label* Character::getMissLabelFromPool()
{
    for (int i = 0; i < missLabels.size(); i++) {
        Label *label = missLabels.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Label *label = Label::createWithBMFont("gameSceneMissLabel.fnt", "Miss!");
    addChild(label);
    label->setVisible(false);
    missLabels.pushBack(label);
    return label;
}

Label* Character::getDamageLabelFromPool()
{
    for (int i = 0; i < damageLabels.size(); i++) {
        Label *label = damageLabels.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Label *label = Label::createWithBMFont("gameSceneKouLifeLabel.fnt", "-0");
    addChild(label);
    label->setVisible(false);
    damageLabels.pushBack(label);
    return label;
}

Label* Character::getBaoDamageLabelFromPool()
{
    for (int i = 0; i < baoDamageLabels.size(); i++) {
        Label *label = baoDamageLabels.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Label *label = Label::createWithBMFont("gameSceneBaoJiLabel.fnt", "暴击\n0");
    addChild(label);
    label->setVisible(false);
    baoDamageLabels.pushBack(label);
    return label;
}

float Character::getFloor()
{
    return floor;
}

void Character::setFloor(float f)
{
    floor = f;
}

void Character::falldown()
{
    m_pStateMachine->changeState(fallDownState);
}

void Character::standup()
{
    m_pStateMachine->changeState(standUpState);
}

void Character::move()
{
    m_pStateMachine->changeState(moveState);
}

//for animation
//void Character::playAnimation(int trackIndex, const char* animationName,bool loop)
//{
//    skeletonNode->setToSetupPose();
//    skeletonNode->setBonesToSetupPose();
//    skeletonNode->setSlotsToSetupPose();
//    skeletonNode->setAnimation(trackIndex, animationName, loop);
//}

float Character::getCharacterScaleFactor()
{
    return characterScaleFactor;
}

Rect Character::getBoundingBox()
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    Rect rect = skeletonNode->getBoundingBox();
    return Rect(getPositionX()+rect.origin.x*scaleFactory*characterScaleFactor, getPositionY()+rect.origin.y*scaleFactory*characterScaleFactor, rect.size.width*scaleFactory*characterScaleFactor, rect.size.height*scaleFactory*characterScaleFactor);
}

spBoundingBoxAttachment* Character::getHittestPolygon()
{
    spAttachment *boundingBox = skeletonNode->getAttachment("hitBox", "hitBox");
    spBoundingBoxAttachment *ba = (spBoundingBoxAttachment*)boundingBox;
    return ba;
//    AppDelegate *app = (AppDelegate*)Application::getInstance();
//    float scaleFactory = app->scaleFactory;
//    float minX=99999;
//    float minY=99999;
//    float maxX = -99999;
//    float maxY = -99999;
//    
//    for(int i = 0;i < ba->verticesCount; i+=2){
//        if (i % 2==0) {
//            float x = ba->vertices[i];
//            float y = ba->vertices[i+1];
//            if (x <= minX) {
//                minX = x;
//            }
//            if (y <= minY) {
//                minY = y;
//            }
//            if (x >= maxX){
//                maxX = x;
//            }
//            if (y >= maxY) {
//                maxY = y;
//            }
//        }
//    }
//    log("scaleFactory:%f,characterScaleFactor:%f",scaleFactory,characterScaleFactor);
//    
//    return Rect(getPositionX()+minX*scaleFactory*characterScaleFactor, getPositionY()+minY*scaleFactory*characterScaleFactor, (maxX-minX)*scaleFactory*characterScaleFactor, (maxY-minY)*scaleFactory*characterScaleFactor);
    
    
    
//    Rect rect = skeletonNode->getBoundingBox();
//    return Rect(getPositionX()+rect.origin.x, getPositionY()+rect.origin.y, rect.size.width, rect.size.height);
    
    
//    //hitRectNode->drawRect(rect.origin, Vec2(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height), Color4F(0, 1, 0, 1));
//    //log("getRect");
//    if (m_pStateMachine->isInState(*lieDownState)||m_pStateMachine->isInState(*flowState)||m_pStateMachine->isInState(*injureState)||m_pStateMachine->isInState(*dieState)) {
//        float soldierWidth = monsterData->hitRect.size.width;
//        float soldierHeight = monsterData->hitRect.size.height;
//        return Rect(getPositionX(), getPositionY()-soldierWidth/2, soldierHeight, soldierWidth);
////        Rect rect = Rect(getPositionX()+monsterData->hitRect.origin.x, getPositionY()+monsterData->hitRect.origin.y, getPositionY()+monsterData->hitRect.size.width, getPositionY()+monsterData->hitRect.size.height);
//
////        hitRectNode->drawRect(monsterData->hitRect.origin, Vec2(monsterData->hitRect.origin.x+monsterData->hitRect.size.width,monsterData->hitRect.origin.y+monsterData->hitRect.size.height), Color4F(0, 1, 0, 1));
////
////        return rect;
//    }else{
//        //return Rect(getPositionX()-soldierWidth/2, getPositionY(), soldierWidth, soldierHeight);
//        Rect rect = Rect(getPositionX()+monsterData->hitRect.origin.x, getPositionY()+monsterData->hitRect.origin.y, getPositionY()+monsterData->hitRect.size.width, getPositionY()+monsterData->hitRect.size.height);
//
//        //hitRectNode->drawRect(monsterData->hitRect.origin, Vec2(monsterData->hitRect.origin.x+monsterData->hitRect.size.width,monsterData->hitRect.origin.y+monsterData->hitRect.size.height), Color4F(0, 1, 0, 1));
//
//        return rect;
//    }
}

SkeletonAnimation* Character::getSkeletonNode()
{
    return skeletonNode;
}

//是否是飞行怪物
bool Character::isCanFly()
{
    return canfly;
}

void Character::reset()
{
    paused = false;
    canfly = false;
    defensed = false;
    lifeTime = 0;
    characterScaleFactor = 1;
    lastAttackedId = -1;
    currentTimeScale = 1;
    if(skeletonNode){
        skeletonNode->setTimeScale(currentTimeScale);
    }
    setDirection(CharacterDirectionLeft);
    life = monsterData->life;
    progressBar->setPercentage(100 *(life/(float)monsterData->life));
    lifeBar->setVisible(false);
    skillBeginTime = 15 + CCRANDOM_0_1()*25;
    m_pStateMachine->setCurrentState(standState);
    m_pStateMachine->changeState(standState);
//    CallFunc *func = CallFunc::create([=](){
//        m_pStateMachine->setCurrentState(standState);
//        m_pStateMachine->changeState(standState);
//    });
//    this->runAction(Sequence::create(DelayTime::create(CCRANDOM_0_1()*0.1),func, NULL));
}

void Character::hitted(){
    EventCustom event("MonsterHitted");
    event.setUserData(this);
    _eventDispatcher->dispatchEvent(&event);
}

bool Character::handleMessage(const Telegram& msg)
{
    if (paused) {
        return false;
    }
    return m_pStateMachine->handleMessage(msg);
}

bool Character::canSkill(){
    return lifeTime >= skillBeginTime && !skilled;
}

void Character::update(float dt)
{
    if (!paused) {
        showLifeBarTime -= dt;
        lifeTime += dt;
        if (showLifeBarTime<0) {
            showLifeBarTime = 0;
        }
        m_pStateMachine->update(dt);
        lifeBar->setVisible(showLifeBarTime>0);
    }
}

StateMachine<Character>* Character::getFSM()
{
    return m_pStateMachine;
}

bool Character::isDefenseState()
{
    return m_pStateMachine->isInState(*defenseState);
}

bool Character::isFlowState()
{
    return m_pStateMachine->isInState(*flowState);
}

bool Character::isStandState()
{
    return m_pStateMachine->isInState(*standState);
}

bool Character::isMoveState()
{
    return m_pStateMachine->isInState(*moveState);
}

bool Character::isAttackState()
{
    return m_pStateMachine->isInState(*attackState);
}

bool Character::isFallDownState()
{
    return m_pStateMachine->isInState(*fallDownState);
}

bool Character::isDizzyState()
{
    return m_pStateMachine->isInState(*dizzyState);
}

bool Character::isStandUpState()
{
    return m_pStateMachine->isInState(*standUpState);
}

bool Character::isStiffState()
{
    return m_pStateMachine->isInState(*stiffState);
}

bool Character::isRollBackState()
{
    return m_pStateMachine->isInState(*rollBackState);
}

bool Character::isLieDownState()
{
    return m_pStateMachine->isInState(*lieDownState);
}

bool Character::isDieState()
{
    return m_pStateMachine->isInState(*dieState);
}

bool Character::canDefense()
{
    return !defensed && monsterData->canQTE;
}

void Character::defense()
{
    defensed = true;
    m_pStateMachine->changeState(defenseState);
}

void Character::parry()
{
    EventCustom event("MonsterParry");
    event.setUserData(this);
    getEventDispatcher()->dispatchEvent(&event);
}

void Character::dizzy()
{
    m_pStateMachine->changeState(dizzyState);
}

void Character::die(){
    world->monsterDied(this);
    m_pStateMachine->changeState(dieState);
}

void Character::liedown()
{
    m_pStateMachine->changeState(lieDownState);
}

void Character::stiff()
{
    m_pStateMachine->changeState(stiffState);
}

void Character::attack()
{
    m_pStateMachine->changeState(attackState);
}

void Character::flowup()
{
    m_pStateMachine->changeState(flowState);
}

void Character::rollback()
{
    m_pStateMachine->changeState(rollBackState);
}

void Character::shanbi()
{
    EventCustom event("MonsterShanbi");
    event.setUserData(this);
    getEventDispatcher()->dispatchEvent(&event);
}

void Character::takeDamage(float value,Vec2 pos,bool isBaoJi)
{
    if (life <= 0 || value <= 0) {
        return;
    }
    showLifeBarTime += 1.5;
    if(showLifeBarTime>1.5)
        showLifeBarTime = 1.5;
    life -= value;
    if (life <= 0) {
        life = 0;
        lifeBar->setVisible(false);
    }else{
        lifeBar->setVisible(true);
    }
    progressBar->setPercentage(100 *(life/(float)monsterData->life));
//    if(life <= 0){
//        m_pStateMachine->changeState(dieState);
//    }
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
    CustomerUserData userData;
    userData.monster = this;
    userData.damage = value;
    
    if (isBaoJi) {
        EventCustom event("MonsterBaoDamaged");
        event.setUserData(&userData);
        _eventDispatcher->dispatchEvent(&event);
    }else{
        EventCustom event("MonsterDamaged");
        event.setUserData(&userData);
        _eventDispatcher->dispatchEvent(&event);
    }

    particleSystem->setPosition(pos);
    
    particleSystem->setPositionType(ParticleSystem::PositionType::GROUPED);
    
}

void Character::pause()
{
    currentTimeScale = skeletonNode->getTimeScale();
    skeletonNode->setTimeScale(0);
    paused = true;
}

void Character::resume()
{
    skeletonNode->setTimeScale(currentTimeScale);
    paused = false;
}

void Character::setDirection(CharacterDirection d)
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    direction = d;

//    if (getType() <= 2) {
//        characterScaleFactor = 0.22;
//    }else if(getType() == 3){
//        characterScaleFactor = 0.25;
//    }
    switch (direction) {
            //        case kUp:
            //            self.rotation = -90;
            //            break;
            //        case kDown:
            //            self.rotation = 90;
            //            break;
        case CharacterDirectionLeft:
            skeletonNode->setScaleX(1*scaleFactory*characterScaleFactor);
            break;
        case CharacterDirectionRight:
            skeletonNode->setScaleX(-1*scaleFactory*characterScaleFactor);
            break;
        default:
            break;
    }
}

CharacterDirection Character::getDirection()
{
    return direction;
}

void Character::setState(State<Character>* d)
{
    m_pStateMachine->changeState(d);
}

State<Character>* Character::getState()
{
    return m_pStateMachine->currentState();
}

bool Character::hittestPoint(Vec2 p)
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 pos = this->convertToNodeSpace(p);

//    spBone *bodybone = skeletonNode->findBone("body");
//    spAttachment *ata = skeletonNode->getAttachment("hitBox", "hitBox");
//    spBoundingBoxAttachment *boundingAttachment = (spBoundingBoxAttachment*)ata;
//
//    spPolygon *boundingPolygon = spPolygon_create(boundingAttachment->verticesCount);
//    for (int i = 0; i<boundingAttachment->verticesCount; i++) {
//        boundingPolygon->vertices[i]=boundingAttachment->vertices[i];
//        boundingPolygon->count+=1;
//    }
//    spBoundingBoxAttachment_computeWorldVertices(boundingAttachment, bodybone, boundingPolygon->vertices);
//    
//    for (int i = 0; i<boundingPolygon->count; i++) {
//        boundingPolygon->vertices[i]=boundingPolygon->vertices[i]*scaleFactory*characterScaleFactor;
//    }
//    
//    bool clicked = spPolygon_containsPoint(boundingPolygon, pos.x, pos.y);
////    if(clicked){
////        int pCount = boundingPolygon->count/2;
////        CC_SAFE_DELETE_ARRAY(hitPolygon);
////        hitPolygon = new Vec2[pCount];
////        for (int i = 0; i < pCount; i++) {
////            hitPolygon[i] = Vec2(boundingPolygon->vertices[i*2],boundingPolygon->vertices[i*2+1]);
////        }
////        hitRectNode->drawPolygon(hitPolygon, pCount, Color4F(0, 255, 0, 255), 2, Color4F(0, 255, 0, 150));
////    }
//    spPolygon_dispose(boundingPolygon);
//    return clicked;
    


    bool hit = false;
    spSkeletonBounds* bounds = spSkeletonBounds_create();
    spSkeletonBounds_update(bounds, skeletonNode->getSkeleton(), true);
    spBoundingBoxAttachment *ba = spSkeletonBounds_containsPoint(bounds, pos.x, pos.y);
    if (ba) {
        hit = true;
    }
    //spSkeletonData_dispose(skeletonData);
    spSkeletonBounds_dispose(bounds);
    //spAtlas_dispose(atlas);
    return hit;
}

void Character::setType(CharacterType d)
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    if(skeletonNode){
        skeletonNode->removeFromParent();
        skeletonNode = NULL;
    }
    if (monsterData) {
        monsterData->release();
    }
    monsterData = WaveManager::getInstance()->getMonsterDataByType(d);
//#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid monster type: %d", d);
    CCASSERT(monsterData != NULL, msg);
//#endif
    char name[256] = {0};
    sprintf(name, "monster%d.atlas", d);
    spAtlas* atlas = spAtlas_createFromFile(name, 0);
    char name1[256] = {0};
    sprintf(name1, "monster%d.json", d);
    skeletonNode = SkeletonAnimation::createWithFile(name1, atlas);
    skeletonNode->setPosition(0, 0);

//    if (d <= 2) {
//        characterScaleFactor = 0.22;
//    }else if(d == 3){
//        characterScaleFactor = 0.25;
//    }
    skeletonNode->setScale(1.0*scaleFactory*characterScaleFactor);
    addChild(skeletonNode);
    

//    spAttachment *lifeBarBox = skeletonNode->getAttachment("lifeBar", "lifeBar");
//    spBoundingBoxAttachment *ba = (spBoundingBoxAttachment*)lifeBarBox;
//    lifeBar->setPositionY(ba->vertices[1]*scaleFactory*characterScaleFactor);
    spBone *rootbone = skeletonNode->findBone("root");
    spBone *bone = skeletonNode->findBone("lifeBar");
    lifeBar->setPositionY(bone->y*rootbone->scaleX*scaleFactory*characterScaleFactor);
    log("rootbone->scaleX:%f,bone->y:%f,bone->worldY:%f",rootbone->scaleX,bone->y,bone->worldY);

    
    //skeletonNode->setDebugBonesEnabled(true);

    
    
//    skeletonNode->setAnimationListener(this, animationStateEvent_selector(Character::animationStateEvent));
    
//    skeletonNode->setStartListener( [this] (int trackIndex) {
//        spTrackEntry* entry = spAnimationState_getCurrent(skeletonNode->getState(), trackIndex);
//        const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
//        
//        if (m_pStateMachine->isInState(*attackState)) {
//            log("%d start: %s", trackIndex, animationName);
//        }
//    });
//    skeletonNode->setEndListener( [this] (int trackIndex) {
//        if (m_pStateMachine->isInState(*attackState)){
//            log("%d end", trackIndex);
//        }
//    });
//    skeletonNode->setCompleteListener( [this] (int trackIndex, int loopCount) {
////        if (m_pStateMachine->isInState(*attackState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            BGTWall *wall = world->getWall();
////            dispatcher->dispatchMessage(0,                  //time delay 1.5
////                                      getID(),           //sender ID
////                                      wall->getID(),           //receiver ID
////                                      Msg_WallDamaged,        //msg
////                                      NULL);
////        }else if(m_pStateMachine->isInState(*stiffState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            //BGTWall *wall = world->getWall();
////            m_pStateMachine->changeState(moveState);
////        }else if(m_pStateMachine->isInState(*fallDownState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            //BGTWall *wall = world->getWall();
////            m_pStateMachine->changeState(standUpState);
////        }else if(m_pStateMachine->isInState(*standUpState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            //BGTWall *wall = world->getWall();
////            m_pStateMachine->changeState(moveState);
////        }
//    });
//    skeletonNode->setEventListener( [this] (int trackIndex, spEvent* event) {
//        if (m_pStateMachine->isInState(*attackState)){
//            log("%d event: %s, %d, %f, %s", trackIndex, event->data->name, event->intValue, event->floatValue, event->stringValue);
//        }
//    });
    
    
//    void setTrackStartListener (spTrackEntry* entry, const StartListener& listener);
//    void setTrackEndListener (spTrackEntry* entry, const EndListener& listener);
//    void setTrackCompleteListener (spTrackEntry* entry, const CompleteListener& listener);
//    void setTrackEventListener (spTrackEntry* entry, const EventListener& listener);
    
//    virtual void onAnimationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);
//    virtual void onTrackEntryEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);
    
    setDirection(direction);
}

void Character::animationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount)
{
    
}

CharacterType Character::getType()
{
    return (CharacterType)monsterData->type;
}

void Character::setLife(float d)
{
    life = d;
}

float Character::getLife()
{
    return life;
}

//void Character::setTotalLife(float d)
//{
//    totalLife = d;
//}

float Character::getTotalLife()
{
    return monsterData->life;
}

//void Character::setSoldierWidth(float d)
//{
//    soldierWidth = d;
//}

float Character::getSoldierWidth()
{
    return monsterData->hitRect.size.width;
}

//void Character::setSoldierHeight(float d)
//{
//    soldierHeight = d;
//}

float Character::getSoldierHeight()
{
    return monsterData->hitRect.size.height;;
}

void Character::setHeightFromFloor(float d)
{
    heightFromFloor = d;
}

float Character::getHeightFromFloor()
{
    return heightFromFloor;
}

//void Character::setMoveSpeed(float d)
//{
//    moveSpeed = d;
//}

float Character::getMoveSpeed()
{
    return monsterData->moveSpeed;
}

//void Character::setAttackSpeed(float d)
//{
//    attackSpeed = d;
//}

float Character::getAttackSpeed()
{
    return monsterData->attackSpeed;
}

//void Character::setDamage(float d)
//{
//    damage = d;
//}

float Character::getDamage()
{
    return (float)monsterData->damage;
}

void Character::setIsRemoteSoldier(bool d)
{
    isRemoteSoldier = d;
}

bool Character::getIsRemoteSoldier()
{
    return isRemoteSoldier;
}

//void Character::setAttackRange(float d)
//{
//    attackRange = d;
//}

float Character::getAttackRange()
{
    return monsterData->attackRange;
}

MonsterData* Character::getMonsterData()
{
    return monsterData;
}
