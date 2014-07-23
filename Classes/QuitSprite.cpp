//
//  QuitSprite.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/20/14.
//
//

#include "pre_declaration.h"

QuitSprite * QuitSprite::spriteModelWithFile(const char *spName)
{
    QuitSprite *pobSprite = new QuitSprite();
    
    if (pobSprite && pobSprite->initWithFile(spName))//
    {
        //pobSprite->myInit();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool QuitSprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCLog("%s","ccTouchBegan");
    if(containTouchPoint(touch))
    {
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
            CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    #else
            CCDirector::sharedDirector()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
    #endif
    #endif
        return true;
    }
    return false;
}

void QuitSprite::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void QuitSprite::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

QuitSprite::~QuitSprite(){
    CCLOG("Resolve Function");
}

CCRect QuitSprite::rect()
{
    CCSize size = getTexture()->getContentSize();
    return CCRectMake(-size.width / 2 ,-size.height / 2, size.width ,size.height);
}

bool QuitSprite::containTouchPoint(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}