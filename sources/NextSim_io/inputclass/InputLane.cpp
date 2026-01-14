/**
 * NextSim Captain
 * @file : InputLane.cpp
 * @version : 1.0
 * @author : ???
 */

#include <NextSim_io/inputclass/InputLane.hpp>

// InputLane methods
#include <sstream>
#include <algorithm>

namespace NextSimIO
{
InputLane::InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
                     std::size_t rightLaneIdVal, std::string laneAccessType, int numCellVal, std::string shape)
    : m_id(idVal),
      m_leftLaneId(leftLaneIdVal),
      m_rightLaneId(rightLaneIdVal),
      m_accessibleTypes(laneAccessType),
      m_numCell(numCellVal)
{
    m_id = idVal;
    m_numCell = numCellVal;
    m_leftLaneId = leftLaneIdVal;
    m_rightLaneId = rightLaneIdVal;
    m_accessibleTypes = laneAccessType;
    std::replace(shape.begin(), shape.end(), ',', ' ');
    std::istringstream iss(shape);
    double x, y;
    while (iss >> x >> y) {
        m_shape.emplace_back(x, y);
    }
}

InputLane::InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
                     std::size_t rightLaneIdVal, int numCellVal,
                     bool LeftEmpty, bool RightEmpty, std::string shape)
{
    std::replace(shape.begin(), shape.end(), ',', ' ');
    std::istringstream iss(shape);
    double x, y;
    while (iss >> x >> y) {
        m_shape.emplace_back(x, y);
    }

    m_id = idVal;
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

void InputLane::PushCell(InputCell cell)
{
    m_cellVector.emplace_back(cell);
}

void InputLane::PushSegment(InputSegment segment)
{
    m_segmentVector.emplace_back(segment);
}
} // namespace NextSimIO