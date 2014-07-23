//
//  MainScene.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#include "pre_declaration.h"

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("Background", BackgroundLoader::loader());
    lib->registerCCNodeLoader("MainScene", MainSceneLayerLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    CCNode* node = reader->readNodeGraphFromFile("MainScene.ccbi", scene);
    reader->release();
    
    float screenWidth = CCDirector::sharedDirector()->getVisibleSize().width;
    float screenHeight = CCDirector::sharedDirector()->getVisibleSize().height;
    QuitSprite * quitSprite = QuitSprite::spriteModelWithFile("ccbResources/quit_make.png");
    quitSprite->setPosition(ccp(screenWidth-screenHeight/6, screenHeight/6));
    quitSprite->setScale(0.2);

    scene->addChild(quitSprite, 3);
    
    if(node!=NULL)
    {
        scene->addChild(node);
    }
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}

bool MainScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    return true;
}

SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStartGame", MainScene::onStartGame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHighScore", MainScene::onHighScore);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAbout", MainScene::onAbout);
    return NULL;
}

SEL_CCControlHandler MainScene::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void MainScene::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    
}

void MainScene::onStartGame(cocos2d::CCObject *pSender)
{
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, GameScene::scene(), transitionColor));
}

void MainScene::onHighScore(cocos2d::CCObject *pSender)
{
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, HighScore::scene(), transitionColor));
}

void MainScene::onAbout(cocos2d::CCObject *pSender)
{
    ccColor3B transitionColor;
    transitionColor.r = 0;
    transitionColor.g = 0;
    transitionColor.b = 0;
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, AboutScene::scene(), transitionColor));
}

void MainScene::onEnter()
{
    CCLayer::onEnter();
    StartMusic();
}
void MainScene::onExit()
{
    CCLayer::onExit();
    StopMusic();
}

void MainScene::visit(void)
{
    CCLayer::visit();
    
}

void MainScene::StartMusic()
{
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("BackMusic.mp3").c_str());
    
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.8);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("BackMusic.mp3").c_str(), true);
}

void MainScene::StopMusic()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}