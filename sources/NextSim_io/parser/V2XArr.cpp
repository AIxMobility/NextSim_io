/**
 * NextSim Captain
 * @file : V2XArr.cpp
 * @version : 2.1
 * @author : Elena
 */

#include <vector>
#include <algorithm>
#include <NextSim_io/inputclass/InputV2X.hpp>
#include <NextSim_io/parser/V2XArr.hpp>
#include <NextSim_io/FilePath.hpp>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <fstream>
#include <iostream>

namespace NextSimIO
{
V2XArr::V2XArr()
{
    InputV2X consolidatedV2X;
    InputV2XConfig config;
    bool hasV2XInput = false;

    // 1. Load config_v2x.json
    std::ifstream configIfs(NextSimIO::V2XConfigJSONPath.string());
    if (configIfs.is_open())
    {
        hasV2XInput = true;
        rapidjson::IStreamWrapper isw(configIfs);
        rapidjson::Document doc;
        doc.ParseStream(isw);

        if (!doc.HasParseError())
        {
            auto readMsgConfig = [](const rapidjson::Value& parent,
                                     const char* key,
                                     MsgConfig& target) {
                if (!parent.HasMember(key)) return;
                const auto& value = parent[key];
                if (!value.IsObject()) return;
                if (value.HasMember("active")) target.active = value["active"].GetBool();
                if (value.HasMember("interval")) target.interval = value["interval"].GetInt();
            };

            auto readMsgConfigTime = [](const rapidjson::Value& parent,
                                         const char* key,
                                         MsgConfigTime& target) {
                if (!parent.HasMember(key)) return;
                const auto& value = parent[key];
                if (!value.IsObject()) return;
                if (value.HasMember("active")) target.active = value["active"].GetBool();
                if (value.HasMember("interval")) target.interval = value["interval"].GetInt();
                if (value.HasMember("startTime")) target.startTime = value["startTime"].GetString();
                if (value.HasMember("duration")) target.duration = value["duration"].GetInt();
            };

            // 1.1 Load V2XConfig
            if (doc.HasMember("V2XConfig") && doc["V2XConfig"].IsObject())
            {
                const rapidjson::Value& v2xConfig = doc["V2XConfig"];
                if (v2xConfig.HasMember("V2IRange")) config.v2iRange = v2xConfig["V2IRange"].GetDouble();
                readMsgConfig(v2xConfig, "V2XDebugLog", config.debugLog);
            }

            // 1.2 Load V2XMessage
            if (doc.HasMember("V2XMessage") && doc["V2XMessage"].IsObject())
            {
                const rapidjson::Value& msg = doc["V2XMessage"];
                readMsgConfig(msg, "Position", config.position);
                readMsgConfig(msg, "TrafficInfo", config.trafficInfo);
                readMsgConfig(msg, "Signal", config.signal);
                readMsgConfig(msg, "RoadEvent", config.roadEvent);
                readMsgConfigTime(msg, "SchoolZone", config.schoolZone);
                readMsgConfigTime(msg, "SpeedLimit", config.speedLimit);
                if (msg.HasMember("CollisionWarn")) {
                    if (msg["CollisionWarn"].IsObject()) {
                        const auto& collisionWarn = msg["CollisionWarn"];
                        if (collisionWarn.HasMember("active")) config.collisionWarn.active = collisionWarn["active"].GetBool();
                        if (collisionWarn.HasMember("range") && collisionWarn["range"].IsObject()) {
                            const auto& range = collisionWarn["range"];
                            if (range.HasMember("straight")) {
                                config.collisionWarn.straightRange = range["straight"].GetDouble();
                            }
                            if (range.HasMember("rtor")) {
                                config.collisionWarn.rtorRange = range["rtor"].GetDouble();
                            }
                        }
                        if (collisionWarn.HasMember("DRACThreshold")) {
                            config.collisionWarn.DRACThreshold = collisionWarn["DRACThreshold"].GetDouble();
                        }
                        if (collisionWarn.HasMember("interval")) {
                            config.collisionWarn.interval = collisionWarn["interval"].GetInt();
                        }
                    }
                }
            }
        }
        consolidatedV2X.SetConfig(config);
    }

    // 2. Load event_v2x.xml
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::V2XEventXMLPath.string().c_str());

