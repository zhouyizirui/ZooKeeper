//
//  GameThread.cpp
//  GameServer
//
//  Created by zhouyizirui on 8/2/14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#include "pre_declaration.h"
GameThread::GameThread(ODSocket * socket)
{
    m_socket = socket;
    m_bStop = false;
}
GameThread::~GameThread()
{
    
}

void *GameThread::start_thread(void * p)
{
    ((GameThread *)p)->run();
    return 0;
    return NULL;
}

int GameThread::start()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    int ret = pthread_create(&m_thread, &attr, start_thread, this);
    pthread_attr_destroy(&attr);
    return ret;
}
int GameThread::stop()
{
    //int ret = pthread_kill(m_thread, SIGINT);
    cout<<"Stop the game thread "<<endl;
    int ret = pthread_cancel(m_thread);
    return ret;
}
int GameThread::join()
{
    int ret = pthread_join(m_thread, NULL);
    return ret;
}
void GameThread::run()
{
    while (m_bStop == false)
    {
        cout<<"The thread is running!"<<endl;
        char recvBuf[8];
        int nRec = m_socket->Recv(recvBuf, 8);
        if(nRec!=0)
        {
            cout<<recvBuf<<endl;
            m_bStop = true;
        }
    }
}