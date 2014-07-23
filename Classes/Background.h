//
//  Background.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#ifndef __ZooKeeper__Background__
#define __ZooKeeper__Background__

USING_NS_CC;
USING_NS_CC_EXT;

class Background
:public cocos2d::CCLayer
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCBSelectorResolver
,public cocos2d::extension::CCNodeLoaderListener
{
private:
    
public:
    Background();
    ~Background();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Background, create);
    //CREATE_FUNC(Background);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
};

class BackgroundLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BackgroundLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Background);
};



#endif /* defined(__ZooKeeper__Background__) */
