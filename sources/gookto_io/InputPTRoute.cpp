#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/InputPTRoute.hpp>

InputPTRoute::InputPTRoute(int id, double interval) : id(id), interval(interval) {};

void InputPTRoute::setLinkSeq(std::string linkSeq)
{
    std::string tempStr;
    size_t pos = 0;
    while ((pos = linkSeq.find(" ")) != std::string::npos)
    {
        tempStr = linkSeq.substr(0, pos);
        link_seq.push_back(std::stoi(tempStr));
        linkSeq.erase(0, pos + 1);
    }
}

void InputPTRoute::setNodeSeq(std::string nodeSeq)
{
    std::string tempStr;
    size_t pos = 0;
    while ((pos = nodeSeq.find(" ")) != std::string::npos)
    {
        tempStr = nodeSeq.substr(0, pos);
        node_seq.push_back(std::stoi(tempStr));
        nodeSeq.erase(0, pos + 1);
    }
}

void InputPTRoute::setStationSeq(std::string stationSeq)
{
    std::string tempStr;
    size_t pos = 0;
    while ((pos = stationSeq.find(" ")) != std::string::npos)
    {
        tempStr = stationSeq.substr(0, pos);
        station_seq.push_back(std::stoi(tempStr));
        stationSeq.erase(0, pos + 1);
    }
}