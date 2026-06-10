/**
 * NextSim Captain
 * @file InputV2X.hpp
 * @version : 1.2
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
enum class InputV2XMsgType
{
    Undefined = 0,
    Position = 1,
    TrafficInfo = 2,
    Signal = 3,
    RoadEvent = 4,
    SchoolZone = 5,
    SpeedLimit = 6,
    CollisionWarn = 7
};

constexpr int ToInt(InputV2XMsgType msgType)
{
    return static_cast<int>(msgType);
}

struct MsgConfig
{
    bool active = false;
    int interval = 1; // seconds
};

struct MsgConfigTime
{
    bool active = false;
    int interval = 1; // seconds
    std::string startTime = "00:00:00";
    int duration = -1; // duration in seconds, -1 for simulation end
};

/**
 * @struct InputV2XConfig
 * @brief Consolidated configuration for V2X (Range + Message switches)
 */
struct InputV2XConfig
{
    // General V2X configuration
    double v2iRange = 500.0;
    MsgConfig debugLog;
    
    // Message Activation Switches and Timing
    MsgConfig position;
    MsgConfig trafficInfo;
    MsgConfig signal;
    MsgConfig roadEvent;
    
    MsgConfigTime schoolZone;
    MsgConfigTime speedLimit;

    struct {
        bool active = false;
        double straightRange = 100.0; // m
        double rtorRange = 50.0;      // m
        double DRACThreshold = 3.4;   // m/s^2
        int interval = 1;             // seconds
    } collisionWarn;
};

/**
 * @struct InputRSU
 * @brief RSU placement information
 */
struct InputRSU
{
    int id;
    int nodeId;
};

/**
 * @struct InputV2XEvent
 * @brief V2X Event information from event_v2x.xml
 */
struct InputV2XEvent
{
    int linkId = 0;
    std::vector<int> laneIds; // -1 for all lanes, or list of lane IDs
    double startPos = 0.0;
    double endPos = 0.0;
    double startTime = 0.0;
    double endTime = 0.0;
    int msgType = 0; 

    // Integrated content fields (simplified from former MsgContent)
    double speedLimit = 0.0;
    std::string eventDetail = "";
};

/**
 * @class InputV2X
 * @brief Class for V2X input data management
 */
class InputV2X
{
public:
    InputV2X() = default;

    void SetConfig(InputV2XConfig config) { m_config = config; }
    const InputV2XConfig& GetConfig() const { return m_config; }

    void AddEvent(InputV2XEvent event) { m_events.push_back(event); }
    const std::vector<InputV2XEvent>& GetEvents() const { return m_events; }

    void AddRSU(InputRSU rsu) { m_rsus.push_back(rsu); }
    const std::vector<InputRSU>& GetRSUs() const { return m_rsus; }

private:
    InputV2XConfig m_config;
    std::vector<InputV2XEvent> m_events;
    std::vector<InputRSU> m_rsus;
};
} // namespace NextSimIO

#endif
