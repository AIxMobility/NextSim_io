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
            InputTMC tmc;
            if (scenario.HasMember("trafficCenter") && scenario["trafficCenter"].IsObject())
            {
                const rapidjson::Value& tc = scenario["trafficCenter"];
                if (tc.HasMember("signalControl") && tc["signalControl"].IsObject())
                {
                    const rapidjson::Value& sc = tc["signalControl"];
                    bool active = false;
                    double interval = 1.0;
                    if (sc.HasMember("active") && sc["active"].IsBool()) 
                        active = sc["active"].GetBool();
                    if (sc.HasMember("interval") && sc["interval"].IsNumber())
                        interval = sc["interval"].GetDouble();
                    else if (sc.HasMember("timeStep") && sc["timeStep"].IsNumber())
                        interval = sc["timeStep"].GetDouble();
                    tmc.SetSignalTMCInfo(active, interval);
                }
            }
            // Fallback for older formats if needed, or just use defaults
            InputScenario singleScenario(
                id,
                startTime,
                duration,
                BGTduration,
                odID,
                todID,
                tmc);
            m_scenarios.emplace_back(singleScenario);
        }
    }
}
} // namespace NextSimIO
