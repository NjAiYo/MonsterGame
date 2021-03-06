//
//  BGTWorld.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTWorld.h"
#include "GameScene.h"
#include "AppDelegate.h"
#include "BGTWall.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "MessageDispatcher.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Knife.h"
#include "CCShake.h"
#include "MonsterData.h"

BGTWorld::BGTWorld()
:currentLevelIndex(-1)
,currentWaveIndex(-1)
,currentWave(NULL)
,gameBgSprite(NULL)
,qteCharacter(nullptr)
{
    
}

BGTWorld::~BGTWorld()
{
    free(roads);
}

bool BGTWorld::initWithGameScene(GameScene *gs)
{
    if (!Node::init()) {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    waveManager = WaveManager::getInstance();
    gameScene = gs;
    entityManager = GameEntityManager::getInstance();
    dispatcher = MessageDispatcher::getInstance();

    bgLayer = Layer::create();
    addChild(bgLayer,-1);
    
    shadowLayer = Layer::create();
    addChild(shadowLayer,0);
    
    for (int i = 0; i < 10; i++) {
        Sprite *sprite = Sprite::createWithSpriteFrameName("shadow.png");
        shadowLayer->addChild(sprite);
        sprite->setVisible(false);
        shadowsPool.pushBack(sprite);
    }
    
    battlefieldLayer = Layer::create();
    addChild(battlefieldLayer,1);
    
    monsterLayer = Layer::create();
    battlefieldLayer->addChild(monsterLayer);
    
    for (int i = 0; i < 5; i++) {
        MonsterBullet *bullet = new MonsterBullet();
        bullet->initWithWorld(this);
        monsterLayer->addChild(bullet);
        bullet->release();
        bulletsPool.pushBack(bullet);
        bullet->setVisible(false);
        entityManager->registerEntity(bullet);
    }
    
    
    frontBgLayer = Layer::create();
    addChild(frontBgLayer,2);
    
    
    qteLayer = new QTELayer();
    qteLayer->initWithWorld(this);
    addChild(qteLayer,999999);
    qteLayer->setVisible(false);
    qteLayer->release();
    
    
    weaponLayer = Layer::create();
    addChild(weaponLayer,3);
    inQTEMode = false;
    wall = new BGTWall();
    wall->initWithWorld(this);
    bgLayer->addChild(wall,1);
    wall->release();
    entityManager->registerEntity(wall);
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    wall->setPosition(150*scaleFactory,500*scaleFactory);
    Vec2 wallPosition = wall->getPosition();
    
    float x1 = wallPosition.x + cosf(M_PI*-70.0f/180.0f)*wall->getWidth()/2;
    float y1 = wallPosition.y - sinf(M_PI*-70.0f/180.0f)*wall->getWidth()/2;
    wall->topPosition = Vec2(x1,y1);
    
    float x2 = wallPosition.x + cosf(M_PI*110.0f/180.0f)*wall->getWidth()/2;
    float y2 = wallPosition.y - sinf(M_PI*110.0f/180.0f)*wall->getWidth()/2;
    wall->bottomPosition = Vec2(x2,y2);
    bottomPositionYForMonster = wall->bottomPosition.y - 50;
//    auto draw = DrawNode::create();
//    addChild(draw, 10);
//    draw->drawLine(Vec2(x1,y1), Vec2(x2, y2), Color4F(0.0, 1.0, 0.0, 1.0));
    
    road0Y = y1;
    road1Y = wallPosition.y - sinf(M_PI*-70.0f/180.0f)*wall->getWidth()/4;
    road2Y = wallPosition.y;
    road3Y = wallPosition.y - sinf(M_PI*110.0f/180.0f)*wall->getWidth()/4;
    road4Y = y2;
    
    roads = (float*)malloc(sizeof(float)*5);
    roads[0] = road0Y;
    roads[1] = road1Y;
    roads[2] = road2Y;
    roads[3] = road3Y;
    roads[4] = road4Y;
    
    knife = new Knife();
    knife->initWithWorld(this);
    battlefieldLayer->addChild(knife,10000);
    knife->release();
    weapons.pushBack(knife);
    
    pistol = new Pistol();
    pistol->initWithWorld(this);
    battlefieldLayer->addChild(pistol,10000);
    pistol->release();
    weapons.pushBack(pistol);
    entityManager->registerEntity(knife);
    entityManager->registerEntity(pistol);
    
    

    
    uiLayer = Layer::create();
    addChild(uiLayer,4);
    waveTip = Label::create("一大波怪物正在靠近", "Arial", 120*scaleFactory);
    waveTip->setColor(Color3B(255, 255, 255));
    uiLayer->addChild(waveTip);
    waveTip->setPosition(size.width/2+size.width, size.height/2);
    waveTip->setVisible(false);
    
    
    enegy = 0;
    maxEnegy = 100;
    
    _eventDispatcher->addCustomEventListener("MonsterDied", CC_CALLBACK_1(BGTWorld::monsterDiedHandler,this));
    _eventDispatcher->addCustomEventListener("monsterSkilled", CC_CALLBACK_1(BGTWorld::monsterSkilledHandler,this));
    _eventDispatcher->addCustomEventListener("MonsterShot", CC_CALLBACK_1(BGTWorld::monsterShotHandler,this));
    
    

    return true;
}

Sprite* BGTWorld::getShadowByMonster(Character* monster)
{
    for (int i = 0; i < shadowsPool.size(); i++) {
        Sprite *label = shadowsPool.at(i);
        if (label->isVisible() && label->getTag() == monster->getID()) {
            return label;
        }
    }
    return nullptr;
}

MonsterBullet* BGTWorld::getIdleBulletFromPool()
{
    for (int i = 0; i < bulletsPool.size(); i++) {
        MonsterBullet* label = bulletsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    MonsterBullet *bullet = new MonsterBullet();
    bullet->initWithWorld(this);
    monsterLayer->addChild(bullet);
    bullet->release();
    bulletsPool.pushBack(bullet);
    bullet->setVisible(false);
    entityManager->registerEntity(bullet);
    return bullet;
}

Sprite* BGTWorld::getIdleShadowFromPool()
{
    for (int i = 0; i < shadowsPool.size(); i++) {
        Sprite *label = shadowsPool.at(i);
        if (!label->isVisible()) {
            return label;
        }
    }
    Sprite *sprite = Sprite::createWithSpriteFrameName("shadow.png");
    shadowLayer->addChild(sprite);
    sprite->setVisible(false);
    shadowsPool.pushBack(sprite);
    return sprite;
}

void BGTWorld::monsterShotHandler(EventCustom* event)
{
    ShotInfo *info = (ShotInfo*)event->getUserData();
    Character *monster = (Character*)entityManager->getEntityFromID(info->monsterId);
    Vec2 startPos = monster->convertToWorldSpace(Vec2(info->x,info->y));
    //Vec2 startPos = Vec2(info->x+monster->getPositionX(),info->y+monster->getPositionY());
    MonsterBullet *bullet = getIdleBulletFromPool();
    bullet->setPosition(startPos);
    bullet->flyY = startPos.y;
    bullet->setType(monster->getType());
    bullet->speed = monster->getMonsterData()->arrowMoveSpeed;
    bullet->damage = monster->getDamage();
    bullet->baoji = monster->getMonsterData()->baoji;
    bullet->fly();
    bullet->setLocalZOrder(monster->getLocalZOrder());
}

void BGTWorld::monsterSkilledHandler(EventCustom* event)
{
    skillCharacter = (Character*)event->getUserData();
    isPlaySkill = true;
    //pause 1 second
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible() || skillCharacter==monster) {
            continue;
        }
        monster->pause();
    }
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(BGTWorld::resumeSkill), 1.0f);
}

