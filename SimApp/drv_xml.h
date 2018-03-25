#ifndef DRV_XML_H
#define DRV_XML_H

#include "pugixml.hpp"
#include <iostream>
#include <string>

using namespace std;

class drv_xml
{

public:
    drv_xml();
    ~drv_xml();

    void init(string fileName);
    pugi::xml_node getRootNode();
    pugi::xml_node findNode(pugi::xml_node root, string Name, string cnt);
    int GetCount(pugi::xml_node root, string Name);
    string GetValue(pugi::xml_node root, string Name, string cnt);
    //QString GetValue(QDomNode root);
    //QString GetAttribute(QDomNode root, QString ab);

    pugi::xml_document doc;
    pugi::xml_node ModelConfig;
};

#endif // DRV_XML_H
