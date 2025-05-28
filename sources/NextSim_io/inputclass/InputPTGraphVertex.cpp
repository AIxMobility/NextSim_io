/**
 * NextSim Captain
 * @file InputPTGraphVertex.cpp
 * @version 1.0
 * @author Yeonwoo Yu
 */

#include <math.h>
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

Trip::Trip(int tripId, const std::vector<int> &stops, const std::vector<int> &arrivalTimes, const std::vector<int> &departureTimes)
    : m_tripId(tripId), m_stops(stops), m_arrivalTimes(arrivalTimes), m_departureTimes(departureTimes) {}

    int Trip::GetTripId() const {
        return m_tripId;
    }

    const std::vector<int>& Trip::GetStops() const {
        return m_stops;
    }

    const std::vector<int>& Trip::GetArrivalTimes() const {
        return m_arrivalTimes;
    }

    const std::vector<int>& Trip::GetDepartureTimes() const {
        return m_departureTimes;
    }

InputPTGraphVertex::InputPTGraphVertex(const Stop& stop, std::shared_ptr<Trip> trip)
    : m_stop(stop), m_trip(std::move(trip)) {}

    const Stop& InputPTGraphVertex::GetStop() const {
        return m_stop;
    }

    std::shared_ptr<Trip> InputPTGraphVertex::GetTrip() const {
        return m_trip;
    }

    void InputPTGraphVertex::AddConnection(ConnectionInfo connectionInfo) {
        m_connections.push_back(std::move(connectionInfo));
    }

    const std::vector<ConnectionInfo>& InputPTGraphVertex::GetConnections() const {
        return m_connections;
    }

}; // namespace NextSimIO