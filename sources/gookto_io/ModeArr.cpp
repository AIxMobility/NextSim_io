#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/ModeArr.hpp>
#include <gookto_io/Mode.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>

ModeArr::ModeArr()
{
    parseArr();
}

void ModeArr::parseArr(){
    TiXmlDocument doc;

    doc.LoadFile("./network_xml/mode.xml");
    std::cout << "Loading AgentsArr" << std::endl;
    if (!doc.LoadFile("./network_xml/mode.xml")) return;

    TiXmlElement *root = doc.FirstChildElement();

    for(TiXmlElement *elem = root->FirstChildElement() ; elem != NULL ; elem = elem->NextSiblingElement())
    {
        int id = std::stoi(elem->Attribute("id"));
        int scycle = std::stoi(elem->Attribute("scycle"));

        if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
        if (!scycle)   throw std::runtime_error ("Element should have 'scycle' attribute");

        TiXmlElement *e = elem->FirstChildElement();
        Mode tMode = Mode(id, scycle);

        std::string microArr = e->Attribute("linkid");
        tMode.setMicroLinkArr(microArr);
        e = e->NextSiblingElement();
        std::string mesoArr = e->Attribute("linkid");
        tMode.setMesoLinkArr(mesoArr);

        modeArr.push_back(tMode);
    }
}