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
 * @brief Class for information of each agent from agents.xml
 */
class InputAgents
{
private:

    /**
     * @details Agent ID
     */
    int id;

    /**
     * @details Agent type ID
     */
    int typeId;

    /**
     * @details Departure time [s]
     */
    double dpt_time;

    /**
     * @details Sequence of links that agent passes
     */
    std::vector<int> link_seq;

    /**
     * @details Sequence of nodes that agent passes
     */
    std::vector<int> node_seq;

    /**
     * @details Sequence of stations that agent passes
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
     * @param type Agent type ID
     * @param dpt_time Departure time
     */
    InputAgents(int id, int typeId, double dpt_time);

    /**
     * @details Set sequence of links
     * @param linkSeq Sequence of links
     */
    void setLinkSeq(std::string linkSeq);

    /**
     * @details Set sequence of nodes
     * @param nodeSeq Sequence of nodes
     */
    void setNodeSeq(std::string nodeSeq);

    /**
     * @details Set sequence of stations
     * @param stationSeq Sequence of stations
     */
    void setStationSeq(std::string stationSeq);

    /**
     * @details Set sequence of distance between stations
     * @param stationDistanceSeq Sequence of distance between stations
     */
    void setStationDistanceSeq(std::string stationDistanceSeq);

    /**
     * @details Get agent ID
     * @return Agent ID
     */
    int getId()
    {
        return id;
    }

    /**
     * @details Get agent type ID
     * @return Agent type ID
     */
    int getTypeId()
    {
        return typeId;
    }

    /**
     * @details Get Departure time
     * @return Departure time [s]
     */
    double getDepTime()
    {
        return dpt_time;
    }

    /**
     * @details Get sequence of links
     * @return Sequence of links that agent passes
     */
    std::vector<int> getLinkSeq()
    {
        return link_seq;
    }

    /**
     * @details Get sequence of nodes
     * @return Sequence of nodes that agent passes
     */
    std::vector<int> getNodeSeq()
    {
        return node_seq;
    }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that agent passes
     */
    std::vector<int> getStationSeq()
    {
        return station_seq;
    }

    /**
     * @details Get sequence of distance between stations
     * @return Sequence of distance between stations
     */
    std::vector<double> getStationDistanceSeq()
    {
        return station_distance_seq;
    }
};

#endif