void BGTWorld::resumeSkill(float dt)
{
    shake(0.1f,5);
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->resume();
    }
    
    isPlaySkill = false;
}

void BGTWorld::monsterDiedHandler(EventCustom* event)
{
    Character *monster = (Character*)event->getUserData();
    int lucky = (lucky / 20)*0.01;
    
    float rate = 0.5 + lucky;
    float value = CCRANDOM_0_1();
    if (value <= rate) {
        //drop coins
        value = CCRANDOM_0_1();
        if (value <= 0.5) {
            //small
        }else if(value <= 0.8){
            //middle
        }else{
            //big
        }
    }
    
    rate = 0.3 + lucky;
    value = CCRANDOM_0_1();
    if (value <= rate) {
        //drop 补给品
        value = CCRANDOM_0_1();
        if (value <= 0.3) {
            //life ball
        }else if(value <= 0.5){
            //enegy ball
        }else{
            //bullets
        }
    }
    
    rate = 0.2 + lucky;
    value = CCRANDOM_0_1();
    if (value <= rate) {
        //drop
//        value = CCRANDOM_0_1();
//        if (value <= 0.7) {
//            //材料
//        }else{
//            //装备
//            value = CCRANDOM_0_1();
//            if (value <= 0.25) {
//                //枪
//                
//            }else if(value <= 0.5){
//                //刀
//                
//            }else if(value <= 0.75){
//                //戒指
//                
//            }else{
//                //项链
//                
//            }
//            float v = -4 + floorf(CCRANDOM_0_1() * 9);
//            int dropLevel = (int)v + monster->getMonsterData()->level;
//            
//        }
    }
}

