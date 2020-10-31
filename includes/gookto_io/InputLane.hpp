#ifndef INPUTLANE_H
#define INPUTLANE_H

#include <vector>
#include "InputCell.hpp"
#include "InputSegment.hpp"

class InputLane
{
private:
    std::size_t m_id;
    // pointers to make them nullptrs if needed
    std::size_t m_leftLaneId = 0, m_rightLaneId = 0;
    // Lane ID should be more than 0
    int m_numCell;
    // Arrays of cells and segments;
    std::vector<InputCell> CellArr;
    std::vector<InputSegment> SegmentArr;

public:
    //constructors
    InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
              std::size_t rightLaneIdVal, int numCellVal);
    InputLane(std::size_t id_val, std::size_t left_lane_id_val,
              std::size_t right_lane_id_val, int num_cell_val, bool RightEmpty,
              bool LeftEmpty);

    InputLane() = default;
    ~InputLane() = default;
    InputLane(const InputLane& lane) = default;
    InputLane& operator=(const InputLane& lane) = default;


    void SetID(const std::size_t id)
    {
        m_id = id;
    }
    void setLeftLaneID(std::size_t left_lane_id_val);
    void setRightLaneID(std::size_t right_lane_id_val);
    void setNumCell(int num_cell_val);
    void pushCell(InputCell cell);
    void pushSegment(InputSegment segment);

    std::size_t getID() { return m_id; }
    std::size_t getLeftLaneID() { return m_leftLaneId; }
    std::size_t getRightLaneID() { return m_rightLaneId; }
    int getNumCell() { return m_numCell; }

    const std::vector<InputCell>& GetCellVector() const { return CellArr; }
    const std::vector<InputSegment>& GetSegmentVector() const { return SegmentArr; }
};


#endif
