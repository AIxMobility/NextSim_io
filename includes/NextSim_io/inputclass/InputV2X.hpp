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
/**
 * @struct InputV2XConfig
 * @brief Consolidated configuration for V2X (Range + Message switches)
 */
struct InputV2XConfig
{
    // Ranges
    double v2iRange = 500.0;
    double v2vRange = 300.0;
    int trafficInfoInterval = 5; // seconds
    int signalPhaseInterval = 1; // seconds
    
    // Message Activation Switches and Timing
    bool position = false;
    bool trafficInfo = false;
    bool signalPhase = false;
    bool roadEvent = false;
    
    struct {
        bool active = false;
        std::string startTime = "00:00:00";
        int duration = -1; // duration in seconds, -1 for simulation end
    } schoolZone, speedLimit;

    bool collisionWarn = false;
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
    bool collisionWarning = false;
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
    InputV2XConfig GetConfig() const { return m_config; }

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
