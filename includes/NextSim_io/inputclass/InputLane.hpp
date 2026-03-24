/**
 * NextSim Captain
 * @file InputLane.hpp
 * @version 1.0
 * @author ???
*/

#pragma once
#ifndef INPUTLANE_H
#define INPUTLANE_H

#include <vector>
#include <string> 
#include <utility>

#include "InputCell.hpp"
#include "InputSegment.hpp"

namespace NextSimIO
{
/**
 * @class InputLane
 * @brief Class for each lane information
 */
class InputLane
{
public:

    /** @cond EXCLUDE */
    InputLane() = default;
    ~InputLane() = default;
    InputLane(const InputLane& lane) = default;
    InputLane& operator=(const InputLane& lane) = default;
    /** @endcond */
    
    /**
     * @details Constructor
     * @param idVal Lane ID
     * @param leftLaneIdVal Left lane ID
     * @param rightLaneIdVal Right lane ID
     * @param laneAccessType Lane access type
     * @param numCellVal Number of cells
     * @param shapePoints Lane shape points
    */
    InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
              std::size_t rightLaneIdVal, std::string laneAccessType, int numCellVal,
              std::vector<std::pair<double, double>> shapePoints);

    /**
     * @details Constructor
     * @param idVal Lane ID
     * @param leftLaneIdVal Left lane ID
     * @param rightLaneIdVal Right lane ID
     * @param numCellVal Number of cells
     * @param LeftEmpty Whether left lane is empty or not\
     * @param RightEmpty Whether right lane is empty or not
     */
    InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
              std::size_t rightLaneIdVal, int numCellVal, 
              bool LeftEmpty, bool RightEmpty);

    /**
     * @details Set lane ID
     * @param id Lane ID
    */
    void SetID(const std::size_t id) { m_id = id; }
    /**
     * @details Set left lane ID
     * @param leftLaneIdVal Left lane ID
    */
    void SetLeftLaneID(std::size_t leftLaneIdVal) { m_leftLaneId = leftLaneIdVal; }

    /**
     * @details Set right lane ID
     * @param rightLaneIdVal Right lane ID
    */
    void SetRightLaneID(std::size_t rightLaneIdVal) { m_rightLaneId = rightLaneIdVal; }
    
    /**
     * @details Set lane access type
     * @param laneAccessType Lane access type
    */
    void SetLaneAccessType(std::string laneAccessType) { m_accessibleTypes = laneAccessType; }

    /**
     * @details Set number of cells
     * @param numCellVal Number of cells
    */
    void SetNumCell(int numCellVal) { m_numCell = numCellVal; }

    /**
     * @details Add cell into sequence
     * @param cell Cell vector
    */
    void PushCell(InputCell cell);

    /**
     * @details Add segment into sequence
     * @param segment Segment vector
    */
    void PushSegment(InputSegment segment);

    /**
     * @details Get lane ID
     * @return Lane ID
    */
    std::size_t GetID() const { return m_id; }

    /**
     * @details Get left lane ID
     * @return Left lane ID
    */
    std::size_t GetLeftLaneID() { return m_leftLaneId; }

    /**
     * @details Get right lane ID
     * @return Right lane ID
    */
    std::size_t GetRightLaneID() { return m_rightLaneId; }
    
    /**
     * @details Get lane access type
     * @return Lane access type
    */
    std::string GetLaneAccessType() const { return m_accessibleTypes; }

    /**
     * @details Get number of cells
     * @return Number of cells
    */
    int GetNumCell() { return m_numCell; }

    /**
     * @details Get vector of cells
     * @return Vector of cells
    */
    const std::vector<InputCell>& GetCellVector() const { return m_cellVector; }

    /**
     * @details Get vector of segments
     * @return Vector of segments
    */
    const std::vector<InputSegment>& GetSegmentVector() const { return m_segmentVector; }

    /**
     * @details Replace lane shape points parsed from XML shape attribute.
     * @param shapePoints Vector of (x, y) points in lane centerline order.
    */
    void SetShapePoints(std::vector<std::pair<double, double>> shapePoints)
    {
        m_shapePoints = std::move(shapePoints);
    }

    /**
     * @details Add one lane shape point.
     * @param x X coordinate
     * @param y Y coordinate
    */
    void PushShapePoint(double x, double y)
    {
        m_shapePoints.emplace_back(x, y);
    }

    /**
     * @details Get lane shape points parsed from XML.
     * @return Vector of (x, y) shape points.
    */
    const std::vector<std::pair<double, double>>& GetShapePoints() const
    {
        return m_shapePoints;
    }

private:

    /**
     * @details Lane ID
    */
    std::size_t m_id;

    /**
     * @details Left lane ID
    */
    std::size_t m_leftLaneId = 0;

    /**
     * @details Right lane ID
    */
    std::size_t m_rightLaneId = 0;
    
    /**
     * @details Lane access type
    */
    std::string m_accessibleTypes = "All";

    /**
     * @details Number of cells in lane
    */
    int m_numCell;

    /**
     * @details Shape points parsed from lane's shape attribute in network.xml
    */
    std::vector<std::pair<double, double>> m_shapePoints;
    
    /**
     * @details Vector of cells in lane
    */
    std::vector<InputCell> m_cellVector;

    /**
     * @details Vector of segments in lane
    */
    std::vector<InputSegment> m_segmentVector;
};
} // namespace NextSimIO

#endif
