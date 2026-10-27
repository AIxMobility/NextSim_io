/**
 * NextSim Captain
 * @file : V2XArr.cpp
 * @version : 2.2
 * @author : Elena
 */

#include <NextSim_io/inputclass/InputV2X.hpp>
#include <NextSim_io/parser/V2XArr.hpp>
#include <NextSim_io/FilePath.hpp>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace NextSimIO
{
V2XArr::V2XArr()
    : V2XArr(NextSimIO::V2XConfigJSONPath,
             NextSimIO::GuideConfigJSONPath,
             NextSimIO::GuideScenarioJSONPath)
{
}

V2XArr::V2XArr(const std::filesystem::path& configPath)
    : V2XArr(configPath, std::filesystem::path(), std::filesystem::path())
{
}

V2XArr::V2XArr(const std::filesystem::path& configPath, const std::filesystem::path& guideConfigPath)
    : V2XArr(configPath, guideConfigPath, std::filesystem::path())
{
}

V2XArr::V2XArr(const std::filesystem::path& configPath,
               const std::filesystem::path& guideConfigPath,
               const std::filesystem::path& guideScenarioPath)
{
    InputV2X consolidatedV2X;
    InputV2XConfig config;

    std::ifstream configIfs(configPath.string());
    if (!configIfs.is_open())
    {
        return;
    }

    rapidjson::IStreamWrapper isw(configIfs);
    rapidjson::Document doc;
    doc.ParseStream(isw);
    if (doc.HasParseError())
    {
        return;
    }

    auto readMsgConfig = [](const rapidjson::Value& parent, const char* key, MsgConfig& target) {
        if (!parent.HasMember(key)) return;
        const auto& value = parent[key];
        if (!value.IsObject()) return;
        if (value.HasMember("active")) target.active = value["active"].GetBool();
        if (value.HasMember("interval")) target.interval = value["interval"].GetInt();
    };

    auto readResponseTime = [](const rapidjson::Value& parent,
                               const char* key,
                               InputGuideResponseTimeInfo& target) {
        if (!parent.HasMember(key) || !parent[key].IsObject()) return;
        const auto& value = parent[key];
        if (value.HasMember("dist") && value["dist"].IsString()) target.dist = value["dist"].GetString();
        if (value.HasMember("max") && value["max"].IsNumber()) target.max = value["max"].GetDouble();
        if (value.HasMember("mean") && value["mean"].IsNumber()) target.mean = value["mean"].GetDouble();
        if (value.HasMember("min") && value["min"].IsNumber()) target.min = value["min"].GetDouble();
        if (value.HasMember("sd") && value["sd"].IsNumber()) target.sd = value["sd"].GetDouble();
    };

    auto validResponseTime = [](const InputGuideResponseTimeInfo& info) {
        const bool validDist = info.dist == "Normal" || info.dist == "LogNormal";
        return validDist && info.min >= 0.0 && info.min <= info.mean &&
               info.mean <= info.max && info.sd >= 0.0;
    };

    auto readResponseInfo = [&](const rapidjson::Value& parent,
                                const char* key,
                                InputGuideResponseInfo& target) {
        if (!parent.HasMember(key) || !parent[key].IsObject()) return;
        const auto& value = parent[key];
        if (value.HasMember("complianceRate") && value["complianceRate"].IsNumber())
            target.complianceRate = value["complianceRate"].GetDouble();
        if (value.HasMember("responseTime") && value["responseTime"].IsObject())
        {
            const auto& responseTime = value["responseTime"];
            readResponseTime(responseTime, "Advisory", target.advisoryResponseTime);
            readResponseTime(responseTime, "Mandatory", target.mandatoryResponseTime);
        }
    };

    auto validResponseInfo = [&](const InputGuideResponseInfo& info) {
        return info.complianceRate >= 0.0 && info.complianceRate <= 1.0 &&
               validResponseTime(info.advisoryResponseTime) &&
               validResponseTime(info.mandatoryResponseTime) &&
               info.advisoryResponseTime.min >= info.mandatoryResponseTime.max;
    };

    auto readGuideResponses = [&](const rapidjson::Value& parent) {
        if (!parent.HasMember("GuideResponse") || !parent["GuideResponse"].IsObject()) return;
        const auto& response = parent["GuideResponse"];
        readResponseInfo(response, "HDV", config.guide.hdvResponse);
        readResponseInfo(response, "Auto", config.guide.autoResponse);
        if (!validResponseInfo(config.guide.hdvResponse) ||
            !validResponseInfo(config.guide.autoResponse))
        {
            std::cerr << "[Guide Log][Config] Invalid Guide configuration; Guide is disabled." << std::endl;
            config.guide.active = false;
        }
    };

    auto readIntArray = [](const rapidjson::Value& parent, const char* key) {
        std::vector<int> values;
        if (!parent.HasMember(key) || !parent[key].IsArray()) return values;
        for (const auto& item : parent[key].GetArray())
        {
            if (item.IsInt()) values.push_back(item.GetInt());
        }
        return values;
    };

    auto readGuideScenarios = [&](const rapidjson::Value& parent) {
        if (!parent.HasMember("GuideScenario") || !parent["GuideScenario"].IsArray()) return;
        config.guideScenarios.clear();
        for (const auto& scenario : parent["GuideScenario"].GetArray())
        {
            if (!scenario.IsObject()) continue;

            InputGuideScenarioInfo info;
            if (scenario.HasMember("id") && scenario["id"].IsInt()) info.id = scenario["id"].GetInt();
            if (scenario.HasMember("active") && scenario["active"].IsBool()) info.active = scenario["active"].GetBool();
            if (scenario.HasMember("type") && scenario["type"].IsString()) info.type = scenario["type"].GetString();
            if (scenario.HasMember("action") && scenario["action"].IsString()) info.action = scenario["action"].GetString();
            if (scenario.HasMember("targetLane") && scenario["targetLane"].IsInt()) info.targetLane = scenario["targetLane"].GetInt();
            if (scenario.HasMember("targetSpeed") && scenario["targetSpeed"].IsNumber()) info.targetSpeed = scenario["targetSpeed"].GetDouble();
            if (scenario.HasMember("startTime") && scenario["startTime"].IsNumber()) info.startTime = scenario["startTime"].GetDouble();
            if (scenario.HasMember("endTime") && scenario["endTime"].IsNumber()) info.endTime = scenario["endTime"].GetDouble();
            if (scenario.HasMember("repeatInterval") && scenario["repeatInterval"].IsNumber()) info.repeatInterval = scenario["repeatInterval"].GetDouble();

            if (scenario.HasMember("target") && scenario["target"].IsObject())
            {
                const auto& target = scenario["target"];
                info.target.link = readIntArray(target, "link");
                info.target.lane = readIntArray(target, "lane");
                if (target.HasMember("startPos") && target["startPos"].IsNumber()) info.target.startPos = target["startPos"].GetDouble();
                if (target.HasMember("endPos") && target["endPos"].IsNumber()) info.target.endPos = target["endPos"].GetDouble();
                if (target.HasMember("upstreamDistance") && target["upstreamDistance"].IsNumber()) info.target.upstreamDistance = target["upstreamDistance"].GetDouble();
            }

            const bool validType = info.type == "Advisory" || info.type == "Mandatory";
            const bool validAction = info.action == "Speed" || info.action == "LaneChange";
            const bool validValues = info.id > 0 &&
                                     (info.action != "LaneChange" ||
                                      (info.targetLane >= 0 && !info.target.link.empty() &&
                                       !info.target.lane.empty() &&
                                       std::find(info.target.lane.begin(), info.target.lane.end(),
                                                 info.targetLane) == info.target.lane.end())) &&
                                     info.targetSpeed >= 0.0 &&
                                     info.startTime >= 0.0 &&
                                     info.endTime >= info.startTime &&
                                     info.repeatInterval >= 0.0 &&
                                     info.target.startPos >= 0.0 &&
                                     info.target.endPos >= info.target.startPos &&
                                     info.target.upstreamDistance >= 0.0;
            if (!validType || !validAction || !validValues)
            {
                std::cerr << "[Guide Log][Config] Invalid GuideScenario ignored." << std::endl;
                continue;
            }

            config.guideScenarios.push_back(info);
        }
    };

    auto readGuide = [&](const rapidjson::Value& guide) {
        if (guide.HasMember("active") && guide["active"].IsBool()) config.guide.active = guide["active"].GetBool();
        if (guide.HasMember("type") && guide["type"].IsString()) config.guide.type = guide["type"].GetString();
        if (guide.HasMember("targetSpeed") && guide["targetSpeed"].IsNumber()) config.guide.targetSpeed = guide["targetSpeed"].GetDouble();
        if (guide.HasMember("complianceRate") && guide["complianceRate"].IsNumber()) config.guide.complianceRate = guide["complianceRate"].GetDouble();
        if (guide.HasMember("randomSeed") && guide["randomSeed"].IsUint()) config.guide.randomSeed = guide["randomSeed"].GetUint();
        if (guide.HasMember("responseTime") && guide["responseTime"].IsObject())
        {
            const auto& responseTime = guide["responseTime"];
            readResponseTime(responseTime, "Advisory", config.guide.advisoryResponseTime);
            readResponseTime(responseTime, "Mandatory", config.guide.mandatoryResponseTime);
        }
        config.guide.hdvResponse.complianceRate = config.guide.complianceRate;
        config.guide.hdvResponse.advisoryResponseTime = config.guide.advisoryResponseTime;
        config.guide.hdvResponse.mandatoryResponseTime = config.guide.mandatoryResponseTime;
        readGuideResponses(guide);

        const bool validType = config.guide.type == "Advisory" || config.guide.type == "Mandatory";
        const bool validValues = config.guide.targetSpeed >= 0.0 &&
                                 config.guide.complianceRate >= 0.0 && config.guide.complianceRate <= 1.0;
        const bool validResponse = validResponseTime(config.guide.advisoryResponseTime) &&
                                   validResponseTime(config.guide.mandatoryResponseTime) &&
                                   config.guide.advisoryResponseTime.min >= config.guide.mandatoryResponseTime.max &&
                                   validResponseInfo(config.guide.hdvResponse) &&
                                   validResponseInfo(config.guide.autoResponse);
        if (!validType || !validValues || !validResponse)
        {
            std::cerr << "[Guide Log][Config] Invalid Guide configuration; Guide is disabled." << std::endl;
            config.guide.active = false;
        }
    };

    if (doc.HasMember("V2XConfig") && doc["V2XConfig"].IsObject())
    {
        const rapidjson::Value& v2xConfig = doc["V2XConfig"];
        if (v2xConfig.HasMember("V2IRange")) config.v2iRange = v2xConfig["V2IRange"].GetDouble();
        readMsgConfig(v2xConfig, "V2XDebugLog", config.debugLog);
    }

    if (doc.HasMember("V2XMessage") && doc["V2XMessage"].IsObject())
    {
        const rapidjson::Value& msg = doc["V2XMessage"];
        readMsgConfig(msg, "Position", config.position);
        readMsgConfig(msg, "TrafficInfo", config.trafficInfo);
        readMsgConfig(msg, "Signal", config.signal);
        readMsgConfig(msg, "RoadEvent", config.roadEvent);
        readMsgConfig(msg, "SpeedLimit", config.speedLimit);
        if (msg.HasMember("CollisionWarn") && msg["CollisionWarn"].IsObject())
        {
            const auto& collisionWarn = msg["CollisionWarn"];
            if (collisionWarn.HasMember("active")) config.collisionWarn.active = collisionWarn["active"].GetBool();
            if (collisionWarn.HasMember("range") && collisionWarn["range"].IsObject())
            {
                const auto& range = collisionWarn["range"];
                if (range.HasMember("straight")) config.collisionWarn.straightRange = range["straight"].GetDouble();
                if (range.HasMember("rtor")) config.collisionWarn.rtorRange = range["rtor"].GetDouble();
            }
            if (collisionWarn.HasMember("DRACThreshold")) config.collisionWarn.DRACThreshold = collisionWarn["DRACThreshold"].GetDouble();
            if (collisionWarn.HasMember("interval")) config.collisionWarn.interval = collisionWarn["interval"].GetInt();
        }

        if (msg.HasMember("Guide") && msg["Guide"].IsObject())
            readGuide(msg["Guide"]);
        readGuideResponses(msg);
        readGuideScenarios(msg);
    }

    if (!guideConfigPath.empty())
    {
        std::ifstream guideIfs(guideConfigPath.string());
        if (guideIfs.is_open())
        {
            rapidjson::IStreamWrapper guideIsw(guideIfs);
            rapidjson::Document guideDoc;
            guideDoc.ParseStream(guideIsw);
            if (!guideDoc.HasParseError())
            {
                if (guideDoc.HasMember("Guide") && guideDoc["Guide"].IsObject())
                    readGuide(guideDoc["Guide"]);
                readGuideResponses(guideDoc);
                readGuideScenarios(guideDoc);
            }
        }
    }

    if (!guideScenarioPath.empty())
    {
        std::ifstream guideScenarioIfs(guideScenarioPath.string());
        if (guideScenarioIfs.is_open())
        {
            rapidjson::IStreamWrapper guideScenarioIsw(guideScenarioIfs);
            rapidjson::Document guideScenarioDoc;
            guideScenarioDoc.ParseStream(guideScenarioIsw);
            if (guideScenarioDoc.HasParseError() || !guideScenarioDoc.IsObject() ||
                !guideScenarioDoc.HasMember("GuideScenario") ||
                !guideScenarioDoc["GuideScenario"].IsArray())
            {
                std::cerr << "[Guide Log][Config] Invalid Guide scenario file; Guide is disabled." << std::endl;
                config.guide.active = false;
                config.guideScenarios.clear();
            }
            else
            {
                readGuideScenarios(guideScenarioDoc);
            }
        }
    }

    consolidatedV2X.SetConfig(config);
    m_v2xs.push_back(consolidatedV2X);
}
} // namespace NextSimIO