bool BGTWorld::isQTEMode()
{
    return inQTEMode;
}

void BGTWorld::enterQTEMode(Character* m)
{
    inQTEMode = true;
    qteCharacter = m;
    qteLayer->setMonsterType(m->getType());
    

    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {// || monster==m
            continue;
        }
        monster->pause();
    }
    gameScene->hideHUD();
    qteLayer->qteBegin();
    qteLayer->setVisible(true);
}

void BGTWorld::exitQTEMode(bool playerWin)
{
    inQTEMode = false;
    qteLayer->setVisible(false);
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->resume();
    }
    if (playerWin) {
        qteCharacter->die();
    }else{
        wall->takeDamage(20);
    }
    
    gameScene->showHUD();

}

void BGTWorld::onEnter()
{
    Node::onEnter();
}

void BGTWorld::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void BGTWorld::onExit()
{
    Node::onExit();
}

void BGTWorld::launchCurrentSkill(){
    
}

void BGTWorld::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
}

//回放，枪蓄力，子弹，技能点，蓄力功能调整，浮空调整，记录保存，编辑器，出怪功能，掉落物品，能量，耐久度，必杀，qte,自动拾取
void BGTWorld::createWorld(int level){
    currentLevelIndex = level;
    Size size = Director::getInstance()->getWinSize();
    


    if(gameBgSprite && gameBgSprite->getTag()!=currentLevelIndex){
        gameBgSprite->removeFromParent();
        frontbgSprite->removeFromParent();
    }
    

    if(!gameBgSprite){
        gameBgSprite = Sprite::create("gamebg0.png");
        gameBgSprite->setTag(currentLevelIndex);
        float w = gameBgSprite->getContentSize().width;
        float h = gameBgSprite->getContentSize().height;
        gameBgSprite->setScaleX(size.width/w);
        gameBgSprite->setScaleY(size.height/h);
        bgLayer->addChild(gameBgSprite,0);
        
        gameBgSprite->setPosition(size.width/2,size.height/2);
        
        frontbgSprite = Sprite::create("gamebg0front.png");
        frontbgSprite->setAnchorPoint(Vec2(0.5,0));
        frontbgSprite->setScaleX(size.width/w);
        frontbgSprite->setScaleY(size.height/h);
        frontbgSprite->setPosition(size.width/2,0);
        frontBgLayer->addChild(frontbgSprite);
    }
    wall->reset();
    
    
    //
    
    //doormask.png
    
    for(int i = 0; i < monsterPool.size(); i++){
        Character *enemy = monsterPool.at(i);
        enemy->setTag(-1);
    }
    
    
    currentLevelData = waveManager->getLevelData(currentLevelIndex);
    for (int i = 0; i < currentLevelData->waves.size(); i++) {
        Wave *wave = currentLevelData->waves.at(i);
        
        //为这次的战斗生成怪物数据
        wave->generateUnitsDataForBattle();
        Vector<Unit*> allUnits = wave->getAllUnits();
        //根据数据生出怪物对象池
        for (int j = 0; j < allUnits.size(); j++) {
            Unit *unit = allUnits.at(j);
            getIdleEnemyByTypeFromPoolForInit(unit->outType);
//            Character *enemy = getIdleEnemyByTypeFromPoolForInit(unit->outType);
//            enemy->setPosition(Vec2(size.width+unit->outPosition.x+50, wall->bottomPosition.y+unit->outPosition.y));
//            enemy->setFloor(wall->bottomPosition.y+unit->outPosition.y);
        }
    }
    
    currentWeapon = knife;
    

//    Character *monster = getIdleEnemyFromPool();
//    monster->setVisible(true);
//    monster->setPosition(Vec2(size.width+arc4random()%100, roads[r]));
//    monster->setFloor(roads[r]);
//    monster->move();
    
    //shake(0.1f,5);
}

