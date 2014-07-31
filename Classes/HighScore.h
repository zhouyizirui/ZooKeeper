//
//  HighScore.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#ifndef __ZooKeeper__HighScore__
#define __ZooKeeper__HighScore__

#include<string>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
class HighScore
:public cocos2d::CCLayer
,public cocos2d::extension::CCBMemberVariableAssigner
,public cocos2d::extension::CCBSelectorResolver
{
private:
    CCLabelTTF * m_labelScores;
    string *displayScores;
public:
    HighScore();
    ~HighScore();
    virtual bool init();
    virtual void visit(void);
    static cocos2d::CCScene* scene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HighScore, create);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);
    void menuBackCallback(CCObject *pSender);
};

class HighScoreLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HighScoreLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HighScore);
};



#endif /* defined(__ZooKeeper__HighScore__) */
