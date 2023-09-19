#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/PTRouteArr.hpp>
#include <gookto_io/InputPTRoute.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

PTRouteArr::PTRouteArr()
{
    parseArr();
}

void PTRouteArr::parseArr(){
    TiXmlDocument doc;

    doc.LoadFile(STSIO::PTRouteXMLPath.string().c_str());
    
    if (!doc.LoadFile(STSIO::PTRouteXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (PTRouteArr)" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for(TiXmlElement *elem = root->FirstChildElement() ; elem != NULL ; elem = elem->NextSiblingElement())
    {
        int id = std::stoi(elem->Attribute("id"));
        int interval = std::stoi(elem->Attribute("interval"));

        TiXmlElement *e = elem->FirstChildElement();
        InputPTRoute tPTRoute = InputPTRoute(id, interval);

        while(e->Value())
        {
            std::string eName = e->Value();
            if (eName == "link")
            {
                std::string linkSeq = e->Attribute("seq");
                tPTRoute.setLinkSeq(linkSeq);
            }
            else if (eName == "node")
            {
                std::string nodeSeq = e->Attribute("seq");
                tPTRoute.setNodeSeq(nodeSeq);
            }
            else if (eName == "station")
            {
                std::string stationSeq = e->Attribute("seq");
                tPTRoute.setStationSeq(stationSeq);
            }
               
            e = e->NextSiblingElement();
        }

        ptrouteArr.push_back(tPTRoute);
    }
}