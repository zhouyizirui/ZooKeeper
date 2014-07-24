//
//  GameScene.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/21/14.
//
//


#include "pre_declaration.h"
#include "GameConstant.h"


TouchType judgeTouchType(CCPoint point);
float Distance(CCPoint a, CCPoint b);
CCScene * GameScene::scene()
{
    CCScene *scene = CCScene::create();
    CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    lib->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
    CCBReader *reader = new CCBReader(lib);
    CCNode *node = reader->readNodeGraphFromFile("GameScene.ccbi", scene);
    reader->release();
    
    if (node!=NULL)
    {
        scene->addChild(node);
    }
    return scene;
}

GameScene::GameScene()
:currentType(NONE)
,m_labelScore(NULL)
,manSprite(NULL)
,meetArray(NULL)
,lionArray(NULL)
,plateArray(NULL)
,backingLions(NULL)
,frontingPlates(NULL)
,stopGame(false)
,increaseLevel(false)
,refreshScore(false)
,levelIndex(6)
,lionNumber(0)
,score(0)
,manIndex(0)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

GameScene::~GameScene()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CC_SAFE_RELEASE(manSprite);
    CC_SAFE_DELETE(m_labelScore);
    
    CC_SAFE_RELEASE(lionArray);
    CC_SAFE_RELEASE(meetArray);
    CC_SAFE_RELEASE(plateArray);
    CC_SAFE_RELEASE(frontingPlates);
    CC_SAFE_RELEASE(backingLions);
    
    CCLOG("In the destroy function");
}

bool GameScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_labelScore", CCLabelTTF*, this->m_labelScore);
    return true;
}

SEL_MenuHandler GameScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler GameScene::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onReturn", GameScene::onReturn);
    return NULL;
}

void GameScene::onReturn(CCObject * pSender)
{
    gameOver();
    AudioControl::resumeBackground();
    //SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CCDirector::sharedDirector()->popScene();
}

void setPositions()
{
    manPositions[0] = ccp(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*7/8);
    manPositions[1] = ccp(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*5/8);
    manPositions[2] = ccp(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*3/8);
    manPositions[3] = ccp(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*1/8);
    
    lionPositions[0] = ccp(0.2, SCREEN_HEIGHT*7/8);
    lionPositions[1] = ccp(0.2, SCREEN_HEIGHT*5/8);
    lionPositions[2] = ccp(0.2, SCREEN_HEIGHT*3/8);
    lionPositions[3] = ccp(0.2, SCREEN_HEIGHT*1/8);
}

bool GameScene::init()
{
    setPositions();
    CCLOG("In the init function");
    manSprite = CCSprite::create("Feeder_The.png");
    //manSprite->retain();
    manSprite->setPosition(manPositions[0]);
    manSprite->setScale(0.18);
    this->addChild(manSprite, 3);
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("b1.png",
                                                          "b2.png",
                                                          this,
                                                          menu_selector(GameScene::menuBackCallback));
    
    pCloseItem->setPosition(ccp(720, 50));
    CCMenu * pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    
    meetArray = CCArray::create();
    plateArray = CCArray::create();
    lionArray = CCArray::create();
    backingLions = CCArray::create();
    frontingPlates = CCArray::create();
    
    meetArray->retain();
    plateArray->retain();
    lionArray->retain();
    backingLions->retain();
    frontingPlates->retain();
    
    this->schedule(schedule_selector(GameScene::update));
    this->schedule(schedule_selector(GameScene::generate), LEVEL_SPEED[levelIndex]);
    
    return true;
}

void GameScene::menuBackCallback(CCObject *pSender)
{
    
    CCDirector::sharedDirector()->popScene();
    AudioControl::resumeBackground();
}

bool GameScene::ccTouchBegan(CCTouch * touch, CCEvent * event)
{
    TouchType touchType = judgeTouchType(touch->getLocation());
    currentType = touchType;
    changeSurface();
    return true;
}

TouchType judgeTouchType(CCPoint point)
{
    if(point.x<SCREEN_WIDTH*2/3) return LEFT;
    else{
        if(point.y>SCREEN_HEIGHT/2) return RIGHT_UP;
        else return RIGHT_DOWN;
    }
}

