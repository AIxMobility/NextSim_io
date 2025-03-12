/**
 * NextSim Captain
 * @file : ScenarioArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <iostream>
#include <sstream>
#include <string>

#include <NextSim_io/parser/ScenarioArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ScenarioArr::ScenarioArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::ScenarioXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (Scenario)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "Scenario")
        {
            const char *id = elem->Attribute("id");
            const char *startTime = elem->Attribute("startTime");
            const char *duration = elem->Attribute("duration");
            const char *odID = elem->Attribute("odMatrixID");
            const char *todID = elem->Attribute("todID");

            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");
            if (!startTime)
                throw std::runtime_error("Element should have 'startTime' attribute");
            if (!duration)
                throw std::runtime_error("Element should have 'duration' attribute");
            if (!odID)
                throw std::runtime_error("Element should have 'odMatrixID' attribute");
            if (!todID)
                throw std::runtime_error("Element should have 'todID' attribute");
            
            InputScenario singleScenario(
                atoi(id), startTime, atoi(duration), atoi(odID), atoi(todID));

            m_scenarios.emplace_back(singleScenario);
        }
    }

    doc.Clear();
}
} // namespace NextSimIO