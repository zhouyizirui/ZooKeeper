//
//  GameConstant.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/23/14.
//
//

#ifndef ZooKeeper_GameConstant_h
#define ZooKeeper_GameConstant_h


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define FRONT_ACTION 100
#define BACK_ACTION -100
#define FRONT_ORIENTATION 200
#define BACK_ORIENTATION -200
#define LION_FORWARD_SPEED 50
#define LION_BACKWARD_SPEED 100
#define MEET_BACKWARD_SPEED 200
#define PLATE_FORWARD_SPEED 150
#define PLATE_PLACE_X_OFFSET 50
#define PLATE_PLACE_Y_OFFSET 20

float LEVEL_SPEED[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
CCPoint manPositions[4];
CCPoint lionPositions[4];

#endif
