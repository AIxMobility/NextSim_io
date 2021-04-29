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
            std::cout << "Got event" << std::endl;
            InputEvent demoEvent(
                static_cast<std::size_t>(atoll(elem->Attribute("id"))),
                atof(elem->Attribute("pos")),
                atoi(elem->Attribute("lane")),
                atof(elem->Attribute("stime")),
                atof(elem->Attribute("etime")),
                atoi(elem->Attribute("type")),
                atoi(elem->Attribute("sern")));

            Events.push_back(demoEvent);
        }
    }
    doc.Clear();
};