void GameScene::changeSurface(void)
{
    switch(currentType){
        case NONE: break;
        case LEFT: {
            CCSprite *plate = CCSprite::create("plate.png");
            plate->setScale(0.08);
            CCPoint startPoint = ccp((manSprite->getPosition()).x-PLATE_PLACE_X_OFFSET, (manSprite->getPosition()).y-PLATE_PLACE_Y_OFFSET);
            plate->setPosition(startPoint);
            this->addChild(plate, 3);
            CCSprite *meet = CCSprite::create("meet.png");
            meet->setScale(0.14);
            meet->setPosition(startPoint);
            this->addChild(meet, 4);
            
            meetArray->addObject(meet);
            plateArray->addObject(plate);
            
            CCPoint finalPosition = ccp(0, startPoint.y);
            CCMoveTo *meetMoveTo = CCMoveTo::create(Distance(startPoint, finalPosition)/MEET_BACKWARD_SPEED, finalPosition);
            meet->runAction(meetMoveTo);
            CCMoveTo *plateMoveTo = CCMoveTo::create(Distance(startPoint, finalPosition)/MEET_BACKWARD_SPEED, finalPosition);
            plate->runAction(plateMoveTo);

            AudioControl::playThrowEffect();
            
        } break;
        case RIGHT_UP: {
            if(manIndex!=0) {
                manSprite->setPosition(manPositions[manIndex-1]);
                manIndex--;
            }
        }break;
        case RIGHT_DOWN: {
            if(manIndex!=3) {
                manSprite->setPosition(manPositions[manIndex+1]);
                manIndex++;
            }
        }break;
    }
}
void GameScene::visit(void)
{
    CCLayer::visit();
}

void GameScene::update(cocos2d::CCTime dt){
    
    for(int i=0; i<meetArray->count(); i++)
    {
        CCSprite *meet = (CCSprite*)meetArray->objectAtIndex(i);
        if(meet->getPosition().x<0.1) {
            meetArray->removeObjectAtIndex(i);
            this->removeChild(meet);
        }
    }
    for(int j=0; j<plateArray->count(); j++)
    {
        CCSprite *plate = (CCSprite*)plateArray->objectAtIndex(j);
        if(plate->getPosition().x<0.1)
        {
            plateArray->removeObjectAtIndex(j);
            this->removeChild(plate);

            AudioControl::playPlateEffect();
            
            score-=50;
            refreshScore=true;
        }
    }
    for(int m = 0; m<frontingPlates->count(); m++)
    {
        CCSprite *newplate = (CCSprite*)frontingPlates->objectAtIndex(m);
        if(newplate->getPosition().x>SCREEN_WIDTH*3/4)
        {
            if(!manSprite->boundingBox().intersectsRect(newplate->boundingBox()))
            {
                frontingPlates->removeObjectAtIndex(m);
                this->removeChild(newplate);
                
                AudioControl::playPlateEffect();
                
                score-=50;
                refreshScore=true;
            }
            else
            {
                frontingPlates->removeObjectAtIndex(m);
                this->removeChild(newplate);
            }
        }
    }
    for(int k=0; k<lionArray->count(); k++)
    {
        LionSprite *lion = (LionSprite*)lionArray->objectAtIndex(k); //FIX ME
        if(lion->getPosition().x>=SCREEN_WIDTH*3/4)
        {
            gameOver();
        }
        else if(lion->getPosition().x<=0.1)
        {
            lion->stopAllActions();
            //LionSprite *backlion = (LionSprite*)backingLions->objectAtIndex(0);
            if(backingLions->count()>0) backingLions->removeObjectAtIndex(0); //Remove the backing lions //FIX ME
            
            
            lionArray->removeObjectAtIndex(k);
            this->removeChild(lion->getParent());
            
            score+=100;
            refreshScore=true;

            AudioControl::playSucessEffect();
        }
    }
    
    for(int i=0; i<meetArray->count(); i++)
    {
        CCSprite * meet = (CCSprite*)meetArray->objectAtIndex(i);
        for(int j=0; j<lionArray->count(); j++)
        {
            LionSprite *lion = (LionSprite*)lionArray->objectAtIndex(j); //FIX ME
            if (lion->boundingBox().intersectsRect(meet->boundingBox()) && lion->getOrientation()==FRONT_ORIENTATION) { //FIX ME
                
                CCSprite *newplate = CCSprite::create("plate.png");
                newplate->setScale(0.08);
                newplate->setPosition(meet->getPosition());
                CCMoveTo *moveTo = CCMoveTo::create(Distance(meet->getPosition(), ccp(SCREEN_WIDTH*3/4+2, newplate->getPosition().y))/PLATE_FORWARD_SPEED, ccp(SCREEN_WIDTH*3/4+2, newplate->getPosition().y));
                newplate->runAction(moveTo);
                frontingPlates->addObject(newplate);
                this->addChild(newplate);
                
                meetArray->removeObjectAtIndex(i);
                this->removeChild(meet);
                CCSprite *plate = (CCSprite*)plateArray->objectAtIndex(i);
                plateArray->removeObjectAtIndex(i);
                this->removeChild(plate);
                
                lion->stopActionByTag(FRONT_ACTION);
                
                CCMoveTo *moveBack = CCMoveTo::create(2.0f, ccp(lion->getPosition().x-200, lion->getPosition().y));
                moveBack->setTag(BACK_ACTION);
                CCMoveTo *moveFront = CCMoveTo::create(Distance(ccp(lion->getPosition().x-200, lion->getPosition().y), ccp(SCREEN_WIDTH*3/4, lion->getPosition().y))/LION_FORWARD_SPEED, ccp(SCREEN_WIDTH*3/4, lion->getPosition().y));
                CCSequence * sequence = CCSequence::create(moveBack, CCCallFunc::create(this, callfunc_selector(GameScene::lionBackEnded)),moveFront, NULL);
                sequence->setTag(FRONT_ACTION);
                lion->setOrientation(BACK_ORIENTATION);
                backingLions->addObject(lion);
                lion->runAction(sequence);
                break;
            }
        }
    }
    changeScore();
    boostLevel();
}

