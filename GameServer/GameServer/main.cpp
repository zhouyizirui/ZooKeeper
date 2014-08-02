//
//  main.cpp
//  GameServer
//
//  Created by zhouyizirui on 8/2/14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#include <iostream>
#include "pre_declaration.h"
int main(int argc, const char * argv[])
{
    // insert code here...
    GameServer::getGameServer()->run();
    //std::cout << "Hello, World!\n";
    return 0;
}

