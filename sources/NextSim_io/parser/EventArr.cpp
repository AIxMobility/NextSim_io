/**
 * NextSim Captain
 * @file : EventArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <vector>

#include <NextSim_io/parser/EventArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
namespace
{
std::vector<int> ParseLaneVector(const char* laneText)
{
    std::vector<int> laneVector;
    std::stringstream laneStream(laneText);
    int laneID = -1;
    while (laneStream >> laneID)
    {
        laneVector.push_back(laneID);
    }

    if (laneVector.empty())
    {
        throw std::runtime_error("Element should have at least one lane id");
    }

    return laneVector;
}
} // namespace

EventArr::EventArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::EventXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (EventArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "event")
        {
            
            const char* id = elem->Attribute("id");
            const char* link_id = elem->Attribute("linkId");
            const char* startPos = elem->Attribute("startPos");
            const char* endPos = elem->Attribute("endPos");
            const char* lane = elem->Attribute("lane");
            const char* stime = elem->Attribute("stime");
            const char* etime = elem->Attribute("etime");
            const char* type = elem->Attribute("type");
            const char* sern = elem->Attribute("sern");

            if (!link_id) link_id = elem->Attribute("link_id");
            if (!startPos) startPos = elem->Attribute("pos");
            if (!endPos) endPos = startPos;

            if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!link_id)   throw std::runtime_error ("Element should have 'linkId' attribute");
            if (!startPos)   throw std::runtime_error ("Element should have 'startPos' attribute");
            if (!endPos)   throw std::runtime_error ("Element should have 'endPos' attribute");
            if (!lane)   throw std::runtime_error ("Element should have 'lane' attribute");
            if (!stime)   throw std::runtime_error ("Element should have 'stime' attribute");
            if (!etime)   throw std::runtime_error ("Element should have 'etime' attribute");
            if (!type)   type = "1";
            if (!sern)   sern = "1";

            InputEvent demoEvent(
                static_cast<std::size_t>(atoll(id)),
                static_cast<std::size_t>(atoll(link_id)),
                atof(startPos),
                atof(endPos),
                ParseLaneVector(lane),
                atof(stime),
                atof(etime),
                atoi(type),
                atoi(sern));

            m_events.push_back(demoEvent);
        }
    }
    doc.Clear();
};
} // namespace NextSimIO
