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
:m_layerScores(NULL)
{
    
}

HighScore::~HighScore()
{
    CC_SAFE_DELETE(m_layerScores);
}

bool HighScore::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_layerScores", CCLabelTTF*, this->m_layerScores);
    return true;
}

SEL_MenuHandler HighScore::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler HighScore::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturn", HighScore::onReturn);
    return NULL;
}

void HighScore::onReturn(CCObject * pSender)
{
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CCDirector::sharedDirector()->popScene();
}
