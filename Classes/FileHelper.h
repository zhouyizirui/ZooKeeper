//
//  FileHelper.h
//  ZooKeeper
//
//  Created by zhouyizirui on 7/25/14.
//
//

#ifndef __ZooKeeper__FileHelper__
#define __ZooKeeper__FileHelper__

#include <iostream>
#include <vector>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
class FileHelper
{
public:
    FileHelper();
    ~FileHelper();
    //CREATE_FUNC(FileHelper);
    void writeTinyXML(vector<int>& score);
    vector<int> readTinyXML();
    void writeScores(int score);
};

#endif /* defined(__ZooKeeper__FileHelper__) */
