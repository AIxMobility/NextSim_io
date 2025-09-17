/**
 * NextSim Captain
 * @file : ScenarioArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

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
            const char *BGTduration = elem->Attribute("BGTduration");
            const char *odID = elem->Attribute("odMatrixID");
            const char *todID = elem->Attribute("todID");
            const char *signalControl = elem->Attribute("signalControl");

            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");
            if (!startTime)
                throw std::runtime_error("Element should have 'startTime' attribute");
            if (!duration)
                throw std::runtime_error("Element should have 'duration' attribute");
            if (!BGTduration)
                throw std::runtime_error("Element should have 'BGTduration' attribute");
            if (!odID)
                throw std::runtime_error("Element should have 'odMatrixID' attribute");
            if (!todID)
                throw std::runtime_error("Element should have 'todID' attribute");
            if (!signalControl)
                throw std::runtime_error("Element should have 'signalControl' attribute");

            bool signalBool = (std::strcmp(signalControl, "1") == 0 ||
                                strcasecmp(signalControl, "true") == 0);
            
            InputScenario singleScenario(
                atoi(id), startTime, atoi(duration), atoi(BGTduration), atoi(odID), atoi(todID), signalBool);

            m_scenarios.emplace_back(singleScenario);
        }
    }

    doc.Clear();
}
} // namespace NextSimIO