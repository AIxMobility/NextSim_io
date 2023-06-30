#include <gookto_io/InputLink.hpp>
#include <captain/Util/GlobalHyperParameters.hpp>
#include <iostream>
#include <string>
#include <cmath>

InputLink::InputLink(std::size_t id, int lane, double length, double width)
    : MetaData(id, length, width), m_numLane(lane)
{
}

void InputLink::SetFromNode(std::size_t val)
{
    m_fromNode = val;
}
void InputLink::SetToNode(std::size_t val)
{
    m_toNode = val;
}
void InputLink::setNumLane(int num)
{
    m_numLane = num;
}

void InputLink::pushLaneId(InputLane lane)
{
    LaneIds.push_back(lane.getID());
    LaneArr.push_back(lane);
    m_laneNumCellVector.push_back(lane.getNumCell());
}

std::vector<std::vector<double>> InputLink::Get2DFreeFlowSpeed()  // m/s
{
    std::vector<std::vector<double>> matrix(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i] = std::vector<double>(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = LaneArr[i].GetCellVector()[j].FreeFlowSpeed / 3.6;
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
            matrix[i][j] = LaneArr[i].GetCellVector()[j].Qmax;
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
            matrix[i][j] = LaneArr[i].GetCellVector()[j].WaveSpeed / 3.6;
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
            matrix[i][j] = LaneArr[i].GetCellVector()[j].MaxSpeed / 3.6;
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
            matrix[i][j] = LaneArr[i].GetCellVector()[j].MinSpeed / 3.6;
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
            matrix[i][j] = LaneArr[i].GetCellVector()[j].MaxVehicle / m_numLane;
        }
    }
    return matrix;
}
