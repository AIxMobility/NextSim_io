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

            V2XData v2xData;
            if (scenario.HasMember("v2x") && scenario["v2x"].IsObject())
            {
                const rapidjson::Value& v2x = scenario["v2x"];
                if (v2x.HasMember("mode") && v2x["mode"].IsObject())
                {
                    const rapidjson::Value& mode = v2x["mode"];
                    if (mode.HasMember("v2i")) v2xData.mode.v2i = mode["v2i"].GetBool();
                    if (mode.HasMember("v2v")) v2xData.mode.v2v = mode["v2v"].GetBool();
                }
                if (v2x.HasMember("msg") && v2x["msg"].IsObject())
                {
                    const rapidjson::Value& msg = v2x["msg"];
                    if (msg.HasMember("congestion")) v2xData.msg.congestion = msg["congestion"].GetBool();
                    if (msg.HasMember("danger")) v2xData.msg.danger = msg["danger"].GetBool();
                }
            }

            InputScenario singleScenario(id, startTime, duration, BGTduration, odID, todID, signalControl, std::move(v2xData));
            m_scenarios.emplace_back(singleScenario);
        }
    }
}
} // namespace NextSimIO