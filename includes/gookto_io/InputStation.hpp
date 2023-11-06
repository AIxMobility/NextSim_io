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
    int lot_size=15;
    double pos;
    int parkingLots;
    std::vector<int> line_list;

public:
    //Constructors
    InputStation(int id, int link_ref, int lane_ref, double pos, int parkingLots);

    // string to vector
    void setLineList(std::string line_list_str);

    int getId() const
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
    int getParkingLotSize()
    {
        return lot_size;
    }
    double getPos()
    {
        return pos;
    }
    int getParkingLotSize()
    {
        return parkingLots;
    }
    std::vector<int> getLineList()
    {
        return line_list;
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