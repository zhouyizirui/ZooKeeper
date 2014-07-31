//
//  AboutScene.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#ifndef __ZooKeeper__AboutScene__
#define __ZooKeeper__AboutScene__

USING_NS_CC;
USING_NS_CC_EXT;

class AboutScene
:public cocos2d::CCLayer
,public cocos2d::extension::CCBSelectorResolver
{
private:
    //CC_SYNTHESIZE_READONLY(CCLayerColor*,m_oLayerColor,LayerColor);
public:
    AboutScene();
    ~AboutScene();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AboutScene, create);
    //CREATE_FUNC(Background);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    void menuBackCallback(CCObject *pSender);
};

class AboutSceneLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AboutSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AboutScene);
};




#endif /* defined(__ZooKeeper__AboutScene__) */
