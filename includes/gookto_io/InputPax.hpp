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
    int origin_pos;
    int dest_link;
    int dest_pos;
    double dpt_time;
    std::string type;
    
public:
    AgentPax(int id, int origin_link, int origin_pos, int dest_link, int dest_pos, 
             double dpt_time, std::string type);

    int getId() { return id; }
    int getOriginLink() { return origin_link; }
    int getOriginPos() { return origin_pos; }
    int getDestLink() { return dest_link; }
    int getDestPos() { return dest_pos; }
    double getDptTime() { return dpt_time; }
    std::string getReserveType() { return type; }
};