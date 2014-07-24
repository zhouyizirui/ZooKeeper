//
//  AudioControl.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/24/14.
//
//

#ifndef __ZooKeeper__AudioControl__
#define __ZooKeeper__AudioControl__

USING_NS_CC;
USING_NS_CC_EXT;
class AudioControl
{
public:
    static void playLionEffect();
    static void playBackground();
    static void pauseBackground();
    static void resumeBackground();
    static void playPlateEffect();
    static void playSucessEffect();
    static void playThrowEffect();
};


#endif /* defined(__ZooKeeper__AudioControl__) */
