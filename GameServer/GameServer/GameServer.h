//
//  GameServer.h
//  GameServer
//
//  Created by zhouyizirui on 8/2/14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#ifndef __GameServer__GameServer__
#define __GameServer__GameServer__

#include <iostream>
//class GameThread;
class GameServer
{
private:
    ODSocket m_pServerSocket;
    //GameThread gameThread;
    bool m_isRunning;
    static GameServer* m_pGameServerInstance;
public:
    static GameServer* getGameServer();
    GameServer();
    ~GameServer();
    
    void initServer();
    void run();
};

#endif /* defined(__GameServer__GameServer__) */
