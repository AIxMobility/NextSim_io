/**
 * STS19 Captain
 * @file : EventArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <gookto_io/EventArr.hpp>
#include <gookto_io/InputEvent.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>

EventArr::EventArr()
{
    TiXmlDocument doc;

    doc.LoadFile("./network_xml/eventdata.xml");
    std::cout << "Loading EventArr" << std::endl;

    if (!doc.LoadFile("./network_xml/eventdata.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "event")
        {
            
            const char* id = elem->Attribute("id");
            const char* link_id = elem->Attribute("link_id");
            const char* pos = elem->Attribute("pos");
            const char* lane = elem->Attribute("lane");
            const char* stime = elem->Attribute("stime");
            const char* etime = elem->Attribute("etime");
            const char* type = elem->Attribute("type");
            const char* sern = elem->Attribute("sern");

            if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!link_id)   throw std::runtime_error ("Element should have 'link_id' attribute");
            if (!pos)   throw std::runtime_error ("Element should have 'pos' attribute");
            if (!lane)   throw std::runtime_error ("Element should have 'lane' attribute");
            if (!stime)   throw std::runtime_error ("Element should have 'stime' attribute");
            if (!etime)   throw std::runtime_error ("Element should have 'etime' attribute");
            if (!type)   type = "1";
            if (!sern)   sern = "1";

            InputEvent demoEvent(
                static_cast<std::size_t>(atoll(id)),
                static_cast<std::size_t>(atoll(link_id)),
                atof(pos),
                atoi(lane),
                atof(stime),
                atof(etime),
                atoi(type),
                atoi(sern));

            Events.push_back(demoEvent);
        }
    }
    doc.Clear();
};