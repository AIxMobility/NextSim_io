/**
 * NextSim Captain
 * @file : InputMessage.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTMESSAGE_H
#define INPUTMESSAGE_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @class InputMessage
 * @brief Class for each message information
*/
class InputMessage
{
private:

    /**
     * @details Message ID
    */
    int id;

    /**
     * @details Start time for message operation
    */
    double stime;

    /**
     * @details End time for message operation
    */
    double etime;

    /**
     * @details Message type (1: speed recommendation, 2: warning)
    */
    int msg_type;

    /**
     * @details Speed value for speed recommendation message [km/h]
    */
    int value;

    // unique to Region Message
    /**
     * @details Node ID for getting message
    */
    int node_id = 0;

    // unique to Vehicle Message
    /**
     * @details Vehicle ID for getting message
    */
    int veh_id = 0;

public:
    // Constructor
    /**
     * @brief Constructor
     * @param id Message ID
     * @param stime Start time
     * @param etime End time
     * @param msg_type Message type
     * @param value Speed value
    */
    InputMessage(int id, double stime, double etime, int msg_type, int value);

    // access functions
    /**
     * @brief Get message ID
     * @return Message ID
    */
    int getId()
    {
        return id;
    }

    /**
     * @brief Get start time
     * @return Start time for message operation
    */
    // ??? 단위
    double getStime()
    {
        return stime;
    }
    
    /**
     * @brief Get end time
     * @return End time for message operation
    */
    double getEtime()
    {
        return etime;
    }

    /**
     * @brief Get message type
     * @return Message type (1: speed recommendation, 2: warning)
    */
    int getMsg_type()
    {
        return msg_type;
    }

    /**
     * @brief Get speed value
     * @return Speed value for speed recommendation message [km/h]
    */
    int getvalue()
    {
        return value;
    }

    /**
     * @brief Get node ID
     * @return Node ID for getting message
    */
    int getNode_id()
    {
        return node_id;
    }

    /**
     * @brief Get vehicle ID
     * @return Vehicle ID for getting message
    */
    int getVeh_id()
    {
        return veh_id;
    }

    /**
     * @brief Set node ID
     * @param nnode_id Node ID for getting message
    */
    void setNode_id (int nnode_id)
    {
        node_id = nnode_id;
    }

    /**
     * @brief Set vehicle ID
     * @param nveh_id Vehicle ID for getting message
    */
    void setVeh_id (int nveh_id)
    {
        veh_id = nveh_id;
    }
};

#endif