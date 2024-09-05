#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <NextSim_io/PTlineArr.hpp>
#include <NextSim_io/InputPTline.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
PTlineArr::PTlineArr()
{
    parseArr();
}

void PTlineArr::parseArr(){
    TiXmlDocument doc;

    doc.LoadFile(NextSimIO::PTlineXMLPath.string().c_str());
    
    if (!doc.LoadFile(NextSimIO::PTlineXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (PTLineArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
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
} // namespace NextSimIO