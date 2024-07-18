#include <NextSim_io/InputLane.hpp>
#include <iostream>


// InputLane methods


InputLane::InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
                     std::size_t rightLaneIdVal,
                     int numCellVal)
    : m_id(idVal),
      m_leftLaneId(leftLaneIdVal),
      m_rightLaneId(rightLaneIdVal),
      m_numCell(numCellVal)
{
    m_id = idVal;
    m_numCell = numCellVal;
    m_leftLaneId = leftLaneIdVal;
    m_rightLaneId = rightLaneIdVal;
}

InputLane::InputLane(std::size_t id_val, std::size_t left_lane_id_val,
                     std::size_t right_lane_id_val,
                     int num_cell_val, bool RightEmpty, bool LeftEmpty)
{
    m_id = id_val;
    m_numCell = num_cell_val;
    if (RightEmpty)
    {
        m_rightLaneId = 0;
    }
    else
    {
        m_rightLaneId = (right_lane_id_val);
    }

    if (LeftEmpty)
    {
        m_leftLaneId = 0;
    }
    else
    {
        m_leftLaneId = (left_lane_id_val);
    }
}


void InputLane::setLeftLaneID(std::size_t left_lane_id_val)
{
    m_leftLaneId = left_lane_id_val;
}

void InputLane::setRightLaneID(std::size_t right_lane_id_val)
{
    m_rightLaneId = right_lane_id_val;
}

void InputLane::setNumCell(int num_cell_val)
{
    m_numCell = num_cell_val;
}

void InputLane::pushCell(InputCell cell)
{
    CellArr.emplace_back(cell);
}

void InputLane::pushSegment(InputSegment segment)
{
    SegmentArr.emplace_back(segment);
}
