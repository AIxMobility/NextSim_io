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

namespace NextSimIO
{
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
     * @details Number of lanes in link
    */
    int m_numLane;

    /**
     * @details Link type (straight, curve)
    */
    std::string m_type;
    
    /**
     * @details Simulation type (micro, meso)
    */
    std::string m_sim_type;

    /**
     * @details Vector of lanes in order
    */
    std::vector<InputLane> m_laneArr;

    /**
     * @details Vector of lane IDs in order
    */
    std::vector<std::size_t> m_laneIds;

    /**
     * @details Vector of number of cells of each lane in order
    */
    std::vector<int> m_laneNumCellVector;

public:
    /**
     * @details Constructor
     * @param id Link ID
     * @param lane Lane ID
     * @param length Link length
     * @param width Link width
     * @param stopline Position of stop line
    */
    InputLink(std::size_t id, int lane, double length, double width, double stopline);

    /** @cond EXCLUDE */
    ~InputLink() = default;
    InputLink(const InputLink& link) = default;
    InputLink& operator=(const InputLink& link) = default;
    /** @endcond */

    /**
     * @details Get free flow speed matrix of each cell in each lane
     * @return Free flow speed matrix [km/hr]
    */
    std::vector<std::vector<double>> Get2DFreeFlowSpeed();

    /**
     * @details Get maximum speed matrix of each cell in each lane
     * @return Maximum speed matrix [km/hr]
    */
    std::vector<std::vector<double>> Get2DMaxSpeed();

    /**
     * @details Get minimum speed matrix of each cell in each lane
     * @return Minimum speed matrix [km/hr]
    */
    std::vector<std::vector<double>> Get2DMinSpeed();

    /**
     * @details Get max capacity matrix of each cell in each lane
     * @return Max capacity matrix [veh/hr]
    */
    std::vector<std::vector<double>> Get2DQmax2D();

    /**
     * @details Get wave speed matrix of each cell in each lane
     * @return Wave speed matrix [km/hr]
    */
    std::vector<std::vector<double>> Get2DWaveSpeed();

    /**
     * @details Get maximum number of vehicles matrix of each cell in each lane
     * @return Maximum number of vehicles matrix [veh/link]
    */
    std::vector<std::vector<size_t>> Get2DMaxVehicle();

    /**
     * @details Get vector of lane IDs
     * @return Vector of lane IDs
    */
    [[nodiscard]] const std::vector<std::size_t>& GetLaneIds() const { return m_laneIds; }

    /**
     * @details Get vector of lanes
     * @return Vector of lanes
    */
    [[nodiscard]] const std::vector<InputLane>& GetLaneArr() const { return m_laneArr; }

    /**
     * @details Get link ID
     * @return Link ID
    */
    [[nodiscard]] std::size_t GetID() const { return ID; }

    /**
     * @details Get vector of number of cells of each lane in order
     * @return Vector of number of cells of each lane in order
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
    void SetNumLane(int num) { m_numLane = num; }

    /**
     * @details Add lane into vector
     * @param lane_id Lane
    */
    void pushLaneId(InputLane lane);

    /**
     * @details Set from node ID
     * @param val From node ID (connected with link start point)
    */
    void SetFromNode(std::size_t val) { m_fromNode = val; }

    /**
     * @details Get from node ID
     * @return From node ID (connected with link start point)
    */
    std::size_t GetFromNode() { return m_fromNode; }

    /**
     * @details Set to node ID
     * @param val To node ID (connected with link end point)
    */
    void SetToNode(std::size_t val) { m_toNode = val; }

    /**
     * @details Get to node ID
     * @return To node ID (connected with link end point)
    */
    std::size_t GetToNode() { return m_toNode; }

    /**
     * @details Set simulation type
     * @param val Simulation type (micro, meso)
    */
    void SetSimType(const std::string& val) { m_sim_type = val; }

    /**
     * @details Get simulation type
     * @return Simulation type (micro, meso)
    */
    const std::string& GetSimType() const { return m_sim_type; }

    /**
     * @details Set link type
     * @param val Link type (straight, curve)
    */
    void SetType(const std::string& val) { m_type = val; }

    /**
     * @details Get link type
     * @return Link type (straight, curve)
    */
    const std::string& GetType() const { return m_type; }

    //Free 2d Vectors
    //Need to make helper functions for Designating cell-by-cell values
};
} // namespace NextSimIO

#endif
