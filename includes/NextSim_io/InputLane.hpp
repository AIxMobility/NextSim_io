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

    // pointers to make them nullptrs if needed
    /**
     * @details Left lane ID
    */
    std::size_t m_leftLaneId = 0;

    /**
     * @details Right lane ID
    */
    std::size_t m_rightLaneId = 0;
    // Lane ID should be more than 0

    /**
     * @details Number of cells
    */
    int m_numCell;

    // Arrays of cells and segments;
    /**
     * @details Sequence of cells
    */
    // ??? 2D array 인지 1D sequence인지 궁금
    std::vector<InputCell> CellArr;

    /**
     * @details Sequence of segments
    */
    std::vector<InputSegment> SegmentArr;

public:
    //constructors
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
     * @param left_lane_id_val Left lane ID
     * @param right_lane_id_val Right lane ID
     * @param num_cell_val Number of cells
     * @param RightEmpty Whether right lane is empty or not
     * @param LeftEmpty Whether left lane is empty or not
    */
    // ??? leftLaneIdVal 과 left_lane_id_val 은 다른가..?
    // ??? right empty는 lane이 비어있는걸 의미? 또는 cell이 비어있는걸 의미?
    InputLane(std::size_t id_val, std::size_t left_lane_id_val,
              std::size_t right_lane_id_val, int num_cell_val, bool RightEmpty,
              bool LeftEmpty);

    // ???
    InputLane() = default;
    ~InputLane() = default;
    InputLane(const InputLane& lane) = default;
    InputLane& operator=(const InputLane& lane) = default;

    /**
     * @details Set lane ID
     * @param id Lane ID
    */
    void SetID(const std::size_t id)
    {
        m_id = id;
    }

    /**
     * @details Set left lane ID
     * @param left_lane_id_val Left lane ID
    */
    void setLeftLaneID(std::size_t left_lane_id_val);

    /**
     * @details Set right lane ID
     * @param right_lane_id_val Right lane ID
    */
    void setRightLaneID(std::size_t right_lane_id_val);

    /**
     * @details Set number of cells
     * @param num_cell_val Number of cells
    */
    void setNumCell(int num_cell_val);

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
     * @details Get sequence of cells
     * @return Sequence of cells
    */
    const std::vector<InputCell>& GetCellVector() const { return CellArr; }

    /**
     * @details Get sequence of segments
     * @return Sequence of segments
    */
    const std::vector<InputSegment>& GetSegmentVector() const { return SegmentArr; }
};


#endif
