//
//  FileHelper.cpp
//  ZooKeeper
//
//  Created by zhouyizirui on 7/25/14.
//
//
#include "pre_declaration.h"

FileHelper::FileHelper()
{

}

FileHelper::~FileHelper()
{
    
}

void FileHelper::writeScores(int score)
{
    int i;
    CCLOG("First, we should read the xml");
    vector<int> highScores = readTinyXML();
    for(i=0; i<highScores.size(); i++)
    {
        if(score>highScores[i]) break;
    }
    if(i==highScores.size()) return;
    else
    {
        highScores.insert(highScores.begin()+i, score);
        highScores.pop_back();
        CCLOG("Then, write it");
        writeTinyXML(highScores);
    }
}

void FileHelper::writeTinyXML(vector<int>& score)
{
    char scores[10];
    memset(scores, 0, 10);
    TiXmlDocument* myTinyXMLDoc=new TiXmlDocument();//创建文档对象
    
    TiXmlElement* rootElement=new TiXmlElement("Grief");//创建根节点并连接到文档
    myTinyXMLDoc->LinkEndChild(rootElement);
    
    TiXmlElement* infoElement=new TiXmlElement("Info");//创建info节点并连接到根节点
    rootElement->LinkEndChild(infoElement);
    
    infoElement->SetAttribute("Name","Scores");//为info节点设置属性
    
    TiXmlElement* rank1Element=new TiXmlElement("Rank1");
    infoElement->LinkEndChild(rank1Element);//创建blog节点并连接到info节点
    sprintf(scores, "%d", score[0]);
    TiXmlText* score1Text=new TiXmlText(scores);
    rank1Element->LinkEndChild(score1Text);//为blog节点添加文本值
    
    TiXmlElement* rank2Element=new TiXmlElement("Rank2");
    infoElement->LinkEndChild(rank2Element);
    memset(scores, 0, 10);
    sprintf(scores, "%d", score[1]);
    TiXmlText* score2Text=new TiXmlText(scores);
    rank2Element->LinkEndChild(score2Text);
    
    TiXmlElement* rank3Element=new TiXmlElement("Rank3");
    infoElement->LinkEndChild(rank3Element);
    memset(scores, 0, 10);
    sprintf(scores, "%d", score[2]);
    TiXmlText* score3Text=new TiXmlText(scores);
    rank3Element->LinkEndChild(score3Text);
    
    //myTinyXMLDoc->SaveFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("HighScores.xml").c_str());//保存xml
    
    myTinyXMLDoc->SaveFile((CCFileUtils::sharedFileUtils()->getWritablePath() + "HighScores.xml").c_str());
    CCLOG("%s", (CCFileUtils::sharedFileUtils()->getWritablePath() + "HighScores.xml").c_str());
    delete myTinyXMLDoc;
}

vector<int> FileHelper::readTinyXML()
{
    /*
    TiXmlDocument* myTinyXMLDoc=new TiXmlDocument(CCFileUtils::sharedFileUtils()->fullPathForFilename("HighScores.xml").c_str());
    myTinyXMLDoc->LoadFile();
    */
    unsigned long size;
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "HighScores.xml";
    //char *pFileContent = (char*)(CCFileUtils::sharedFileUtils()->getFileData("HighScores.xml", "r+", &size));
    char *pFileContent = (char*)(CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r+", &size));
    TiXmlDocument *xmlDoc = new TiXmlDocument();
    xmlDoc->Parse(pFileContent, 0, TIXML_ENCODING_UTF8);
    
    //TiXmlElement* rootElement = myTinyXMLDoc->RootElement();  //获取根节点
    TiXmlElement* rootElement = xmlDoc->RootElement();
    TiXmlElement* infoElement = rootElement->FirstChildElement();  // 获取Info节点
    
    vector<int> highScores;
    
    while (infoElement)
    {
        TiXmlAttribute* attributeOfinfo = infoElement->FirstAttribute();  //获得info的属性
        while ( attributeOfinfo )
        {
            CCLOG("%s : %s",attributeOfinfo->Name(),attributeOfinfo->Value());//获取所有属性
            attributeOfinfo = attributeOfinfo->Next();
        }
        
        TiXmlElement* rank1Element = infoElement->FirstChildElement();//获得rank1
        CCLOG("Rank1 : %s",rank1Element->GetText());
        highScores.push_back(atoi(rank1Element->GetText()));
        
        TiXmlElement* rank2Element = rank1Element->NextSiblingElement();
        CCLOG("Rank2 : %s",rank2Element->GetText());
        highScores.push_back(atoi(rank2Element->GetText()));
        
        TiXmlElement* rank3Element = rank2Element->NextSiblingElement();
        CCLOG("Rank3 : %s",rank3Element->GetText());
        highScores.push_back(atoi(rank3Element->GetText()));
        
        infoElement = infoElement->NextSiblingElement();//查找下一节点
    }
    //delete myTinyXMLDoc;
    delete xmlDoc;
    return highScores;
}



