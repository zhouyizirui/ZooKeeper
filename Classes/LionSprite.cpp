//
//  LionSprite.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/21/14.
//
//

#include "pre_declaration.h"

void LionSprite::onEnter()
{
    CCSprite::onEnter();
}

void LionSprite::onExit()
{
    CCSprite::onExit();
}

LionSprite* LionSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    LionSprite *pobSprite = new LionSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

LionSprite* LionSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}