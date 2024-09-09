/**
 * NextSim Captain
 * @file InputLane.hpp
 * @version 1.0
 * @author ???
*/

#ifndef INPUTLANE_H
#define INPUTLANE_H

#include <vector>

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
     * @details Number of cells in lane
    */
    int m_numCell;

    /**
     * @details Vector of cells in lane
    */
    std::vector<InputCell> m_cellArr;

    /**
     * @details Vector of segments in lane
    */
    std::vector<InputSegment> m_segmentArr;

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
     * @param numCellVal Number of cells
    */
    InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
              std::size_t rightLaneIdVal, int numCellVal);

    /**
     * @details Constructor
     * @param id_val Lane ID
     * @param leftLaneIdVal Left lane ID
     * @param rightLaneIdVal Right lane ID
     * @param numCellVal Number of cells
     * @param LeftEmpty Whether left lane is empty or not\
     * @param RightEmpty Whether right lane is empty or not
    */
    InputLane(std::size_t id_val, std::size_t leftLaneIdVal,
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
    void setLeftLaneID(std::size_t leftLaneIdVal) { m_leftLaneId = leftLaneIdVal; }

    /**
     * @details Set right lane ID
     * @param rightLaneIdVal Right lane ID
    */
    void setRightLaneID(std::size_t rightLaneIdVal) { m_rightLaneId = rightLaneIdVal; }

    /**
     * @details Set number of cells
     * @param numCellVal Number of cells
    */
    void setNumCell(int numCellVal) { m_numCell = numCellVal; }

    /**
     * @details Add cell into sequence
     * @param cell Cell vector
    */
    void pushCell(InputCell cell);

    /**
     * @details Add segment into sequence
     * @param segment Segment vector
    */
    void pushSegment(InputSegment segment);

    /**
     * @details Get lane ID
     * @return Lane ID
    */
    std::size_t getID() const { return m_id; }

    /**
     * @details Get left lane ID
     * @return Left lane ID
    */
    std::size_t getLeftLaneID() { return m_leftLaneId; }

    /**
     * @details Get right lane ID
     * @return Right lane ID
    */
    std::size_t getRightLaneID() { return m_rightLaneId; }

    /**
     * @details Get number of cells
     * @return Number of cells
    */
    int getNumCell() { return m_numCell; }

    /**
     * @details Get vector of cells
     * @return Vector of cells
    */
    const std::vector<InputCell>& GetCellVector() const { return m_cellArr; }

    /**
     * @details Get vector of segments
     * @return Vector of segments
    */
    const std::vector<InputSegment>& GetSegmentVector() const { return m_segmentArr; }
};
} // namespace NextSimIO

#endif
