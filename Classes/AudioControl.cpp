//
//  AudioControl.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/24/14.
//
//
#include "pre_declaration.h"


void AudioControl::playLionEffect()
{
    SimpleAudioEngine::sharedEngine()->preloadEffect("lion_horn.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("lion_horn.wav", false);
}

void AudioControl::playPlateEffect()
{
    SimpleAudioEngine::sharedEngine()->preloadEffect("glass.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("glass.wav",false);
}

void AudioControl::playSucessEffect()
{
    SimpleAudioEngine::sharedEngine()->preloadEffect("Ding.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("Ding.wav",false);
}

void AudioControl::playThrowEffect()
{
    SimpleAudioEngine::sharedEngine()->preloadEffect("throw.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("throw.wav", false);
}

void AudioControl::playBackground()
{
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("BackMusic.mp3").c_str());
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.8);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("BackMusic.mp3").c_str(), true);
}

void AudioControl::pauseBackground()
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AudioControl::resumeBackground()
{
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

