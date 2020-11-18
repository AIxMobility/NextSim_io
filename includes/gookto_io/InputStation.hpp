#ifndef INPUTSTATION_H
#define INPUTSTATION_H

#include <vector>
#include <string>

class InputStation
{
private:
    int id;
    int lane_ref;
    int link_ref;
    int pos;

public:
    //Constructors
    InputStation(int id, int lane_ref, int link_ref, int pos);

    int getId()
    {
        return id;
    }
    int getLaneRef()
    {
        return lane_ref;
    }
    double getLinkRef()
    {
        return link_ref;
    }
    int getPos()
    {
        return pos;
    }
};

#endif