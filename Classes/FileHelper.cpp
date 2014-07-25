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

void FileHelper::writeTinyXML()
{
    TiXmlDocument* myTinyXMLDoc=new TiXmlDocument();//创建文档对象
    
    TiXmlElement* rootElement=new TiXmlElement("Jacky");//创建根节点并连接到文档
    myTinyXMLDoc->LinkEndChild(rootElement);
    
    TiXmlElement* infoElement=new TiXmlElement("Info");//创建info节点并连接到根节点
    rootElement->LinkEndChild(infoElement);
    
    infoElement->SetAttribute("Name","Jacky");//为info节点设置属性
    infoElement->SetAttribute("QQ","754505629");
    infoElement->SetAttribute("E-mail","Geek.Jacky@Gmail.com");
    
    TiXmlElement* blogElement=new TiXmlElement("blog");
    infoElement->LinkEndChild(blogElement);//创建blog节点并连接到info节点
    TiXmlText* blogtext=new TiXmlText("http://blog.csdn.net/jackystudio");
    blogElement->LinkEndChild(blogtext);//为blog节点添加文本值
    
    TiXmlElement* websiteElenment=new TiXmlElement("website");
    infoElement->LinkEndChild(websiteElenment);
    TiXmlText* websitetext=new TiXmlText("http://www.fusijie.com");
    websiteElenment->LinkEndChild(websitetext);
    
    myTinyXMLDoc->SaveFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("testTiny.xml").c_str());//保存xml
    
    delete myTinyXMLDoc;
}

void FileHelper::readTinyXML()
{
    TiXmlDocument* myTinyXMLDoc=new TiXmlDocument(CCFileUtils::sharedFileUtils()->fullPathForFilename("testTiny.xml").c_str());
    myTinyXMLDoc->LoadFile();
    
    TiXmlElement* rootElement = myTinyXMLDoc->RootElement();  //获取根节点
    TiXmlElement* infoElement = rootElement->FirstChildElement();  // 获取Info节点
    
    while (infoElement)
    {
        
        TiXmlAttribute* attributeOfinfo = infoElement->FirstAttribute();  //获得info的属性
        while ( attributeOfinfo )
        {
            CCLOG("%s : %s",attributeOfinfo->Name(),attributeOfinfo->Value());//获取所有属性
            attributeOfinfo = attributeOfinfo->Next();
        }
        
        TiXmlElement* blogElement = infoElement->FirstChildElement();//获得blog
        CCLOG("blog : %s",blogElement->GetText());
        
        TiXmlElement* websiteElement = blogElement->NextSiblingElement();//获取website
        CCLOG("website : %s",websiteElement->GetText());
        
        infoElement = infoElement->NextSiblingElement();//查找下一节点
    }
    delete myTinyXMLDoc;
}



