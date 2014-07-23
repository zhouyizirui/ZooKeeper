//
//  MainScene.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#ifndef __ZooKeeper__MainScene__
#define __ZooKeeper__MainScene__
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MainScene:
public cocos2d::CCLayer
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCNodeLoaderListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    //CREATE_FUNC(MainScene);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void onStartGame(cocos2d::CCObject *pSender);
    void onHighScore(cocos2d::CCObject *pSender);
    void onAbout(cocos2d::CCObject *pSender);
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainScene, create);
    
    void StartMusic();
    void StopMusic();
    virtual void onEnter();
    virtual void onExit();
    virtual void visit(void);
};

class MainSceneLayerLoader:public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};
#endif /* defined(__ZooKeeper__MainScene__) */
