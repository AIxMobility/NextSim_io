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

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>

#include <NextSim_io/parser/ScenarioArr.hpp>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ScenarioArr::ScenarioArr()
{
    std::ifstream ifs(NextSimIO::ScenarioJSONPath.string());
    if (!ifs.is_open())
    {
        std::cout << "Loading failed (Scenario JSON): " << NextSimIO::ScenarioJSONPath << std::endl;
        return;
    }

    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    if (doc.HasParseError())
    {
        std::cout << "Parse error (Scenario JSON)" << std::endl;
        return;
    }

    if (doc.HasMember("Scenarios") && doc["Scenarios"].IsArray())
    {
        const rapidjson::Value& scenarios = doc["Scenarios"];
        for (rapidjson::SizeType i = 0; i < scenarios.Size(); i++)
        {
            const rapidjson::Value& scenario = scenarios[i];
            
            int id = scenario["id"].GetInt();
            std::string startTime = scenario["startTime"].GetString();
            int duration = scenario["duration"].GetInt();
            int BGTduration = scenario["BGTduration"].GetInt();
            int odID = scenario["odMatrixID"].GetInt();
            int todID = scenario["todID"].GetInt();
            bool signalControl = scenario["signalControl"].GetBool();

            bool v2xActive = false;
            if (scenario.HasMember("v2x") && scenario["v2x"].IsBool())
                v2xActive = scenario["v2x"].GetBool();

            InputScenario singleScenario(id, startTime, duration, BGTduration, odID, todID, signalControl, v2xActive);
            m_scenarios.emplace_back(singleScenario);
        }
    }
}
} // namespace NextSimIO