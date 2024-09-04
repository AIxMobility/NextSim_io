/**
 * NextSim Captain
 * @file : InputAgents.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTAGENTS_H
#define INPUTAGENTS_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @class InputAgents
 * @brief Class for agent vehicles information from agents.xml
 */
class InputAgents
{
private:

    /**
     * @details Agent ID
     */
    int id;

    /**
     * @details Agent Type ID
     */
    int typeId;

    /**
     * @details Departure time
     */
    double dpt_time;

    /**
     * @details Sequence of links that the agent will pass
     */
    std::vector<int> link_seq;

    /**
     * @details Sequence of nodes that the agent will pass
     */
    std::vector<int> node_seq;

    /**
     * @details Sequence of stations that the agent will pass
     */
    std::vector<int> station_seq;

    /**
     * @details Sequence of distance between stations
     */
    std::vector<double> station_distance_seq;

public:
    /**
     * @details Constructor
     * @param id Agent ID
     * @param type Agent Type ID
     * @param dpt_time Departure time
     */
    InputAgents(int id, int typeId, double dpt_time);

    /**
     * @details Set link sequence
     * @param linkSeq Sequence of links
     */
    void setLinkSeq(std::string linkSeq);

    /**
     * @details Set node sequence
     * @param nodeSeq Sequence of nodes
     */
    void setNodeSeq(std::string nodeSeq);

    /**
     * @details Set station sequence
     * @param stationSeq Sequence of stations
     */
    void setStationSeq(std::string stationSeq);

    /**
     * @details Set station distance sequence
     * @param stationDistanceSeq Sequence of distance between stations
     */
    void setStationDistanceSeq(std::string stationDistanceSeq);

    /**
     * @details Get Agent ID
     * @return Agent ID
     */
    int getId()
    {
        return id;
    }

    /**
     * @details Get Agent Type ID
     * @return Agent Type ID
     */
    int getTypeId()
    {
        return typeId;
    }

    /**
     * @details Get Departure time
     * @return Departure time
     */
    double getDepTime()
    {
        return dpt_time;
    }

    /**
     * @details Get link sequence
     * @return Sequence of links
     */
    std::vector<int> getLinkSeq()
    {
        return link_seq;
    }

    /**
     * @details Get node sequence
     * @return Sequence of nodes
     */
    std::vector<int> getNodeSeq()
    {
        return node_seq;
    }

    /**
     * @details Get station sequence
     * @return Sequence of stations
     */
    std::vector<int> getStationSeq()
    {
        return station_seq;
    }

    /**
     * @details Get station distance sequence
     * @return Sequence of distance between stations
     */
    std::vector<double> getStationDistanceSeq()
    {
        return station_distance_seq;
    }
};

#endif