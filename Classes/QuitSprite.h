//
//  QuitSprite.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#ifndef __ZooKeeper__QuitSprite__
#define __ZooKeeper__QuitSprite__

USING_NS_CC;
USING_NS_CC_EXT;

class QuitSprite:
public CCSprite
,public CCTouchDelegate
{
public:
    virtual ~QuitSprite();
    static QuitSprite* spriteModelWithFile(const char *spName);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    bool containTouchPoint(CCTouch* touch);
    CCRect rect();
};


#endif /* defined(__ZooKeeper__QuitSprite__) */
