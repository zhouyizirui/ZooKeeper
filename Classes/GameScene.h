//
//  GameScene.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/21/14.
//
//

#ifndef __ZooKeeper__GameScene__
#define __ZooKeeper__GameScene__

USING_NS_CC;
USING_NS_CC_EXT;

enum TouchType{
    NONE=1, LEFT, RIGHT_UP, RIGHT_DOWN
};
class GameScene
:public cocos2d::CCLayer
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCBSelectorResolver
{
private:
    //CC_SYNTHESIZE_READONLY(CCLayerColor*,m_oLayerColor,LayerColor);
    TouchType currentType;
    CCSprite * manSprite;
    CCArray * lionArray;
    CCArray * plateArray;
    CCArray * meetArray;
    CCArray * backingLions;
    CCArray * frontingPlates;
    CCLabelTTF * m_labelScore;
    bool stopGame;
    int manIndex;
    int score;
    int levelIndex;
public:
    GameScene();
    ~GameScene();
    static cocos2d::CCScene* scene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameScene, create);
    //CREATE_FUNC(Background);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode);
    void onReturn(CCObject* pSender);
    virtual bool init();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void visit(void);
    void gameOver();
    void update(cocos2d::CCTime dt);
    void generate(cocos2d::CCTime dt);
    void changeSurface(void);
    void lionBackEnded();
    void menuBackCallback(CCObject *pSender);
    void changeScore();
};

class GameSceneLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameScene);
};



#endif /* defined(__ZooKeeper__GameScene__) */
