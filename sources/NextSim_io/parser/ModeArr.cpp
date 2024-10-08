/**
 * NextSim Captain
 * @file : ModeArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <NextSim_io/parser/ModeArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ModeArr::ModeArr()
{    
    TiXmlDocument doc;

    doc.LoadFile(NextSimIO::ModeXMLPath.string().c_str());
    // std::cout << "Loading ModeArr" << std::endl;
    
    if (!doc.LoadFile(NextSimIO::ModeXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (ModeArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for(TiXmlElement *elem = root->FirstChildElement() ; elem != NULL ; elem = elem->NextSiblingElement())
    {
        int id = std::stoi(elem->Attribute("id"));
        int scycle = std::stoi(elem->Attribute("scycle"));

        TiXmlElement *e = elem->FirstChildElement();
        InputMode tMode = InputMode(id, scycle);

        bool getMicro = false;
        bool getMeso = false;

        while(e->Value())
        {
            std::string eName = e->Value();
            if (eName == "micro")
            {
                std::string microArr = e->Attribute("linkid");
                tMode.setMicroLinkArr(microArr);
                getMicro = true;
            }
            else if (eName == "meso")
            {
                std::string mesoArr = e->Attribute("linkid");
                tMode.setMesoLinkArr(mesoArr);
                getMeso = true;
            }

            if (getMicro && getMeso)
                break;
                
            e = e->NextSiblingElement();
        }

        modeArr.push_back(tMode);
    }
}
} // namespace NextSimIO