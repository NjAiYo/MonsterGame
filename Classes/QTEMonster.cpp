//
//  QTEMonster.cpp
//  MonsterGame
//
//  Created by John Running on 15/5/4.
//
//

#include "QTEMonster.h"
#include "AppDelegate.h"
#include "GameEntityManager.h"
#include "MessageDispatcher.h"
#include "QTELayer.h"

QTEMonster::QTEMonster()
:type((CharacterType)99999)
,characterScaleFactor(1)
{
    
}

QTEMonster::~QTEMonster()
{
    
}

bool QTEMonster::initWithQTELayerAndType(QTELayer *l,CharacterType t)
{
    if (!Node::init()) {
        return false;
    }
    layer = l;
    characterScaleFactor = 1;
    setType(t);
    return true;
}

void QTEMonster::reset()
{
    attackNum = 0;
    skeletonNode->setTimeScale(1);
    skeletonNode->setAnimation(0, StandAnimationName, true);
}

void QTEMonster::attack()
{
    spTrackEntry* entry = skeletonNode->setAnimation(0, AttackAnimationName, true);
    skeletonNode->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        attackNum++;
        layer->qteAttacked();
//        BGTWall *wall = this->getWorld()->getWall();
//        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
//                                                          this->getID(),           //sender ID
//                                                          wall->getID(),           //receiver ID
//                                                          Msg_QTEDamaged,        //msg
//                                                          nullptr);
    });
}

bool QTEMonster::hittestPoint(Vec2 p)
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    Vec2 pos = this->convertToNodeSpace(p);
    
    spBone *bodybone = skeletonNode->findBone("body");
    spAttachment *ata = skeletonNode->getAttachment("hitBox", "hitBox");
    spBoundingBoxAttachment *boundingAttachment = (spBoundingBoxAttachment*)ata;
    
    spPolygon *boundingPolygon = spPolygon_create(boundingAttachment->verticesCount);
    for (int i = 0; i<boundingAttachment->verticesCount; i++) {
        boundingPolygon->vertices[i]=boundingAttachment->vertices[i];
        boundingPolygon->count+=1;
    }
    spBoundingBoxAttachment_computeWorldVertices(boundingAttachment, bodybone, boundingPolygon->vertices);
    
    for (int i = 0; i<boundingPolygon->count; i++) {
        boundingPolygon->vertices[i]=boundingPolygon->vertices[i]*scaleFactory*characterScaleFactor;
    }
    
    bool clicked = spPolygon_containsPoint(boundingPolygon, pos.x, pos.y);
    spPolygon_dispose(boundingPolygon);
    return clicked;
}

CharacterType QTEMonster::getType()
{
    return type;
}

void QTEMonster::setType(CharacterType d)
{
    if(type == d) return;
    type = d;
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    if(skeletonNode){
        skeletonNode->removeFromParent();
        skeletonNode = NULL;
    }

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
 
    skeletonNode->setAnimation(0, StandAnimationName, true);
}

bool QTEMonster::handleMessage(const Telegram& msg)
{
    return false;
}

void QTEMonster::update(float dt)
{
    
}

void QTEMonster::die(){
    skeletonNode->setAnimation(0, DieAnimationName, false);
}

void QTEMonster::beginAttack()
{
    attackNum = 0;
    skeletonNode->setTimeScale(4.7);
    attack();
}

void QTEMonster::stand()
{
    skeletonNode->setTimeScale(1);
    skeletonNode->setAnimation(0, StandAnimationName, true);
}
