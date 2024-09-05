#include <NextSim_io/InputLane.hpp>
#include <iostream>


// InputLane methods


InputLane::InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
                     std::size_t rightLaneIdVal, int numCellVal)
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

InputLane::InputLane(std::size_t id_val, std::size_t leftLaneIdVal,
                     std::size_t rightLaneIdVal, int numCellVal,
                     bool LeftEmpty, bool RightEmpty)
{
    m_id = id_val;
    m_numCell = numCellVal;
    if (RightEmpty)
    {
        m_rightLaneId = 0;
    }
    else
    {
        m_rightLaneId = (rightLaneIdVal);
    }

    if (LeftEmpty)
    {
        m_leftLaneId = 0;
    }
    else
    {
        m_leftLaneId = (leftLaneIdVal);
    }
}


void InputLane::setLeftLaneID(std::size_t leftLaneIdVal)
{
    m_leftLaneId = leftLaneIdVal;
}

void InputLane::setRightLaneID(std::size_t rightLaneIdVal)
{
    m_rightLaneId = rightLaneIdVal;
}

void InputLane::setNumCell(int numCellVal)
{
    m_numCell = numCellVal;
}

void InputLane::pushCell(InputCell cell)
{
    m_cellArr.emplace_back(cell);
}

void InputLane::pushSegment(InputSegment segment)
{
    m_segmentArr.emplace_back(segment);
}
