/**
 * NextSim Captain
 * @file InputV2X.hpp
 * @version : 1.3
 * @author : Elena
 */

#pragma once

#ifndef INPUTV2X_HPP
#define INPUTV2X_HPP

namespace NextSimIO
{
/**
 * @struct MsgConfig
 * @brief Common on/off and interval settings for one V2X message category
 */
struct MsgConfig
{
    bool active = false;
    int interval = 1; // seconds
};

/**
 * @struct InputV2XConfig
 * @brief Consolidated configuration for V2X (Range + Message switches)
 */
struct InputV2XConfig
{
    double v2iRange = 300.0;
    MsgConfig debugLog;
    MsgConfig position;
    MsgConfig trafficInfo;
    MsgConfig signal;
    MsgConfig roadEvent;
    MsgConfig speedLimit;

    /**
     * @brief Collision warning configuration shared by RTOR / straight conflict checks
     */
    struct {
        bool active = false;
        double straightRange = 100.0; // m
        double rtorRange = 50.0;      // m
        double DRACThreshold = 3.4;   // m/s^2
        int interval = 1;             // seconds
    } collisionWarn;
};

/**
 * @class InputV2X
 * @brief Class for V2X input data management
 */
class InputV2X
{
public:
    InputV2X() = default;

    /**
     * @brief Store the parsed V2X configuration
     * @param config V2X configuration loaded from the input parser
     */
    void SetConfig(InputV2XConfig config) { m_config = config; }

    /**
     * @brief Return the parsed V2X configuration
     * @return Stored V2X configuration
     */
    const InputV2XConfig& GetConfig() const { return m_config; }

private:
    InputV2XConfig m_config;
};
} // namespace NextSimIO

#endif
