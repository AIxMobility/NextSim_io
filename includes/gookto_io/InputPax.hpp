#pragma once
#include <vector>
#include <string>

class ODPax
{
private:
    int origin;
    int dest;
    double flow; // pax/hr
    std::string dist;
    
public:
    ODPax(int origin, int dest, double flow, std::string dist);

    int getOrigin() { return origin; }
    int getDest() { return dest; }
    double getFlow() { return flow; }
    std::string getDist() { return dist; }
};


class AgentPax
{
private:
    int origin_link;
    double origin_pos;
    int dest_link;
    double dest_pos;
    int num_pax;
    double time;
    std::string type;
    
public:
    AgentPax(int origin_link, double origin_pos, 
             int dest_link, double dest_pos, 
             int num_pax, double time, std::string type);

    int getOriginLink() { return origin_link; }
    double getOriginPos() { return origin_pos; }
    int getDestLink() { return dest_link; }
    double getDestPos() { return dest_pos; }
    int getNumPax() { return num_pax; }
    double getTime() { return time; }
    std::string getType() { return type; }
};