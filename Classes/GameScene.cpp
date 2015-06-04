//
//  GameScene.cpp
//  BGT
//
//  Created by John Running on 15/2/28.
//
//

#include "GameScene.h"
#include "BGTWall.h"
#include "AppDelegate.h"

GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
    AnimationCache::getInstance()->removeAnimation("m4bullet");
    AnimationCache::getInstance()->removeAnimation("m4bullet_explosion");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("GameScene.plist");
    
}

Scene* GameScene::createSceneWithLevel(unsigned int level)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = new GameScene();
    layer->initWithLevel(level);
    // add layer as a child to scene
    scene->addChild(layer);
    layer->release();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::initWithLevel(unsigned int level)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    SpriteFrameCache *ccsfc = SpriteFrameCache::getInstance();
    
    ccsfc->addSpriteFramesWithFile("VE.plist");
    
    SpriteFrame *frame = nullptr;
    //create bullets animations
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(1.0/25.0);
    animation->setLoops(true);
    animation->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(animation, "m4bullet");
    
    for (int i = 1; i <= 16; i++) {
        frame = ccsfc->getSpriteFrameByName(String::createWithFormat("m4bullet%d.png",i)->getCString());
        animation->addSpriteFrame(frame);
    }

    animation = CCAnimation::create();
    animation->setDelayPerUnit(1.0/25.0);
    AnimationCache::getInstance()->addAnimation(animation, "m4bullet_explosion");
    
    for (int i = 1; i <= 20; i++) {
        frame = ccsfc->getSpriteFrameByName(String::createWithFormat("m4bullet_explosion%d.png",i)->getCString());
        animation->addSpriteFrame(frame);
    }
    
    Animation *bulletAnimation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("m%dbullet",4)->getCString());
    Sprite *skin = Sprite::create();
    addChild(skin,100);
    skin->setPosition(size.width/2,size.height/2);
    skin->runAction(RepeatForever::create(Animate::create(bulletAnimation)));

    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("VE.plist");
    ccsfc->addSpriteFramesWithFile("GameScene.plist");
    
    currentLevel = level;
    state = GameStateReady;

    //log("size:%f,%f,%f",size.width,size.height,scaleFactory);
    
    world = new BGTWorld();
    world->initWithGameScene(this);
    addChild(world);
    world->release();
    
    uiLayer = new UILayer();
    uiLayer->initWithGameScene(this);
    addChild(uiLayer);
    uiLayer->release();
    
    setLevel(currentLevel);
    
    return true;
}

void GameScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    startGame();
}

void GameScene::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}

void GameScene::onEnter()
{
    Layer::onEnter();
    // Register Touch Event
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    
//    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
//    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
//    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
//    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    auto listener = EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit()
{
    Layer::onExit();
}

void GameScene::hideHUD()
{
    uiLayer->setVisible(false);
}

void GameScene::showHUD()
{
    uiLayer->setVisible(true);
}

BGTWorld* GameScene::getWorld()
{
    return world;
}

GameState GameScene::getState()
{
    return state;
}

void GameScene::createWorld()
{
    world->createWorld(currentLevel);
}

void GameScene::startGame()
{
    world->startGame();
    uiLayer->gameStart();
    
    state = GameStateGaming;
    scheduleUpdate();
}

void GameScene::restartGame()
{
    //删掉之前所有的entitymanager里的entity
}

void GameScene::nextLevel()
{
    setLevel(currentLevel+1);
}

void GameScene::setLevel(unsigned value)
{
    currentLevel = value;
    createWorld();
}

void GameScene::pauseGame()
{
    state = GameStatePaused;
    world->pauseGame();
    pausedNodes = Director::getInstance()->getActionManager()->pauseAllRunningActions();
    Director::getInstance()->getScheduler();
}

void GameScene::resumeGame()
{
    Director::getInstance()->getActionManager()->resumeTargets(pausedNodes);
    state = GameStateGaming;
    world->resumeGame();
}

void GameScene::gameEnd(bool isWin)
{
    uiLayer->gameEnd(isWin);
    state = GameStateEnded;
}

void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (state == GameStateGaming) {
        world->onTouchesBegan(touches,unused_event);
    }
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (state == GameStateGaming) {
        world->onTouchesMoved(touches,unused_event);
    }
}

void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    if (state == GameStateGaming) {
        world->onTouchesEnded(touches,unused_event);
    }
}

void GameScene::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
    if (state == GameStateGaming) {
        world->onTouchesCancelled(touches,unused_event);
    }
}

//bool GameScene::onTouchBegan(Touch* touch, Event* event)
//{
//    //c = 0;
//    if (state == GameStateGaming) {
//        world->onTouchBegan(touch,event);
//    }
//    return true;
//}
//
//void GameScene::onTouchMoved(Touch* touch, Event* event)
//{
//        //log("onTouchMoved:%d",c++);
//    if (state == GameStateGaming) {
//        world->onTouchMoved(touch,event);
//    }
//}
//
//void GameScene::onTouchEnded(Touch* touch, Event* event)
//{
//    if (state == GameStateGaming) {
//        world->onTouchEnded(touch,event);
//    }
//}
//
//void GameScene::onTouchCancelled(Touch *touch, Event *unused_event)
//{
//    if (state == GameStateGaming) {
//        world->onTouchCancelled(touch,unused_event);
//    }
//}

void GameScene::update(float dt)
{
    if (state == GameStateGaming) {
        uiLayer->update(dt);
        world->update(dt);
    }
}
