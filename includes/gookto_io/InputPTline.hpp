/**
 * STS19 Captain
 * @file : InputPTline.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTPTROUTE_H
#define INPUTPTROUTE_H

#include <iostream>
#include <string>
#include <vector>

class InputPTline
{
private:
    int id;
    double interval;

    std::vector<int> link_seq;
    std::vector<int> node_seq;
    std::vector<int> station_seq;
    std::vector<double> station_distance_seq;

public:
    InputPTline(int id, double interval);

    // string to vector
    void setLinkSeq(std::string linkSeq);
    void setNodeSeq(std::string nodeSeq);
    void setStationSeq(std::string stationSeq);
    void setStationDistanceSeq(std::string stationDistanceSeq);

    //access function
    int getId() { return id; }
    int getInterval() { return interval; }
    std::vector<int> getLinkSeq() { return link_seq; }
    std::vector<int> getNodeSeq() { return node_seq; }
    std::vector<int> getStationSeq() { return station_seq; }
    std::vector<double> getStationDistanceSeq() { return station_distance_seq; }
};

#endif