//
//  GameThread.h
//  GameServer
//
//  Created by zhouyizirui on 8/2/14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#ifndef __GameServer__GameThread__
#define __GameServer__GameThread__

#include <iostream>
class GameThread
{
private:
    ODSocket* m_socket;
    bool m_bStop;
    pthread_t m_thread;
public:
    static void *start_thread(void *p);
    GameThread(ODSocket *socket);
    ~GameThread();
    int start();
    int join();
    int stop();
    void run();
};


#endif /* defined(__GameServer__GameThread__) */
