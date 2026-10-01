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

namespace NextSimIO
{
V2XArr::V2XArr()
{
    InputV2X consolidatedV2X;
    InputV2XConfig config;

    std::ifstream configIfs(NextSimIO::V2XConfigJSONPath.string());
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
    }

    consolidatedV2X.SetConfig(config);
    m_v2xs.push_back(consolidatedV2X);
}
} // namespace NextSimIO
