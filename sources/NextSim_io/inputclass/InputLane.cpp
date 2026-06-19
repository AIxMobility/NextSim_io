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
namespace
{
constexpr double VehicleStorageLength = 7.0;
constexpr std::size_t ShortResidualCellMaxVehicle = 1;
}

InputLane::InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
                     std::size_t rightLaneIdVal, std::string laneAccessType, 
                     int numCellVal, std::vector<std::pair<double, double>> shapePoints)
    : m_id(idVal),
      m_leftLaneId(leftLaneIdVal),
      m_rightLaneId(rightLaneIdVal),
      m_accessibleTypes(laneAccessType),
      m_numCell(numCellVal),
      m_shapePoints(std::move(shapePoints))
{
    m_id = idVal;
    m_numCell = numCellVal;
    m_leftLaneId = leftLaneIdVal;
    m_rightLaneId = rightLaneIdVal;
    m_accessibleTypes = laneAccessType;
}

InputLane::InputLane(std::size_t idVal, std::size_t leftLaneIdVal,
                     std::size_t rightLaneIdVal, int numCellVal,
                     bool LeftEmpty, bool RightEmpty)
{
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

void InputLane::MergeShortResidualCell()
{
    if (m_cellVector.size() < 2)
        return;

    const auto& residualCell = m_cellVector.back();
    const auto residualMaxVehicle =
        static_cast<std::size_t>(residualCell.length / VehicleStorageLength);
    if (residualMaxVehicle > ShortResidualCellMaxVehicle)
        return;

    auto& previousCell = m_cellVector.at(m_cellVector.size() - 2);
    previousCell.length += residualCell.length;
    m_cellVector.pop_back();
    m_numCell = static_cast<int>(m_cellVector.size());
}

void InputLane::PushSegment(InputSegment segment)
{
    m_segmentVector.emplace_back(segment);
}
} // namespace NextSimIO
