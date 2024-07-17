/**
 * NextSim Captain
 * @file : MessageArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <gookto_io/MessageArr.hpp>
#include <gookto_io/InputMessage.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

MessageArr::MessageArr()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::V2XXMLPath.string().c_str());
    // std::cout << "Loading Message" << std::endl;

    if (!doc.LoadFile(STSIO::V2XXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (MessageArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
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
                    const char* id = e->Attribute("id");
                    const char* stime = e->Attribute("stime");
                    const char* etime = e->Attribute("etime");
                    const char* msg_type = e->Attribute("msg_type");
                    const char* value = e->Attribute("value");

                    if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!stime)   throw std::runtime_error ("Element should have 'stime' attribute");
                    if (!etime)   throw std::runtime_error ("Element should have 'etime' attribute");
                    if (!msg_type)   throw std::runtime_error ("Element should have 'msg_type' attribute");
                    if (!value)   throw std::runtime_error ("Element should have 'value' attribute");

                    InputMessage demoMessage(
                        std::atoi(id),
                        std::atof(stime),
                        std::atof(etime),
                        std::atoi(msg_type),
                        std::atoi(value));
                        
                    const char* node_id = e->Attribute("node_id");

                    if (!node_id)   throw std::runtime_error ("Element should have 'node_id' attribute");

                    demoMessage.setNode_id (std::atoi(node_id));

                    RegionMessage.push_back (demoMessage);
                }
            }
        }

        else if (elemName == "veh_msgs")
        {
            
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh_msg")
                {
                    const char* id = e->Attribute("id");
                    const char* stime = e->Attribute("stime");
                    const char* etime = e->Attribute("etime");
                    const char* msg_type = e->Attribute("msg_type");
                    const char* value = e->Attribute("value");

                    if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!stime)   throw std::runtime_error ("Element should have 'stime' attribute");
                    if (!etime)   throw std::runtime_error ("Element should have 'etime' attribute");
                    if (!msg_type)   throw std::runtime_error ("Element should have 'msg_type' attribute");
                    if (!value)   throw std::runtime_error ("Element should have 'value' attribute");

                    InputMessage demoMessage(
                        std::atoi(id),
                        std::atof(stime),
                        std::atof(etime),
                        std::atoi(msg_type),
                        std::atoi(value));

                    const char* veh_id = e->Attribute("veh_id");

                    if (!veh_id)   throw std::runtime_error ("Element should have 'veh_id' attribute");

                    demoMessage.setVeh_id (std::atoi(veh_id));

                    VehMessage.push_back (demoMessage);
                }
            }
        }
    }
    doc.Clear();
};