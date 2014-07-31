//
//  AboutScene.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#include "pre_declaration.h"

CCScene * AboutScene::scene()
{
    CCScene *scene = CCScene::create();
    
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("Background", BackgroundLoader::loader());
    lib->registerCCNodeLoader("AboutScene", AboutSceneLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    CCNode *node = reader->readNodeGraphFromFile("AboutScene.ccbi", scene);
    reader->release();
    if (node!=NULL)
    {
        scene->addChild(node);
    }
    return scene;
}

AboutScene::AboutScene()
{
    
}

AboutScene::~AboutScene()
{
    
}

bool AboutScene::init()
{
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("b1.png",
                                                          "b2.png",
                                                          this,
                                                          menu_selector(AboutScene::menuBackCallback));
    pCloseItem->setPosition(ccp(750, 50));
    pCloseItem->setScale(0.8);
    CCMenu * pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    return true;
}

SEL_MenuHandler AboutScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler AboutScene::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturn", AboutScene::onReturn);
    return NULL;
     
}

/*
void AboutScene::onReturn(CCObject * pSender)
{
    CCLOG("We are returned");
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CCDirector::sharedDirector()->popScene();
}
*/

void AboutScene::menuBackCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
    AudioControl::resumeBackground();
}