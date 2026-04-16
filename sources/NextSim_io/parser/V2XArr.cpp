/**
 * NextSim Captain
 * @file : V2XArr.cpp
 * @version : 2.0
 * @author : Elena
 */

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
                if (range.HasMember("V2IRange")) m_v2xData.range.v2iRange = range["V2IRange"].GetDouble();
                if (range.HasMember("V2VRange")) m_v2xData.range.v2vRange = range["V2VRange"].GetDouble();
            }

            // 1.2 Load V2XMessage
            if (doc.HasMember("V2XMessage") && doc["V2XMessage"].IsObject())
            {
                const rapidjson::Value& msg = doc["V2XMessage"];
                
                if (msg.HasMember("Position")) m_v2xData.message.position = msg["Position"].GetBool();
                if (msg.HasMember("TrafficInfo")) m_v2xData.message.trafficInfo = msg["TrafficInfo"].GetBool();
                if (msg.HasMember("SignalPhase")) m_v2xData.message.signalPhase = msg["SignalPhase"].GetBool();
                if (msg.HasMember("RoadEvent")) m_v2xData.message.roadEvent = msg["RoadEvent"].GetBool();
                if (msg.HasMember("SchoolZone")) m_v2xData.message.schoolZone = msg["SchoolZone"].GetBool();
                if (msg.HasMember("SpeedLimit")) m_v2xData.message.speedLimit = msg["SpeedLimit"].GetBool();
                if (msg.HasMember("CollisionWarn")) m_v2xData.message.collisionWarn = msg["CollisionWarn"].GetBool();

                if (m_v2xData.message.position)      m_v2xData.activeMsgTypes.push_back(1);
                if (m_v2xData.message.trafficInfo)   m_v2xData.activeMsgTypes.push_back(2);
                if (m_v2xData.message.signalPhase)   m_v2xData.activeMsgTypes.push_back(3);
                if (m_v2xData.message.roadEvent)     m_v2xData.activeMsgTypes.push_back(4);
                if (m_v2xData.message.schoolZone)    m_v2xData.activeMsgTypes.push_back(5);
                if (m_v2xData.message.speedLimit)    m_v2xData.activeMsgTypes.push_back(6);
                if (m_v2xData.message.collisionWarn) m_v2xData.activeMsgTypes.push_back(7);

                m_v2xData.active = !m_v2xData.activeMsgTypes.empty();
            }
        }
        else
        {
            std::cout << "Parse error (V2X Config JSON)" << std::endl;
        }
    }
    else
    {
        std::cout << "Loading failed (V2X Config JSON): " << NextSimIO::V2XConfigJSONPath << std::endl;
    }

    // 2. Load event_v2x.xml
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::V2XEventXMLPath.string().c_str());

    if (loadSuccess)
    {
        TiXmlElement *root = doc.FirstChildElement();
        if (root)
        {
            int eventCounter = 0;
            for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
                 elem = elem->NextSiblingElement())
            {
                std::string elemName = elem->Value();
                if (elemName == "event")
                {
                    V2XEventData eventData;

                    const char* linkId = elem->Attribute("linkId");
                    const char* link_id = elem->Attribute("link_id");
                    const char* lane = elem->Attribute("lane");
                    const char* startPos = elem->Attribute("startPos");
                    const char* endPos = elem->Attribute("endPos");
                    const char* pos = elem->Attribute("pos");
                    const char* stime = elem->Attribute("stime");
                    const char* etime = elem->Attribute("etime");
                    const char* type = elem->Attribute("type");

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

                    int currentEventID = eventCounter++;
                    m_v2xData.events.push_back(eventData);
                    m_v2xData.idEventMap[currentEventID] = eventData;
                }
            }
        }
    }
    else
    {
        std::cout << "Loading failed (V2X Events XML): " << NextSimIO::V2XEventXMLPath << std::endl;
    }

    doc.Clear();
}
} // namespace NextSimIO
