/**
 * NextSim Captain
 * @file InputPTGraphVertex.cpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

#include <NextSim_io/inputclass/InputPTGraphVertex.hpp>

namespace NextSimIO
{

Stop::Stop(int stopId, StopType type)
    : m_stopId(stopId), m_stopType(type) {}

    int Stop::GetStopId() const {
        return m_stopId;
    }

    StopType Stop::GetStopType() const {
    return m_stopType;
    }

Line::Line(int lineId, const std::vector<int> &stops, const std::vector<int> &arrivalTimes, const std::vector<int> &departureTimes)
    : m_lineId(lineId), m_stops(stops), m_arrivalTimes(arrivalTimes), m_departureTimes(departureTimes) {}

    int Line::GetLineId() const {
        return m_lineId;
    }

    const std::vector<int>& Line::GetStops() const {
        return m_stops;
    }

    const std::vector<int>& Line::GetArrivalTimes() const {
        return m_arrivalTimes;
    }

    const std::vector<int>& Line::GetDepartureTimes() const {
        return m_departureTimes;
    }

InputPTGraphVertex::InputPTGraphVertex(const Stop& stop, std::shared_ptr<Line> line)
    : m_stop(stop), m_line(std::move(line)) {}

    const Stop& InputPTGraphVertex::GetStop() const {
        return m_stop;
    }

    std::shared_ptr<Line> InputPTGraphVertex::GetLine() const {
        return m_line;
    }

    void InputPTGraphVertex::AddConnection(ConnectionInfo connectionInfo) {
        m_connections.push_back(std::move(connectionInfo));
    }

    const std::vector<ConnectionInfo>& InputPTGraphVertex::GetConnections() const {
        return m_connections;
    }

}; // namespace NextSimIO