void BGTWorld::shake( float d, float strength )
{
    CCShake* shake = CCShake::create(d,strength);
    shake->setTag(145);
    this->stopActionByTag(145);
    this->setPosition(Vec2(0,0));
    this->runAction(shake);
}

void BGTWorld::toggleToGun()
{
    currentWeapon = pistol;
}

void BGTWorld::toggleToKnife()
{
    currentWeapon = knife;
}

Character* BGTWorld::getIdleEnemyByTypeFromPoolForInit(int type){
    Character *enemy = NULL;
    for (Character *monster : monsterPool) {
        if (monster->getTag()==-1 && monster->getType() == type) {
            enemy = monster;
            break;
        }
    }
    if (!enemy) {
        enemy = new Character();
        enemy->initWithWorldAndType(this,(CharacterType)type);
        monsterLayer->addChild(enemy);
        enemy->setVisible(false);
        enemy->setTag(-1);
        enemy->release();
        monsterPool.pushBack(enemy);
        entityManager->registerEntity(enemy);
    }
    return enemy;
}

Character* BGTWorld::getIdleEnemyByTypeFromPool(int type){
    Character *enemy = NULL;
    for (Character *monster : monsterPool) {
        if (!monster->isVisible() && monster->getType() == type) {
            enemy = monster;
            break;
        }
    }
    if (!enemy) {
        enemy = new Character();
        enemy->initWithWorldAndType(this,(CharacterType)type);
        monsterLayer->addChild(enemy);
        enemy->setVisible(false);
        enemy->release();
        monsterPool.pushBack(enemy);
        entityManager->registerEntity(enemy);
    }
    return enemy;
}

bool BGTWorld::isUseKnife()
{
     return currentWeapon==knife;
}

Weapon* BGTWorld::getCurrentWeapon()
{
    return currentWeapon;
}

void BGTWorld::toggleWeapon()
{
    if (currentWeapon == knife) {
        currentWeapon = pistol;
    }else{
        currentWeapon = knife;
    }
}

BGTWall* BGTWorld::getWall()
{
    return wall;
}

Vector<Character*> BGTWorld::getMonsters()
{
    return monsterPool;
}

float BGTWorld::getEnegy()
{
    return enegy;
}