void GameScene::generate(cocos2d::CCTime dt)
{
    if(stopGame!=true){
    CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("lion.plist");
    
    CCSpriteBatchNode * batchNode = CCSpriteBatchNode::create("lion.png");
    LionSprite *sprite = LionSprite::createWithSpriteFrameName("lion1.png"); //FIX ME
    int number = (int)(CCRANDOM_0_1()*4);
    sprite->setPosition(lionPositions[number]);
    sprite->setOrientation(FRONT_ORIENTATION);
    lionArray->addObject(sprite);
    batchNode->addChild(sprite);
    lionNumber++;
        
    this->addChild(batchNode, 1);
    batchNode->setPosition(CCPointZero);
    
    CCArray* animFrames = CCArray::createWithCapacity(12);
    
    for(int i=1; i<=12; i++)
    {
        char str[50] = {0};
        sprintf(str,"lion%d.png", i);
        CCSpriteFrame* frame = frameCache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
    CCActionInterval *interval = CCRepeatForever::create( CCAnimate::create(animation));
    CCMoveTo *moveTo = CCMoveTo::create(Distance(lionPositions[number], manPositions[number])/LION_FORWARD_SPEED, manPositions[number]);
    moveTo->setTag(FRONT_ACTION);
    sprite->runAction(interval);
    sprite->runAction(moveTo);
    }
}

void GameScene::gameOver()
{
    for(int i=0; i<meetArray->count(); i++)
    {
        CCSprite *meet = (CCSprite*)meetArray->objectAtIndex(i);
        meetArray->removeObjectAtIndex(i);
        this->removeChild(meet);
    }
    for(int i=0; i<plateArray->count(); i++)
    {
        CCSprite *plate = (CCSprite*)plateArray->objectAtIndex(i);
        plateArray->removeObjectAtIndex(i);
        this->removeChild(plate);
    }
    for(int i=0; i<frontingPlates->count(); i++)
    {
        CCSprite *newplate = (CCSprite*)frontingPlates->objectAtIndex(i);
        frontingPlates->removeObjectAtIndex(i);
        this->removeChild(newplate);
    }
    for(int i=0; i<lionArray->count(); i++)
    {
        LionSprite *lion = (LionSprite*)lionArray->objectAtIndex(i); //FIX ME
        lionArray->removeObjectAtIndex(i);
        this->removeChild(lion->getParent());
    }
    for(int i=0; i<backingLions->count(); i++)
    {
        LionSprite *lion = (LionSprite*)backingLions->objectAtIndex(i); //FIX ME
        backingLions->removeObjectAtIndex(i);
        this->removeChild(lion->getParent());
    }
    this->removeChild(manSprite);
    stopGame = true;
    CCLabelTTF *label = CCLabelTTF::create("Game Over", "Marker Felt", 38);
    label->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_WIDTH/2));
    this->addChild(label);
    
    AudioControl::playLionEffect();
}

void GameScene::lionBackEnded()
{
    CCLOG("In the back ended");
    LionSprite* lion = (LionSprite*)backingLions->objectAtIndex(0);
    lion->stopActionByTag(BACK_ACTION);
    lion->setOrientation(FRONT_ORIENTATION);
    if (backingLions->count() > 0) backingLions->removeObjectAtIndex(0);
}

void GameScene::changeScore()
{
    if(refreshScore)
    {
        char thescore[20];
        sprintf(thescore, "%d", score);
        char title[20] = "Scores:";
        strcat(title, thescore);
        m_labelScore->setString(title);
        refreshScore=false;
        if(lionNumber>0 && lionNumber%10==0) increaseLevel=true; //FIX ME
    }
}

void GameScene::boostLevel()
{
    if(increaseLevel)
    {
        levelIndex--;
        if(levelIndex<0) levelIndex=0;
        this->unschedule(schedule_selector(GameScene::generate));
        this->schedule(schedule_selector(GameScene::generate), LEVEL_SPEED[levelIndex]);
        increaseLevel=false;
    }
}

float Distance(CCPoint a, CCPoint b)
{
    return sqrtf(powf(a.x-b.x, 2)+powf(a.y-b.y, 2));
}

