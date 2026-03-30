/**
 * NextSim Captain
 * @file InputV2X.hpp
 * @version : 1.1
 * @author : Elena
 */

#pragma once

#ifndef INPUTV2X_HPP
#define INPUTV2X_HPP

#include <vector>
#include <string>
#include <map>

namespace NextSimIO
{
/**
 * @struct V2XMsgType
 * @brief V2X Message Type Mapping (Numeric IDs like Node Types)
 */
// V2XMsgType is now managed in Captain::Enumerations as enum class V2XMsgType

struct V2XMsgContent
{
    double speedLimit = 0.0;
    std::string eventDetail = "";
    bool collisionWarning = false;
    // Add other dynamic fields as needed
};

struct V2XRange
{
    double v2iRange = 500.0;
    double v2vRange = 300.0;
};

struct V2XMessageConfig
{
    bool position = false;
    bool trafficInfo = false;
    bool signalPhase = false;
    bool roadEvent = false;
    bool schoolZone = false;
    bool speedLimit = false;
    bool collisionWarn = false;
};

struct V2XEventData
{
    int linkId = 0;
    std::vector<int> laneIds; // -1 for all lanes, or list of lane IDs
    double startPos = 0.0;
    double endPos = 0.0;
    double startTime = 0.0;
    double endTime = 0.0;
    int msgType = 0; // Numeric ID from V2XMsgType
    V2XMsgContent content;
};

struct V2XData
{
    bool active = false;
    V2XRange range;
    V2XMessageConfig message;
    std::vector<int> activeMsgTypes; // Computed from message config for engine use
    std::vector<V2XEventData> events;
    
    std::map<int, V2XEventData> idEventMap; // [EventID, EventData]
};
} // namespace NextSimIO

#endif
