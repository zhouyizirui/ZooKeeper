//
//  SocketThread.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 8/2/14.
//
//

#include "SocketThread.h"
#include "cocos2d.h"
USING_NS_CC;

SocketThread* SocketThread::m_pInstance=new SocketThread;
char SocketThread::data[10];

SocketThread* SocketThread::getInstance(){
	return m_pInstance;
}
void SocketThread::setData(char input[], int length)
{
    memcpy(data, input, length);
}

SocketThread::SocketThread(void)
{
    //memset(data, 0, sizeof(data));
}

SocketThread::~SocketThread(void)
{
	if(m_pInstance!=NULL){
		delete m_pInstance;
	}
}



int SocketThread::start(){
	int errCode = 0;
	do{
		pthread_attr_t tAttr;
		errCode = pthread_attr_init(&tAttr);
		CC_BREAK_IF(errCode!=0); //但是上面这个函数其他内容则主要为你创建的线程设定为分离式
		errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
		if (errCode!=0) {
			pthread_attr_destroy(&tAttr);
			break;
		}
		errCode = pthread_create(&pid,&tAttr,start_thread,this);
	}while (0);
	return errCode;
}

void* SocketThread::start_thread(void *arg)   {
	SocketThread* thred=(SocketThread*)arg;
	ODSocket cdSocket;
	cdSocket.Init();
	if(!cdSocket.Create(AF_INET,SOCK_STREAM,0))
    {
        CCLOG("Create socket error!");
    }
	bool iscon=cdSocket.Connect("127.0.0.1",20000);
	if(iscon){
		thred->state=0;
		//ResPonseThread::GetInstance()->start();// 启动响应参数
		CCLOG("conection established");
        cdSocket.Send(data, 10);
        CCLOG("Message Sent");
	}else{
		thred->state=1;
        CCLOG("Not connected");
	}
	thred->csocket=cdSocket;
	return NULL;
}
ODSocket SocketThread::getSocket(){
	return this->csocket;
}

void SocketThread::stop(){
	pthread_cancel(pid);
	pthread_detach(pid);
}


