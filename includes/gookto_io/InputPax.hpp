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
    int origin_link;
    double origin_pos;
    int dest_link;
    double dest_pos;
    double dpt_time;
    std::string type;
    
public:
    AgentPax(int id, int origin_link, double origin_pos, 
             int dest_link, double dest_pos, 
             double dpt_time, std::string type);

    int getId() { return id; }
    int getOriginLink() { return origin_link; }
    double getOriginPos() { return origin_pos; }
    int getDestLink() { return dest_link; }
    double getDestPos() { return dest_pos; }
    double getDptTime() { return dpt_time; }
    std::string getReserveType() { return type; }
};