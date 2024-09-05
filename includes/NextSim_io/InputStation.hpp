/**
 * NextSim Captain
 * @file : InputStation.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef INPUTSTATION_H
#define INPUTSTATION_H

#include <vector>
#include <string>

/**
 * @class InputStation
 * @brief Class for each public transit station information
 */
class InputStation
{
private:
    /**
     * @details Station ID
    */
    int id;

    /**
     * @details Link ID that station is located
    */
    int link_ref;

    /**
     * @details Lane ID that station is located
    */
    int lane_ref;

    /**
     * @details Position of station (from link start point)
    */
    // ??? lane start point부터인지? offset 이라고 적는게 나은지?
    double pos;

    /**
     * @details Number of parking lots
    */
    int parkingLots;

    /**
     * @details Sequence of line IDs that pass the station
    */
    std::vector<int> line_list;

public:
    /**
     * @details Constructor
     * @param id Station ID
     * @param link_ref Link ID
     * @param lane_ref Lane ID
     * @param pos Position of station
     * @param parkingLots Number of parking lots
     */
    InputStation(int id, int link_ref, int lane_ref, double pos, int parkingLots);

    // string to vector
    /**
     * @details Set sequence of line IDs
     * @param line_list_str Sequence of line IDs that pass the station
    */
    void setLineList(std::string line_list_str);

    /**
     * @details Get station ID
     * @return Station ID
    */
    int getId() const
    {
        return id;
    }

    /**
     * @details Get link ID
     * @return Link ID that station is located
    */
    int getLinkRef()
    {
        return link_ref;
    }

    /**
     * @details Get lane ID
     * @return Lane ID that station is located
    */
    int getLaneRef()
    {
        return lane_ref;
    }

    /**
     * @details Get position of station
     * @return Position of station (from link start point)
    */
    double getPos()
    {
        return pos;
    }

    /**
     * @details Get number of parking lots
     * @return Number of parking lots
    */
    int getParkingLotSize()
    {
        return parkingLots;
    }

    /**
     * @details Get sequence of line IDs
     * @return Sequence of line IDs that pass the station
    */
    std::vector<int> getLineList()
    {
        return line_list;
    }
};

/**
 * @class InputDRTStation
 * @brief Class for each DRT station information
 */
class InputDRTStation
{
private:

    /**
     * @details DRT station ID
    */
    int id;

    /**
     * @details Link ID that station is located
    */
    int link_ref;

    /**
     * @details Lane ID that station is located
    */
    int lane_ref;

    /**
     * @details Position range of DRT station
    */
    std::pair<double, double> pos_range;

public:
    //Constructors
    /**
     * @details Constructor
     * @param id DRT station ID
     * @param link_ref Link ID
     * @param lane_ref Lane ID
    */
    InputDRTStation(int id, int link_ref, int lane_ref);

    // string to vector
    /**
     * @details Set position range of DRT station
     * @param pos_range_str Pair of start and end position (from link start point)
    */
    void setPosRange(std::string pos_range_str);

    /**
     * @details Get DRT station ID
     * @return DRT station ID
    */
    int getId()
    {
        return id;
    }
    
    /**
     * @details Get link ID
     * @return Link ID that station is located
    */
    int getLinkRef()
    {
        return link_ref;
    }

    /**
     * @details Get lane ID
     * @return Lane ID that station is located
    */
    int getLaneRef()
    {
        return lane_ref;
    }

    /**
     * @details Get position range of DRT station
     * @return Pair of start and end position (from link start point)
    */
    std::pair<double, double> getPosRange()
    {
        return pos_range;
    }
};
#endif