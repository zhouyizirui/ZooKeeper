//
//  GameServer.cpp
//  GameServer
//
//  Created by zhouyizirui on 8/2/14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#include "pre_declaration.h"
GameServer* GameServer::m_pGameServerInstance = NULL;
GameServer* GameServer::getGameServer()
{
    if(!m_pGameServerInstance)
    {
        m_pGameServerInstance = new GameServer();
    }
    return m_pGameServerInstance;
}

GameServer::GameServer()
:m_isRunning(true)
{
    initServer();
}

GameServer::~GameServer()
{
    
}

void GameServer::initServer()
{
    if(m_pServerSocket.Init())
    {
        cout<<"Init server failed!"<<endl;
    }
    if(!m_pServerSocket.Create(AF_INET, SOCK_STREAM))
    {
        cout<<"Socket create failed!"<<endl;
    }
    if(!m_pServerSocket.Bind(SERVER_PORT))
    {
        cout<<"Bind the server socket failed!"<<endl;
    }
    if(!m_pServerSocket.Listen())
    {
        cout<<"Listen server failed!"<<endl;
    }
}

void GameServer::run()
{
    cout<<"The server is running!"<<endl;
    while(m_isRunning)
    {
        ODSocket * clientSocket = new ODSocket();
        if(!m_pServerSocket.Accept(*clientSocket))
        {
            clientSocket->Close();
            continue;
        }
        else
        {
            GameThread *gameThread = new GameThread(clientSocket);
            gameThread->start();
            cout<<"Accept the connection!"<<endl;
            //gameThread->stop();
        }
    }
}