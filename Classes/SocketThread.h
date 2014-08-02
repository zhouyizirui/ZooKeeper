//
//  SocketThread.h
//  Thenet
//
//  Created by zhouyizirui on 8/2/14.
//
//

#ifndef __Thenet__SocketThread__
#define __Thenet__SocketThread__

#include <iostream>
#include "ODSocket.h"
#include <pthread.h>
class SocketThread
{
public:
    ~SocketThread();
    static SocketThread* getInstance();
    ODSocket getSocket();
    int state;
    int start();
    ODSocket csocket;
    void stop();
    static void setData(char input[], int length);
private:
    pthread_t pid;
    static void* start_thread(void *);
    SocketThread();
    static SocketThread* m_pInstance;
    static char data[10];
};


#endif /* defined(__Thenet__SocketThread__) */
