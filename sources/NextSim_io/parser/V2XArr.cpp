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
#include <fstream>
#include <iostream>

namespace NextSimIO
{
V2XArr::V2XArr()
    : V2XArr(NextSimIO::V2XConfigJSONPath, NextSimIO::GuideConfigJSONPath)
{
}

V2XArr::V2XArr(const std::filesystem::path& configPath)
    : V2XArr(configPath, std::filesystem::path())
{
}

V2XArr::V2XArr(const std::filesystem::path& configPath, const std::filesystem::path& guideConfigPath)
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

    auto readGuideConfig = [&](const rapidjson::Value& parent) {
        if (parent.HasMember("GuideDebugLog") && parent["GuideDebugLog"].IsObject())
            readMsgConfig(parent, "GuideDebugLog", config.guide.debugLog);
    };

    auto readGuide = [&](const rapidjson::Value& guide) {
        if (guide.HasMember("active") && guide["active"].IsBool()) config.guide.active = guide["active"].GetBool();
        if (guide.HasMember("type") && guide["type"].IsString()) config.guide.type = guide["type"].GetString();
        if (guide.HasMember("targetSpeed") && guide["targetSpeed"].IsNumber()) config.guide.targetSpeed = guide["targetSpeed"].GetDouble();
        if (guide.HasMember("complianceRate") && guide["complianceRate"].IsNumber()) config.guide.complianceRate = guide["complianceRate"].GetDouble();
        if (guide.HasMember("randomSeed") && guide["randomSeed"].IsUint()) config.guide.randomSeed = guide["randomSeed"].GetUint();
        if (guide.HasMember("responseGain") && guide["responseGain"].IsNumber()) config.guide.responseGain = guide["responseGain"].GetDouble();
        if (guide.HasMember("maxAcceleration") && guide["maxAcceleration"].IsNumber()) config.guide.maxAcceleration = guide["maxAcceleration"].GetDouble();
        if (guide.HasMember("maxDeceleration") && guide["maxDeceleration"].IsNumber()) config.guide.maxDeceleration = guide["maxDeceleration"].GetDouble();
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
                                 config.guide.complianceRate >= 0.0 && config.guide.complianceRate <= 1.0 &&
                                 config.guide.responseGain >= 0.0 &&
                                 config.guide.maxAcceleration > 0.0 && config.guide.maxDeceleration > 0.0;
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
                if (guideDoc.HasMember("GuideConfig") && guideDoc["GuideConfig"].IsObject())
                    readGuideConfig(guideDoc["GuideConfig"]);
                if (guideDoc.HasMember("Guide") && guideDoc["Guide"].IsObject())
                    readGuide(guideDoc["Guide"]);
                readGuideResponses(guideDoc);
            }
        }
    }

    consolidatedV2X.SetConfig(config);
    m_v2xs.push_back(consolidatedV2X);
}
} // namespace NextSimIO
