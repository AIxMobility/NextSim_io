#include <gookto_io/InputLink.hpp>
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

std::vector<std::vector<double>> InputLink::Get2DFreeFlowSpeed()
{
    std::vector<std::vector<double>> matrix(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i] = std::vector<double>(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = LaneArr[i].GetCellVector()[j].FreeFlowSpeed;
        }
    }
    return matrix;
}
std::vector<std::vector<double>> InputLink::Get2DQmax2D()
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
std::vector<std::vector<double>> InputLink::Get2DWaveSpeed()
{
    std::vector<std::vector<double>> matrix;
    matrix.resize(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i].resize(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            matrix[i][j] = LaneArr[i].GetCellVector()[j].WaveSpeed;
        }
    }
    return matrix;
}
std::vector<std::vector<size_t>> InputLink::Get2DMaxVehicle(int vehlength)
{
    std::vector<std::vector<size_t>> matrix;
    matrix.resize(m_numLane);
    for (int i = 0; i < m_numLane; i++)
    {
        matrix[i].resize(m_laneNumCellVector[i]);
        for (int j = 0; j < m_laneNumCellVector[i]; j++)
        {
            // temporary calculation basaed on ceiling(length / 5)
            matrix[i][j] = static_cast<std::size_t>(std::ceil(Length/vehlength));
        }
    }
    return matrix;
}
