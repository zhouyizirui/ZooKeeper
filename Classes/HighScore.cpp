//
//  HighScore.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#include "pre_declaration.h"

CCScene * HighScore::scene()
{
    CCScene *scene = CCScene::create();
    
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("Background", BackgroundLoader::loader());
    lib->registerCCNodeLoader("HighScore", HighScoreLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    CCNode *node = reader->readNodeGraphFromFile("HighScore.ccbi", scene);
    reader->release();
    if (node!=NULL)
    {
        scene->addChild(node);
    }
    return scene;
}

HighScore::HighScore()
:m_labelScores(NULL)
{
    displayScores = new string("");
}

HighScore::~HighScore()
{
    CC_SAFE_DELETE(displayScores);
}

bool HighScore::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    return true;
}

SEL_MenuHandler HighScore::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler HighScore::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void HighScore::menuBackCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
    AudioControl::resumeBackground();
}

bool HighScore::init()
{
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("b1.png",
                                                          "b2.png",
                                                          this,
                                                          menu_selector(HighScore::menuBackCallback));
    pCloseItem->setPosition(ccp(750, 50));
    pCloseItem->setScale(0.8);
    CCMenu * pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    FileHelper *fileHelper = new FileHelper();
    vector<int> highScores = fileHelper->readTinyXML();
    char score[10];
    for(int i=0; i<3; i++)
    {
        memset(score, 0, 10);
        sprintf(score, "%d", highScores[i]);
        if(i!=2) displayScores->append(score).append("\n");
        else displayScores->append(score);
    }
    m_labelScores = CCLabelTTF::create("", "Marker Felt", 38);
    m_labelScores->setPosition(ccp(400, 250));
    this->addChild(m_labelScores, 4);
    
    CCLabelTTF * topLabel = CCLabelTTF::create("High Scores", "Marker Felt", 46);
    topLabel->setPosition(ccp(400, 360));
    this->addChild(topLabel, 4);
    
    delete fileHelper;
    return true;
}

void HighScore::visit()
{
    CCLayer::visit();
    m_labelScores->setString(displayScores->c_str());
}