    if (loadSuccess)
    {
        hasV2XInput = true;
        TiXmlElement *root = doc.FirstChildElement();
        if (root)
        {
            for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
                 elem = elem->NextSiblingElement())
            {
                std::string elemName = elem->Value();
                if (elemName == "event")
                {
                    InputV2XEvent eventData;

                    const char* linkId = elem->Attribute("linkId");
                    const char* lane = elem->Attribute("lane");
                    const char* startPos = elem->Attribute("startPos");
                    const char* endPos = elem->Attribute("endPos");
                    const char* stime = elem->Attribute("stime");
                    const char* etime = elem->Attribute("etime");
                    const char* type = elem->Attribute("type");
                    const char* speedLimit = elem->Attribute("speedLimit");
                    const char* detail = elem->Attribute("detail");

                    if (linkId) eventData.linkId = atoi(linkId);
                    if (lane) eventData.laneIds.push_back(atoi(lane));
                    else eventData.laneIds.push_back(-1);
                    if (startPos) eventData.startPos = atof(startPos);
                    if (endPos) eventData.endPos = atof(endPos);
                    if (stime) eventData.startTime = atof(stime);
                    if (etime) eventData.endTime = atof(etime);

                    if (type)
                    {
                        std::string typeStr(type);
                        if (typeStr == "Position") eventData.msgType = ToInt(InputV2XMsgType::Position);
                        else if (typeStr == "TrafficInfo") eventData.msgType = ToInt(InputV2XMsgType::TrafficInfo);
                        else if (typeStr == "Signal") eventData.msgType = ToInt(InputV2XMsgType::Signal);
                        else if (typeStr == "RoadEvent") eventData.msgType = ToInt(InputV2XMsgType::RoadEvent);
                        else if (typeStr == "SchoolZone") eventData.msgType = ToInt(InputV2XMsgType::SchoolZone);
                        else if (typeStr == "SpeedLimit") eventData.msgType = ToInt(InputV2XMsgType::SpeedLimit);
                        else if (typeStr == "CollisionWarn") eventData.msgType = ToInt(InputV2XMsgType::CollisionWarn);
                        else eventData.msgType = atoi(type);
                    }

                    if (speedLimit) eventData.speedLimit = atof(speedLimit);
                    if (detail) eventData.eventDetail = detail;

                    consolidatedV2X.AddEvent(eventData);
                }
            }
        }
    }

    // 3. Load network_v2x.xml
    TiXmlDocument netDoc;
    bool netLoadSuccess = netDoc.LoadFile(NextSimIO::V2XNetworkXMLPath.string().c_str());
    if (netLoadSuccess)
    {
        hasV2XInput = true;
        TiXmlElement *root = netDoc.FirstChildElement();
        if (root)
        {
            for (TiXmlElement *category = root->FirstChildElement(); category != nullptr;
                 category = category->NextSiblingElement())
            {
                std::string catName = category->Value();
                std::string lowCatName = catName;
                std::transform(lowCatName.begin(), lowCatName.end(), lowCatName.begin(), ::tolower);

                if (lowCatName == "schoolzones" || lowCatName == "schoolzone" || 
                    lowCatName == "speedlimits" || lowCatName == "speedlimit")
                {
                    int defaultType = (lowCatName.find("school") != std::string::npos) ? 5 : 6;
                    for (TiXmlElement *elem = category->FirstChildElement(); elem != nullptr;
                         elem = elem->NextSiblingElement())
                    {
                        InputV2XEvent zoneData;
                        zoneData.msgType = defaultType;
                        const char* linkId = elem->Attribute("linkId");
                        const char* lanes = elem->Attribute("laneIds");
                        const char* startPos = elem->Attribute("startPos");
                        const char* endPos = elem->Attribute("endPos");
                        const char* limit = elem->Attribute("speedLimit");

                        if (linkId) zoneData.linkId = atoi(linkId);
                        if (lanes) {
                            std::stringstream ss(lanes);
                            std::string segment;
                            while(std::getline(ss, segment, ',')) zoneData.laneIds.push_back(atoi(segment.c_str()));
                        } else zoneData.laneIds.push_back(-1);

                        if (startPos) zoneData.startPos = atof(startPos);
                        if (endPos) zoneData.endPos = atof(endPos);
                        if (limit) zoneData.speedLimit = atof(limit);
                        
                        consolidatedV2X.AddEvent(zoneData);
                    }
                }
                else if (lowCatName == "rsus" || lowCatName == "rsu")
                {
                    for (TiXmlElement *elem = category->FirstChildElement(); elem != nullptr;
                         elem = elem->NextSiblingElement())
                    {
                        InputRSU rsu;
                        const char* id = elem->Attribute("id");
                        const char* nodeId = elem->Attribute("nodeId");
                        if (id) rsu.id = atoi(id);
                        if (nodeId) rsu.nodeId = atoi(nodeId);
                        consolidatedV2X.AddRSU(rsu);
                    }
                }
            }
        }
    }
    if (hasV2XInput)
        m_v2xs.push_back(consolidatedV2X);
}
} // namespace NextSimIO
