#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/PTlineArr.hpp>
#include <gookto_io/InputPTline.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

PTlineArr::PTlineArr()
{
    parseArr();
}

void PTlineArr::parseArr(){
    TiXmlDocument doc;

    doc.LoadFile(STSIO::PTlineXMLPath.string().c_str());
    
    if (!doc.LoadFile(STSIO::PTlineXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (PTlineArr)" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for(TiXmlElement *elem = root->FirstChildElement() ; elem != NULL ; elem = elem->NextSiblingElement())
    {
        int id = std::stoi(elem->Attribute("id"));
        int interval = std::stoi(elem->Attribute("interval"));

        TiXmlElement *e = elem->FirstChildElement();
        InputPTline tPTline = InputPTline(id, interval);

        std::string eName = e->Value();
        if (eName == "link")
        {
            std::string linkSeq = e->Attribute("seq");
            tPTline.setLinkSeq(linkSeq);
        }
        
        e = e->NextSiblingElement();
        eName = e->Value();
        if (eName == "node")
        {
            std::string nodeSeq = e->Attribute("seq");
            tPTline.setNodeSeq(nodeSeq);
        }
        
        e = e->NextSiblingElement();
        eName = e->Value();
        if (eName == "station")
        {
            std::string stationSeq = e->Attribute("seq");
            tPTline.setStationSeq(stationSeq);

            std::string stationDistanceSeq = e->Attribute("distance");
            tPTline.setStationDistanceSeq(stationDistanceSeq);
        }
        
        ptlineArr.push_back(tPTline);
    }
}