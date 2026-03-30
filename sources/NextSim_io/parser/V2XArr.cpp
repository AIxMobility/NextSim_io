/**
 * NextSim Captain
 * @file : V2XArr.cpp
 * @version : 1.5
 * @author : Elena
 */

#include <NextSim_io/parser/V2XArr.hpp>
#include <NextSim_io/FilePath.hpp>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
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

            // 1.2 Load V2XMessage (replaces old V2XConfig)
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

                // Compute activeMsgTypes using int values matching Captain::V2XMsgType enum
                // (Position=1, TrafficInfo=2, SignalPhase=3, RoadEvent=4, SchoolZone=5, SpeedLimit=6, CollisionWarn=7)
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

    // 2. Load event_v2x.json
    std::ifstream eventIfs(NextSimIO::V2XEventJSONPath.string());
    if (eventIfs.is_open())
    {
        rapidjson::IStreamWrapper isw(eventIfs);
        rapidjson::Document doc;
        doc.ParseStream(isw);

        if (!doc.HasParseError() && doc.HasMember("V2XEvents") && doc["V2XEvents"].IsArray())
        {
            const rapidjson::Value& events = doc["V2XEvents"];
            int eventCounter = 0;
            for (rapidjson::SizeType i = 0; i < events.Size(); i++)
            {
                const rapidjson::Value& event = events[i];
                V2XEventData eventData;
                if (event.HasMember("linkId")) eventData.linkId = event["linkId"].GetInt();
                
                // Multi-lane support
                if (event.HasMember("laneIds") && event["laneIds"].IsArray())
                {
                    const rapidjson::Value& lanes = event["laneIds"];
                    for (rapidjson::SizeType j = 0; j < lanes.Size(); j++)
                    {
                        eventData.laneIds.push_back(lanes[j].GetInt());
                    }
                }
                else if (event.HasMember("laneId")) // Legacy support
                {
                    eventData.laneIds.push_back(event["laneId"].GetInt());
                }
                
                if (eventData.laneIds.empty()) eventData.laneIds.push_back(-1); // Default to all lanes

                if (event.HasMember("startPos")) eventData.startPos = event["startPos"].GetDouble();
                if (event.HasMember("endPos")) eventData.endPos = event["endPos"].GetDouble();
                if (event.HasMember("startTime")) eventData.startTime = event["startTime"].GetDouble();
                if (event.HasMember("endTime")) eventData.endTime = event["endTime"].GetDouble();
                if (event.HasMember("msgType")) eventData.msgType = event["msgType"].GetInt();

                if (event.HasMember("content") && event["content"].IsObject())
                {
                    const rapidjson::Value& content = event["content"];
                    if (content.HasMember("speedLimit")) eventData.content.speedLimit = content["speedLimit"].GetDouble();
                    if (content.HasMember("eventDetail")) eventData.content.eventDetail = content["eventDetail"].GetString();
                    if (content.HasMember("collisionWarning")) eventData.content.collisionWarning = content["collisionWarning"].GetBool();
                }

                int currentEventID = eventCounter++;
                m_v2xData.events.push_back(eventData);
                m_v2xData.idEventMap[currentEventID] = eventData;
            }
        }
        else
        {
            std::cout << "Parse error (V2X Events JSON)" << std::endl;
        }
    }
    else
    {
        std::cout << "Loading failed (V2X Events JSON): " << NextSimIO::V2XEventJSONPath << std::endl;
    }
}
} // namespace NextSimIO