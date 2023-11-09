#pragma once
#include <vector>
#include <string>

class ODPax
{
private:
    int origin;
    int dest;
    int flow; // pax/hr
    std::string dist;
    
public:
    ODPax(int origin, int dest, int flow, std::string dist);

    int getOrigin() { return origin; }
    int getDest() { return dest; }
    int getFlow() { return flow; }
    std::string getDist() { return dist; }
};


class AgentPax
{
private:
    int id;
    int origin_station;
    int dest_station;
    double dpt_time;
    std::string type;
    
public:
    AgentPax(int id, int origin_station, int dest_station, 
             double dpt_time, std::string type);

    int getId() { return id; }
    int getOriginStation() { return origin_station; }
    int getDestStation() { return dest_station; }
    double getDptTime() { return dpt_time; }
    std::string getReserveType() { return type; }
};