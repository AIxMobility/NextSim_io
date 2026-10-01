/**
 * NextSim Captain
 * @file : InputLink.cpp
 * @version : 1.0
 * @author : Jae Hwan Jung, Justin Kim
*/

#include <cmath>
#include <sstream>
#include <algorithm>
#include <NextSim_io/inputclass/InputLink.hpp>

namespace NextSimIO
{
InputLink::InputLink(std::size_t id, int lane, 
                     double length, double width, double stopLine)
    : MetaData(id, length, width, stopLine), m_numLane(lane)
{
}

void InputLink::PushLaneId(InputLane lane)
{
    m_laneIdVector.push_back(lane.GetID());
    m_laneVector.push_back(lane);
    m_laneNumCellVector.push_back(lane.GetNumCell());
}

std::vector<std::vector<double>> InputLink::Get2DFreeFlowSpeed()  // m/s
{
    std::vector<std::vector<double>> matrix(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i] = std::vector<double>(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = m_laneVector[i].GetCellVector()[j].freeFlowSpeed / 3.6;
        }
    }
    return matrix;
}

std::vector<std::vector<double>> InputLink::Get2DQmax2D()  // veh/hr
{
    std::vector<std::vector<double>> matrix(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i] = std::vector<double>(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = m_laneVector[i].GetCellVector()[j].qMax;
        }
    }
    return matrix;
}

std::vector<std::vector<double>> InputLink::Get2DWaveSpeed()  // m/s
{
    std::vector<std::vector<double>> matrix(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i] = std::vector<double>(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = m_laneVector[i].GetCellVector()[j].waveSpeed / 3.6;
        }
    }
    return matrix;
}

std::vector<std::vector<double>> InputLink::Get2DMaxSpeed()  // m/s
{
    std::vector<std::vector<double>> matrix(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i] = std::vector<double>(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = m_laneVector[i].GetCellVector()[j].maxSpeed / 3.6;
        }
    }
    return matrix;
}

std::vector<std::vector<double>> InputLink::Get2DMinSpeed()  // m/s
{
    std::vector<std::vector<double>> matrix(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i] = std::vector<double>(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = m_laneVector[i].GetCellVector()[j].minSpeed / 3.6;
        }
    }
    return matrix;
}

std::vector<std::vector<size_t>> InputLink::Get2DMaxVehicle()  // veh/lane
{
    std::vector<std::vector<size_t>> matrix;
    matrix.resize(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i].resize(m_laneNumCellVector[i]); 
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            // temporary calculation basaed on ceiling(length / 5)
            // matrix[i][j] = static_cast<std::size_t>(std::ceil(Length/vehlength));
            matrix[i][j] = m_laneVector[i].GetCellVector()[j].length / 7;
        }
    }
    return matrix;
}
} // namespace NextSimIO