void BGTWorld::reset()
{
    currentWaveIndex = -1;
    timePast = 0;
    enegy = 0;
    maxEnegy = 100;
    totalKilledNum = 0;
    waveEnemyNumLeftToBeOut = 0;
    waveKilledNum = 0;
    nextWaveOutTimeLeft = 0.1;
    showedNextWaveUI = false;
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->resume();
    }
}

void BGTWorld::startGame()
{
    reset();
}

void BGTWorld::endGame(bool isWin)
{
    gameScene->gameEnd(isWin);
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->pause();
    }
}

void BGTWorld::nextWave(){
    currentWaveIndex++;
    timePast = 0;
    showedNextWaveUI = false;
    log("%d:currentLevelData->waves=%zd",currentWaveIndex,currentLevelData->waves.size());
    if (currentWaveIndex < currentLevelData->waves.size()) {
        currentWave = currentLevelData->getWave(currentWaveIndex);
        Vector<Unit*> allUnits = currentWave->getAllUnits();
        log("allUnits.size()=%zd",allUnits.size());
        waveEnemyNumLeftToBeOut = (unsigned int)allUnits.size();
        waveKilledNum = 0;
    }
}

void BGTWorld::monsterDied(Character* monster)
{
    Sprite *shadow = getShadowByMonster(monster);
    shadow->setVisible(false);
    shadow->setTag(-1);
    
    enegy += 5;
    if (enegy > 100) {
        enegy = 100;
    }
    totalKilledNum++;
    waveKilledNum++;
    if(waveKilledNum >= currentWave->getAllUnits().size()){
        if(currentWaveIndex == currentLevelData->waves.size()-1){
            //最后一波的所有怪都杀了
            CallFunc *func = CallFunc::create([=](){
                endGame(true);
            });
            waveTip->runAction(Sequence::create(DelayTime::create(1.0),func, NULL));
        }else{
            //这一波怪物都被杀了
            if (nextWaveOutTimeLeft > 4) {
                nextWaveOutTimeLeft = 4;
                //showNextWaveUI();
            }
        }
    }
}

void BGTWorld::showNextWaveUI(){
    waveTip->setVisible(true);
    Size size = Director::getInstance()->getWinSize();
    waveTip->setPosition(size.width/2+size.width, size.height/2);
    waveTip->runAction(Sequence::create(DelayTime::create(1.0),MoveBy::create(0.5, Vec2(-size.width,0)),DelayTime::create(1.0),MoveBy::create(0.5, Vec2(-size.width,0)), NULL));
}

void BGTWorld::resumeGame(){
//    for(Character *monster : monsterPool)
//    {
//        if (!monster->isVisible()) {
//            continue;
//        }
//        monster->pause();
//    }
}

void BGTWorld::pauseGame(){
//    for(Character *monster : monsterPool)
//    {
//        if (!monster->isVisible()) {
//            continue;
//        }
//        monster->resume();
//    }
}


