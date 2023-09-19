#ifndef INPUTSTATION_H
#define INPUTSTATION_H

#include <vector>
#include <string>

class InputStation
{
private:
    int id;
    int link_ref;
    int lane_ref;
    int pos;

public:
    //Constructors
    InputStation(int id, int link_ref, int lane_ref, int pos);

    int getId()
    {
        return id;
    }
    int getLinkRef()
    {
        return link_ref;
    }
    int getLaneRef()
    {
        return lane_ref;
    }
    int getPos()
    {
        return pos;
    }
};


class InputDRTStation
{
private:
    int id;
    int link_ref;
    int lane_ref;
    std::pair<double, double> pos_range;

public:
    //Constructors
    InputDRTStation(int id, int link_ref, int lane_ref);

    // string to vector
    void setPosRange(std::string pos_range_str);

    int getId()
    {
        return id;
    }
    int getLinkRef()
    {
        return link_ref;
    }
    int getLaneRef()
    {
        return lane_ref;
    }
    std::pair<double, double> getPosRange()
    {
        return pos_range;
    }
};
#endif