//
//  GameScene.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/21/14.
//
//


#include "pre_declaration.h"
#include "GameConstant.h"

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
,distinguishNumber(0)
,score(0)
,manIndex(0)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

GameScene::~GameScene()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CC_SAFE_RELEASE(manSprite);
    CC_SAFE_RELEASE(m_labelScore);
    
    CC_SAFE_RELEASE(lionArray);
    CC_SAFE_RELEASE(meetArray);
    CC_SAFE_RELEASE(plateArray);
    CC_SAFE_RELEASE(frontingPlates);
    CC_SAFE_RELEASE(backingLions);
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
    
    //Create the man sprite
    manSprite = CCSprite::create("Feeder_The.png");
    manSprite->setPosition(manPositions[0]);
    manSprite->setScale(0.15);
    manSprite->retain();
    this->addChild(manSprite, 3);
    
    //Create the close menu sprite
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("b1.png",
                                                          "b2.png",
                                                          this,
                                                          menu_selector(GameScene::menuBackCallback));
    pCloseItem->setPosition(ccp(750, 50));
    pCloseItem->setScale(0.8);
    CCMenu * pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    //Create the arrays
    meetArray = CCArray::create();
    plateArray = CCArray::create();
    lionArray = CCArray::create();
    backingLions = CCArray::create();
    frontingPlates = CCArray::create();
    
    //Retain them
    meetArray->retain();
    plateArray->retain();
    lionArray->retain();
    backingLions->retain();
    frontingPlates->retain();
    
    //Set the scheduler, game started
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
    touchRespond();
    return true;
}

TouchType GameScene::judgeTouchType(CCPoint point)
{
    if(stopGame) return NONE;
    else
    {
        if(point.x<SCREEN_WIDTH*2/3) return LEFT;
        else{
            if(point.y>SCREEN_HEIGHT/2) return RIGHT_UP;
            else return RIGHT_DOWN;
        }
    }
}