void BGTWorld::update(float dt)
{
    if (inQTEMode) {
        return;
    }
    timePast += dt;
    if (nextWaveOutTimeLeft > 0) {
        //log("nextWaveOutTimeLeft:%f",nextWaveOutTimeLeft);
        nextWaveOutTimeLeft -= dt;
        if(nextWaveOutTimeLeft <=4 && nextWaveOutTimeLeft>3 && !showedNextWaveUI){
            showNextWaveUI();
            showedNextWaveUI = true;
        }
        if(nextWaveOutTimeLeft <=0){
            nextWave();
        }
    }


    //put next enemy to battle field
    if(currentWave){
        Size size = Director::getInstance()->getWinSize();
        Vector<Unit*> allUnits = currentWave->getAllUnits();
        //根据数据生出怪物对象池
        for (int j = 0; j < allUnits.size(); j++) {
            Unit *unit = allUnits.at(j);
            if (unit->outed) {
                continue;
            }
            if (unit->outTime <= (timePast-1)) {
                Character *monster = getIdleEnemyByTypeFromPool(unit->outType);
                float y = bottomPositionYForMonster+unit->outPosition.y;
                float floorY = y;
                if (monster->isjumper()) {
                    y = size.height + 200;
                }
                monster->reset();
                monster->setPosition(Vec2(size.width+unit->outPosition.x+50, y));
                monster->setFloor(floorY);
                monster->setLocalZOrder(9999-y);
                monster->setVisible(true);
                if (monster->isjumper()) {
                    monster->drop();
                }else{
                    monster->move();
                }
                
                unit->outed = true;
                waveEnemyNumLeftToBeOut--;
                if(waveEnemyNumLeftToBeOut<=0){
                    //这一波所有的怪物都出击了,
                    nextWaveOutTimeLeft = waveGapTime;
                }
                Sprite *shadow = getIdleShadowFromPool();
                shadow->setVisible(true);
                shadow->setTag(monster->getID());
                shadow->setPosition(monster->getPositionX(),monster->getFloor());
                
                //log("put monster to field:type=%d,x=%f,y=%f,time=%f",unit->outType,unit->outPosition.x,unit->outPosition.y,unit->outTime);
                std::sort(monsterPool.begin(), monsterPool.end(), [](Node* a, Node* b){
                    return a->getLocalZOrder() >= b->getLocalZOrder();
                });
            }
        }
    }
    
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->update(dt);
        Sprite *shadow = getShadowByMonster(monster);
        if (shadow) {
            shadow->setPosition(monster->getPositionX(),monster->getPositionY());
        }
    }
    
    for (int i = 0; i < bulletsPool.size(); i++) {
        MonsterBullet* bullet = bulletsPool.at(i);
        if (!bullet->isVisible()) {
            continue;
        }
        bullet->update(dt);
    }
    
    currentWeapon->update(dt);
    wall->update(dt);
    if (wall->getLife() <= 0) {
        endGame(false);
    }
    dispatcher->dispatchDelayedMessages();
}

void BGTWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (inQTEMode) {
        qteLayer->onTouchesBegan(touches, unused_event);
    }else{
        currentWeapon->onTouchesBegan(touches, unused_event);
    }
}

void BGTWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (inQTEMode) {
        qteLayer->onTouchesMoved(touches, unused_event);
    }else{
        currentWeapon->onTouchesMoved(touches, unused_event);
    }
}

void BGTWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (inQTEMode) {
        qteLayer->onTouchesEnded(touches, unused_event);
    }else{
        currentWeapon->onTouchesEnded(touches, unused_event);
    }
}

void BGTWorld::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
    if (inQTEMode) {
        qteLayer->onTouchesCancelled(touches, unused_event);
    }else{
        currentWeapon->onTouchesCancelled(touches, unused_event);
    }
}

//bool BGTWorld::onTouchBegan(Touch* touch, Event* event)
//{
//    if (inQTEMode) {
//        qteLayer->onTouchBegan(touch, event);
//    }else{
//        currentWeapon->onTouchBegan(touch, event);
//    }
//
//    return true;
//}
//
//void BGTWorld::onTouchMoved(Touch* touch, Event* event)
//{
//    if (inQTEMode) {
//        qteLayer->onTouchMoved(touch, event);
//    }else{
//        currentWeapon->onTouchMoved(touch, event);
//    }
//
//}
//
//void BGTWorld::onTouchEnded(Touch* touch, Event* event)
//{
//    if (inQTEMode) {
//        qteLayer->onTouchEnded(touch, event);
//    }else{
//        currentWeapon->onTouchEnded(touch, event);
//    }
//}
//
//void BGTWorld::onTouchCancelled(Touch *touch, Event *unused_event)
//{
//    if (inQTEMode) {
//        qteLayer->onTouchCancelled(touch, unused_event);
//    }else{
//        currentWeapon->onTouchCancelled(touch, unused_event);
//    }
//}
