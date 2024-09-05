//! NextSim Captain
//! Copyright (c) 2019 Justin Kim, Kaist
//! Copying, reproducing and commercial use is not allowed.
//! We are not conveying any rights to any intellectual property of any third
//! parties
//!
//! \file : InputLink.hpp
//! \version : 1.0
//! \author : Jae Hwan Jung, Justin Kim

/**
 * NextSim Captain
 * @file : InputLink.hpp
 * @version : 1.0
 * @author : Jae Hwan Jung, Justin Kim
*/
#ifndef INPUTLINK_H
#define INPUTLINK_H


#include <vector>
#include <string>
#include "BaseClass.hpp"
#include "InputLane.hpp"
// #include "InputLane.hpp"
// #include "InputCell.hpp"

/**
 * @class InputLink
 * @brief Class for each link information
*/
class InputLink : public MetaData
{
private:

    /**
     * @details To node ID (connected with link end point)
    */
    std::size_t m_toNode = 0;

    /**
     * @details From node ID (connected with link start point)
    */
    std::size_t m_fromNode = 0;

    /**
     * @details Number of lanes
    */
    int m_numLane;

    /**
     * @details Link type (straight, curve)
    */
    std::string _type;
    
    /**
     * @details Simulation type (micro, meso)
    */
    std::string _sim_type;

    /**
     * @details Sequence of lanes
    */
    std::vector<InputLane> LaneArr;

    /**
     * @details Sequence of lane IDs
    */
    std::vector<std::size_t> LaneIds;

    /**
     * @details Sequence of number of cells of each lane
    */
    std::vector<int> m_laneNumCellVector;

public:
    //Constructors
    /**
     * @details Constructor
     * @param id Link ID
     * @param lane Lane ID
     * @param length Link length
     * @param width Link width
     * @param stopline Position of stop line
    */
    InputLink(std::size_t id, int lane, double length, double width, double stopline);

    // ???
    ~InputLink() = default;
    InputLink(const InputLink& link) = default;
    InputLink& operator=(const InputLink& link) = default;


    //each cell might have different 4 params
    /**
     * @details Get free flow speed of each cell
     * @return Free flow speed of each cell [km/hr]
    */
    // ??? return 완성 안 된 함수들이긴 한데 일단 적어둠
    std::vector<std::vector<double>> Get2DFreeFlowSpeed();

    /**
     * @details Get maximum speed of each cell
     * @return Maximum speed of each cell [km/hr]
    */
    std::vector<std::vector<double>> Get2DMaxSpeed();

    /**
     * @details Get minimum speed of each cell
     * @return Minimum speed of each cell [km/hr]
    */
    std::vector<std::vector<double>> Get2DMinSpeed();

    /**
     * @details Get max capacity of each cell
     * @return Max capacity of each cell [veh/hr]
    */
    std::vector<std::vector<double>> Get2DQmax2D();

    /**
     * @details Get wave speed of each cell
     * @return Wave speed of each cell [km/hr]
    */
    std::vector<std::vector<double>> Get2DWaveSpeed();

    /**
     * @details Get maximum number of vehicles of each cell
     * @return Maximum number of vehicles of each cell [veh/link]
    */
    std::vector<std::vector<size_t>> Get2DMaxVehicle();

    /**
     * @details Get sequence of lane IDs
     * @return Sequence of lane IDs
    */
    [[nodiscard]] const std::vector<std::size_t>& GetLaneIds() const { return LaneIds; }

    /**
     * @details Get sequence of lanes
     * @return Sequence of lanes
    */
    [[nodiscard]] const std::vector<InputLane>& GetLaneArr() const { return LaneArr; }

    /**
     * @details Get link ID
     * @return Link ID
    */
    [[nodiscard]] std::size_t GetID() const { return ID; }

    /**
     * @details Get number of ???
     * @return 
    */
    int GetNumSect() { return m_laneNumCellVector[0]; }

    /**
     * @details Get number of lanes
     * @return Number of lanes
    */
    int GetNumLane() { return m_numLane; }

    /**
     * @details Set number of lanes
     * @param num Number of lanes
    */
    void setNumLane(int num);

    /**
     * @details Add lane into sequence
     * @param lane_id Lane
    */
    void pushLaneId(InputLane lane);

    /**
     * @details Set from node ID
     * @param val From node ID (connected with link start point)
    */
    void SetFromNode(std::size_t val);

    /**
     * @details Get from node ID
     * @return From node ID (connected with link start point)
    */
    std::size_t GetFromNode() { return m_fromNode; }

    /**
     * @details Set to node ID
     * @param val To node ID (connected with link end point)
    */
    void SetToNode(std::size_t val);

    /**
     * @details Get to node ID
     * @return To node ID (connected with link end point)
    */
    std::size_t GetToNode() { return m_toNode; }

    /**
     * @details Set simulation type
     * @param val Simulation type (micro, meso)
    */
    void SetSimType(const std::string& val) { _sim_type = val; }

    /**
     * @details Get simulation type
     * @return Simulation type (micro, meso)
    */
    [[nodiscard]] const std::string& GetSimType() const { return _sim_type; }

    /**
     * @details Set link type
     * @param val Link type (straight, curve)
    */
    void SetType(const std::string& val) { _type = val; }

    /**
     * @details Get link type
     * @return Link type (straight, curve)
    */
    [[nodiscard]] const std::string& GetType() const { return _type; }
    //Free 2d Vectors

    //Need to make helper functions for Designating cell-by-cell values
};

#endif
