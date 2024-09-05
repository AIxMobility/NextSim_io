/**
 * NextSim Captain
 * @file : InputPTline.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#ifndef INPUTPTROUTE_H
#define INPUTPTROUTE_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @class InputPTline
 * @brief Class for each public transit line information
 */
class InputPTline
{
private:

    /**
     * @details Public transit line ID
    */
    int id;

    /**
     * @details Dispatch interval [min]
    */
    double interval;

    /**
     * @details Sequence of links that line passes
    */
    std::vector<int> link_seq;

    /**
     * @details Sequence of nodes that line passes
    */
    std::vector<int> node_seq;

    /**
     * @details Sequence of stations that line passes
    */
    std::vector<int> station_seq;

    /**
     * @details Sequence of distance between stations
    */
    std::vector<double> station_distance_seq;
    
public:
    /**
     * @details Constructor
     * @param id Public transit line ID
     * @param interval Dispatch interval
    */
    InputPTline(int id, double interval);

    /**
     * @details Set sequence of links
     * @param linkSeq Sequence of links that line passes
    */
    void setLinkSeq(std::string linkSeq);

    /**
     * @details Set sequence of nodes
     * @param nodeSeq Sequence of nodes that line passes
    */
    void setNodeSeq(std::string nodeSeq);

    /**
     * @details Set sequence of stations
     * @param stationSeq Sequence of stations that line passes
    */
    void setStationSeq(std::string stationSeq);

    /**
     * @details Set sequence of distance between stations
     * @param stationDistanceSeq Sequence of distance between stations
    */
    void setStationDistanceSeq(std::string stationDistanceSeq);

    /**
     * @details Get public transit line ID
     * @return Public transit line ID
    */
    int getId() { return id; }

    /**
     * @details Get dispatch interval
     * @return Dispatch interval [min]
    */
    int getInterval() { return interval; }

    /**
     * @details Get sequence of links
     * @return Sequence of links that line passes
    */
    std::vector<int> getLinkSeq() { return link_seq; }

    /**
     * @details Get sequence of nodes
     * @return Sequence of nodes that line passes
    */
    std::vector<int> getNodeSeq() { return node_seq; }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that line passes
    */
    std::vector<int> getStationSeq() { return station_seq; }

    /**
     * @details Get sequence of distance between stations
     * @return Sequence of distance between stations
    */
    std::vector<double> getStationDistanceSeq() { return station_distance_seq; }
};

#endif