void GameScene::touchRespond(void)
{
    switch(currentType){
        case NONE: break;
        case LEFT: {
            //Start point is a little biased
            CCPoint startPoint = ccp((manSprite->getPosition()).x-PLATE_PLACE_X_OFFSET, (manSprite->getPosition()).y-PLATE_PLACE_Y_OFFSET);
            
            //Create the plate
            CCSprite *plate = CCSprite::create("plate.png");
            plate->setScale(0.06);
            plate->setPosition(startPoint);
            this->addChild(plate, 3);
            
            //Create the meet
            CCSprite *meet = CCSprite::create("meet.png");
            meet->setScale(0.10);
            meet->setPosition(startPoint);
            this->addChild(meet, 4);
            
            //Add them to the array
            meetArray->addObject(meet);
            plateArray->addObject(plate);
            
            //Run the action to move the meet and plate
            CCPoint finalPosition = ccp(0, startPoint.y);
            CCMoveTo *meetMoveTo = CCMoveTo::create(Distance(startPoint, finalPosition)/MEET_BACKWARD_SPEED, finalPosition);
            meet->runAction(meetMoveTo);
            CCMoveTo *plateMoveTo = CCMoveTo::create(Distance(startPoint, finalPosition)/MEET_BACKWARD_SPEED, finalPosition);
            plate->runAction(plateMoveTo);
            
            //Play the effect
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
            //Remove it
            meetArray->removeObjectAtIndex(i);
            this->removeChild(meet);
            i--; //IMPORTANT!!!!
        }
    }
    for(int j=0; j<plateArray->count(); j++)
    {
        CCSprite *plate = (CCSprite*)plateArray->objectAtIndex(j);
        if(plate->getPosition().x<0.1)
        {
            //Remove it
            plateArray->removeObjectAtIndex(j);
            this->removeChild(plate);
            j--; //IMPORTANT!!!
            
            //Play effect
            AudioControl::playPlateEffect();
            
            //Change Score
            score-=50;
            refreshScore=true;
            changeScore();
        }
    }
    for(int m = 0; m<frontingPlates->count(); m++)
    {
        CCSprite *newplate = (CCSprite*)frontingPlates->objectAtIndex(m);
        if(newplate->getPosition().x>SCREEN_WIDTH*3/4)
        {
            if(!manSprite->boundingBox().intersectsRect(newplate->boundingBox()))
            {
                //Remove it
                frontingPlates->removeObjectAtIndex(m);
                this->removeChild(newplate);
                m--;//IMPORTANT!!!
                
                //Play effect
                AudioControl::playPlateEffect();
                
                //Change score
                score-=50;
                refreshScore=true;
                changeScore();
            }
            else
            {
                //Remove it
                frontingPlates->removeObjectAtIndex(m);
                this->removeChild(newplate);
                m--;//IMPORTANT!!!
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
            removeBacking(lion);
            
            //Remove it from lion array.
            lionArray->removeObjectAtIndex(k);
            this->removeChild(lion->getParent());
            k--; //IMPORTANT!!!
            
            //Change the score.
            score+=100;
            refreshScore=true;
            changeScore();
            distinguishNumber++;
            changeDistinguishedNumber();
            boostLevel();
            
            //Play the music.
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
                
                //Create the new plate and move it.
                CCSprite *newplate = CCSprite::create("plate.png");
                newplate->setScale(0.05);
                newplate->setPosition(meet->getPosition());
                CCMoveTo *moveTo = CCMoveTo::create(Distance(meet->getPosition(), ccp(SCREEN_WIDTH*3/4+2, newplate->getPosition().y))/PLATE_FORWARD_SPEED, ccp(SCREEN_WIDTH*3/4+2, newplate->getPosition().y));
                newplate->runAction(moveTo);
                frontingPlates->addObject(newplate);
                this->addChild(newplate);
                
                //Remove the meet and the plate.
                meetArray->removeObjectAtIndex(i);
                this->removeChild(meet);
                CCSprite *plate = (CCSprite*)plateArray->objectAtIndex(i);
                this->removeChild(plate);
                plateArray->removeObjectAtIndex(i);
                
                i--; //IMPORTANT!!!!!!!
                
                lion->stopActionByTag(FRONT_ACTION);
                CCMoveTo *moveBack = CCMoveTo::create(Distance(lion->getPosition(), ccp(lion->getPosition().x-LION_BACKWARD_DIS, lion->getPosition().y))/LION_BACKWARD_SPEED, ccp(lion->getPosition().x-LION_BACKWARD_DIS, lion->getPosition().y));
                CCMoveTo *moveFront = CCMoveTo::create(Distance(ccp(lion->getPosition().x-LION_BACKWARD_DIS, lion->getPosition().y), ccp(SCREEN_WIDTH*3/4, lion->getPosition().y))/LION_FORWARD_SPEED, ccp(SCREEN_WIDTH*3/4, lion->getPosition().y));
                CCSequence * sequence = CCSequence::create(moveBack, CCCallFunc::create(this, callfunc_selector(GameScene::lionBackEnded)),moveFront, NULL);
                sequence->setTag(FRONT_ACTION);
                lion->setOrientation(BACK_ORIENTATION);
                backingLions->addObject(lion);
                lion->runAction(sequence);
                break;
            }
        }
    }
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
    sprite->setTag(lionNumber);
    sprite->setScale(0.9);
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
        CCSprite *meet = (CCSprite*)meetArray->objectAtIndex(0);
        meetArray->removeObjectAtIndex(0);
        this->removeChild(meet);
        i--;
    }
    for(int i=0; i<plateArray->count(); i++)
    {
        CCSprite *plate = (CCSprite*)plateArray->objectAtIndex(0);
        plateArray->removeObjectAtIndex(0);
        this->removeChild(plate);
        i--;
    }
    for(int i=0; i<frontingPlates->count(); i++)
    {
        CCSprite *newplate = (CCSprite*)frontingPlates->objectAtIndex(0);
        frontingPlates->removeObjectAtIndex(0);
        this->removeChild(newplate);
        i--;
    }
    for(int i=0; i<lionArray->count(); i++)
    {
        LionSprite *lion = (LionSprite*)lionArray->objectAtIndex(0); //FIX ME
        lionArray->removeObjectAtIndex(0);
        this->removeChild(lion->getParent());
        i--;
    }
    this->removeChild(manSprite);
    stopGame = true;
    
    this->unschedule(schedule_selector(GameScene::update));
    this->unschedule(schedule_selector(GameScene::generate));
    
    CCLabelTTF *label = CCLabelTTF::create("Game Over", "Marker Felt", 38);
    label->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_WIDTH/2));
    this->addChild(label);
    
    AudioControl::playLionEffect();
    
    FileHelper *file = new FileHelper();
    file->writeScores(score);
    delete file;
}

void GameScene::lionBackEnded()
{
    LionSprite* lion = (LionSprite*)backingLions->objectAtIndex(0);
    lion->setOrientation(FRONT_ORIENTATION);
    backingLions->removeObjectAtIndex(0);
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
    }
}

void GameScene::changeDistinguishedNumber()
{
    if(distinguishNumber>0 && distinguishNumber%10==0) increaseLevel=true; //FIX ME
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

void GameScene::removeBacking(LionSprite *sprite)
{
    for(int i=0; i<backingLions->count(); i++)
    {
        if(sprite->getTag()==((LionSprite*)(backingLions->objectAtIndex(i)))->getTag())
        {
            backingLions->removeObjectAtIndex(i);
            i--;
        }
    }
}

