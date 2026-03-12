/**
 * NextSim Captain
 * @file : InputMessage.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#pragma once
#ifndef INPUTMSG_H
#define INPUTMSG_H

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class InputV2XMsg
 * @brief Class for each msg information
*/
class InputV2XMsg
{
public:
    /**
     * @brief Constructor
     * @param id Msg ID
     * @param sTime Start time
     * @param eTime End time
     * @param msgType Msg type
     * @param value Speed value
    */
    InputV2XMsg(int id, double sTime, double eTime, 
                 int msgType, int value);

    /**
     * @brief Get message ID
     * @return Message ID
    */
    int GetID() { return m_id;}

    /**
     * @brief Get start time
     * @return Start time for message operation
    */
    double GetStartTime() { return m_sTime;}
    
    /**
     * @brief Get end time
     * @return End time for message operation
    */
    double GetEndTime() { return m_eTime;}

    /**
     * @brief Get message type
     * @return Message type (1: speed recommendation, 2: warning)
    */
    int GetMsgType() { return m_msgType;}

    /**
     * @brief Get speed value
     * @return Speed value for speed recommendation message [km/h]
    */
    int GetValue() { return m_value;}

    /**
     * @brief Get node ID
     * @return Node ID for getting message
    */
    int GetNodeID() { return m_nodeID;}

    /**
     * @brief Get vehicle ID
     * @return Vehicle ID for getting message
    */
    int GetVehID() { return m_vehID;}

    /**
     * @brief Set node ID
     * @param nodeID Node ID for getting message
    */
    void SetNodeID (int nodeID) { m_nodeID = nodeID; }

    /**
     * @brief Set vehicle ID
     * @param vehID Vehicle ID for getting message
    */
    void SetVehID (int vehID) { m_vehID = vehID; }

private:
    /**
     * @details Message ID
    */
    int m_id;

    /**
     * @details Start time for message operation
    */
    double m_sTime;

    /**
     * @details End time for message operation
    */
    double m_eTime;

    /**
     * @details Message type (1: speed recommendation, 2: warning)
    */
    int m_msgType;

    /**
     * @details Speed value for speed recommendation message [km/h]
    */
    int m_value;

    /**
     * @details Node ID for getting message (unique to Region Message)
    */
    int m_nodeID = 0;

    /**
     * @details Vehicle ID for getting message (unique to Vehicle Message)
    */
    int m_vehID = 0;
};
} // namespace NextSimIO

#endif