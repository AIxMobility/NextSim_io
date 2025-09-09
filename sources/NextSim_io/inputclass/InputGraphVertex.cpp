/**
 * NextSim Captain
 * @file InputGraphVertex.cpp
 * @version 1.0
 * @author Dongheon Lee
 */

#include <math.h>
#include <NextSim_io/inputclass/InputGraphVertex.hpp>

namespace NextSimIO
{
InputGraphVertex::InputGraphVertex()
    : m_id(0), m_type(0), m_heuristic(0), m_rank(0) {};

InputGraphVertex::InputGraphVertex(int id, int type, float heuristic, int rank)
    : m_id(id), m_type(type), m_heuristic(heuristic), m_rank(rank) {};

ConnectionInfo::ConnectionInfo(int fromLink, int toLink, int fromLane, int toLane, double length)
    : m_fromLink(fromLink), m_toLink(toLink), m_fromLane(fromLane), m_toLane(toLane), m_length(length) {};

VertexCoord::VertexCoord(float x, float y)
    : m_x(x), m_y(y) {};

void InputGraphVertex::pushLink(port link)
{
    m_connectedLinks.emplace_back(link);
    if (link.GetType() == -1)
        m_connectedOutLinks.emplace_back(link);
}

float InputGraphVertex::CalHeuristic(InputGraphVertex departVertex, InputGraphVertex destVertex)
{
    std::vector<VertexCoord> departCoord = departVertex.GetCoordinates();
    std::vector<VertexCoord> destCoord = destVertex.GetCoordinates();

    float x_depart = departCoord[0].GetX();
    float y_depart = departCoord[0].GetY();
    float x_dest = destCoord[0].GetX();
    float y_dest = destCoord[0].GetY();

    float heuristic = sqrt(pow(x_dest - x_depart, 2) + pow(y_dest - y_depart, 2));

    return heuristic;
}

double InputGraphVertex::GetVertexLength(int fromLink, int toLink)
{
    std::vector<ConnectionInfo> connections = GetConnectionInfo();

    for (auto &connection : connections)
    {
        if (connection.GetFromLink() == fromLink && connection.GetToLink() == toLink)
        {
            return connection.GetLength();
        }
    }

    return 0;
}

} // namespace NextSimIO
