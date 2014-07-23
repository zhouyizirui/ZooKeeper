//
//  LionSprite.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/21/14.
//
//

#ifndef __ZooKeeper__LionSprite__
#define __ZooKeeper__LionSprite__

USING_NS_CC;
USING_NS_CC_EXT;

class LionSprite:
public CCSprite
{
public:
    CC_SYNTHESIZE(int, orientation, Orientation);
    virtual void onEnter();
    virtual void onExit();
    static LionSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    static LionSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
};

#endif /* defined(__ZooKeeper__LionSprite__) */
