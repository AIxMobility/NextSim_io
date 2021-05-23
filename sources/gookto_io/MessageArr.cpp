#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <gookto_io/MessageArr.hpp>
#include <gookto_io/InputMessage.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>

MessageArr::MessageArr()
{
    TiXmlDocument doc;

    doc.LoadFile("./network_xml/message.xml");
    std::cout << "Loading Message" << std::endl;

    if (!doc.LoadFile("./network_xml/message.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "region_msgs")
        {
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "region_msg")
                {
                    InputMessage demoMessage(
                        std::atoi(e->Attribute("id")),
                        std::atoi(e->Attribute("stime")),
                        std::atoi(e->Attribute("etime")),
                        std::atoi(e->Attribute("msg_type")),
                        std::atoi(e->Attribute("value")));

                    demoMessage.setNode_id (std::atoi(e->Attribute("node_id")));

                    RegionMessage.push_back (demoMessage);
                }
            }
        }

        if (elemName == "veh_msgs")
        {
            
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh_msg")
                {
                    InputMessage demoMessage(
                    std::atoi(e->Attribute("id")),
                    std::atoi(e->Attribute("stime")),
                    std::atoi(e->Attribute("etime")),
                    std::atoi(e->Attribute("msg_type")),
                    std::atoi(e->Attribute("value")));

                    demoMessage.setVeh_id (std::atoi(e->Attribute("veh_id")));

                    VehMessage.push_back (demoMessage);
                }
            }
        }
    }
    doc.Clear();
};