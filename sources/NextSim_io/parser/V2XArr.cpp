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

    // 1. Load config_v2x.json
    std::ifstream configIfs(NextSimIO::V2XConfigJSONPath.string());
    if (configIfs.is_open())
    {
        rapidjson::IStreamWrapper isw(configIfs);
        rapidjson::Document doc;
        doc.ParseStream(isw);

        if (!doc.HasParseError())
        {
            // 1.1 Load V2XRange
            if (doc.HasMember("V2XRange") && doc["V2XRange"].IsObject())
            {
                const rapidjson::Value& range = doc["V2XRange"];
                if (range.HasMember("V2IRange")) config.v2iRange = range["V2IRange"].GetDouble();
                if (range.HasMember("V2VRange")) config.v2vRange = range["V2VRange"].GetDouble();
            }

            // 1.2 Load V2XMessage
            if (doc.HasMember("V2XMessage") && doc["V2XMessage"].IsObject())
            {
                const rapidjson::Value& msg = doc["V2XMessage"];
                if (msg.HasMember("Position")) config.position = msg["Position"].GetBool();
                if (msg.HasMember("TrafficInfo")) {
                    if (msg["TrafficInfo"].IsBool()) config.trafficInfo.active = msg["TrafficInfo"].GetBool();
                    else if (msg["TrafficInfo"].IsObject()) {
                        const auto& trafficInfo = msg["TrafficInfo"];
                        if (trafficInfo.HasMember("active")) config.trafficInfo.active = trafficInfo["active"].GetBool();
                        if (trafficInfo.HasMember("interval")) config.trafficInfo.interval = trafficInfo["interval"].GetInt();
                    }
                }
                if (msg.HasMember("SignalPhase")) {
                    if (msg["SignalPhase"].IsBool()) config.signalPhase.active = msg["SignalPhase"].GetBool();
                    else if (msg["SignalPhase"].IsObject()) {
                        const auto& signalPhase = msg["SignalPhase"];
                        if (signalPhase.HasMember("active")) config.signalPhase.active = signalPhase["active"].GetBool();
                        if (signalPhase.HasMember("interval")) config.signalPhase.interval = signalPhase["interval"].GetInt();
                    }
                }
                if (msg.HasMember("RoadEvent")) config.roadEvent = msg["RoadEvent"].GetBool();
                if (msg.HasMember("SchoolZone")) {
                    if (msg["SchoolZone"].IsBool()) config.schoolZone.active = msg["SchoolZone"].GetBool();
                    else if (msg["SchoolZone"].IsObject()) {
                        const auto& sz = msg["SchoolZone"];
                        if (sz.HasMember("active")) config.schoolZone.active = sz["active"].GetBool();
                        if (sz.HasMember("startTime")) config.schoolZone.startTime = sz["startTime"].GetString();
                        if (sz.HasMember("duration")) config.schoolZone.duration = sz["duration"].GetInt();
                    }
                }
                if (msg.HasMember("SpeedLimit")) {
                    if (msg["SpeedLimit"].IsBool()) config.speedLimit.active = msg["SpeedLimit"].GetBool();
                    else if (msg["SpeedLimit"].IsObject()) {
                        const auto& sl = msg["SpeedLimit"];
                        if (sl.HasMember("active")) config.speedLimit.active = sl["active"].GetBool();
                        if (sl.HasMember("startTime")) config.speedLimit.startTime = sl["startTime"].GetString();
                        if (sl.HasMember("duration")) config.speedLimit.duration = sl["duration"].GetInt();
                    }
                }
                if (msg.HasMember("CollisionWarn")) config.collisionWarn = msg["CollisionWarn"].GetBool();
            }

            // 1.3 Load V2XInterval
            if (doc.HasMember("V2XInterval") && doc["V2XInterval"].IsObject())
            {
                const rapidjson::Value& interval = doc["V2XInterval"];
                if (interval.HasMember("TrafficInfoInterval")) config.trafficInfo.interval = interval["TrafficInfoInterval"].GetInt();
                if (interval.HasMember("SignalPhaseInterval")) config.signalPhase.interval = interval["SignalPhaseInterval"].GetInt();
            }
        }
        consolidatedV2X.SetConfig(config);
    }

    // 2. Load event_v2x.xml
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::V2XEventXMLPath.string().c_str());

    if (loadSuccess)
    {
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
                    const char* link_id = elem->Attribute("link_id");
                    const char* lane = elem->Attribute("lane");
                    const char* startPos = elem->Attribute("startPos");
                    const char* endPos = elem->Attribute("endPos");
                    const char* pos = elem->Attribute("pos");
                    const char* stime = elem->Attribute("stime");
                    const char* etime = elem->Attribute("etime");
                    const char* type = elem->Attribute("type");
                    const char* speedLimit = elem->Attribute("speedLimit");
                    const char* detail = elem->Attribute("detail");
                    const char* collision = elem->Attribute("collision");

                    if (linkId) eventData.linkId = atoi(linkId);
                    else if (link_id) eventData.linkId = atoi(link_id);
                    if (lane) eventData.laneIds.push_back(atoi(lane));
                    else eventData.laneIds.push_back(-1);
                    if (startPos) eventData.startPos = atof(startPos);
                    else if (pos) { eventData.startPos = atof(pos); eventData.endPos = atof(pos); }
                    if (endPos) eventData.endPos = atof(endPos);
                    if (stime) eventData.startTime = atof(stime);
                    if (etime) eventData.endTime = atof(etime);

                    if (type)
                    {
                        std::string typeStr(type);
                        if (typeStr == "Position") eventData.msgType = 1;
                        else if (typeStr == "TrafficInfo") eventData.msgType = 2;
                        else if (typeStr == "SignalPhase") eventData.msgType = 3;
                        else if (typeStr == "RoadEvent") eventData.msgType = 4;
                        else if (typeStr == "SchoolZone") eventData.msgType = 5;
                        else if (typeStr == "SpeedLimit") eventData.msgType = 6;
                        else if (typeStr == "CollisionWarn") eventData.msgType = 7;
                        else eventData.msgType = atoi(type);
                    }

                    if (speedLimit) eventData.speedLimit = atof(speedLimit);
                    if (detail) eventData.eventDetail = detail;
                    if (collision) eventData.collisionWarning = (std::string(collision) == "true");

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
    m_v2xs.push_back(consolidatedV2X);
}
} // namespace NextSimIO
