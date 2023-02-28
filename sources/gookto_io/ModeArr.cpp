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
    std::cout << "Loading ModeArr" << std::endl;
    if (!doc.LoadFile("./network_xml/mode.xml")) return;

    TiXmlElement *root = doc.FirstChildElement();

    for(TiXmlElement *elem = root->FirstChildElement() ; elem != NULL ; elem = elem->NextSiblingElement())
    {
        int id = std::stoi(elem->Attribute("id"));
        int scycle = std::stoi(elem->Attribute("scycle"));

        TiXmlElement *e = elem->FirstChildElement();
        Mode tMode = Mode(id, scycle);

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