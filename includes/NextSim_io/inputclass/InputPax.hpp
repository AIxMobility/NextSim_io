/**
 * NextSim Captain
 * @file : InputPax.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef INPUTPAX_H
#define INPUTPAX_H

#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class InputODPax
 * @brief Class for each origin-destination passenger information
 */
class InputODPax
{
public:
    /**
     * @details Constructor
     * @param origin Origin station ID
     * @param dest Destination station ID
     * @param flow Passenger flow
     * @param dist Estimated distribution of passenger generation
    */
    InputODPax(int origin, int dest, int flow, std::string dist);

    /**
     * @details Get origin station ID
     * @return Origin station ID
    */
    int GetOrigin() { return m_origin; }

    /**
     * @details Get destination station ID
     * @return Destination station ID
    */
    int GetDest() { return m_dest; }

    /**
     * @details Get passenger flow
     * @return Passenger flow [pax/hr]
    */
    int GetFlow() { return m_flow; }

    /**
     * @details Get estimated distribution of passenger generation
     * @return Estimated distribution of passenger generation
    */
    std::string GetDist() { return m_dist; }

private:

    /**
     * @details Origin station ID
     */
    int m_origin;

    /**
     * @details Destination station ID
     */
    int m_dest;

    /**
     * @details Passenger flow [pax/hr]
     */
    int m_flow;

    /**
     * @details Estimated distribution of passenger generation
     */
    std::string m_dist;
};

/**
 * @class InputAgentPax
 * @brief Class for each agent passenger information
 */
class InputAgentPaxTrip 
{
public:
    /**
     * @details Constructor
     * @param origin Origin ID
     * @param dest Destination ID
     * @param mode Transportation mode
    */
    InputAgentPaxTrip(int origin, int dest, std::string mode)
        : m_origin(origin), m_dest(dest), m_mode(mode) {}

    /**
     * @details Get origin ID
     * @return Origin ID
    */
    int GetOrigin() const { return m_origin; }

    /**
     * @details Get destination ID
     * @return Destination ID
    */
    int GetDest() const { return m_dest; }

    /**
     * @details Get transportation mode
     * @return Transportation mode
    */
    std::string GetMode() const { return m_mode; }

private:
    /**
     * @details Origin ID
     */
    int m_origin;

    /**
     * @details Destination ID
     */
    int m_dest;

    /**
     * @details Transportation mode
     */
    std::string m_mode;
};

/**
 * @class InputAgentPax
 * @brief Class for each agent passenger information
 */
class InputAgentPax
{
    public:
    /**
     * @details Constructor
     * @param id Agent ID
     * @param originLink Origin link ID
     * @param originOffset Origin offset
     * @param destLink Destination link ID
     * @param destOffset Destination offset
     * @param time Departure time
    */
    InputAgentPax(int id, int originLink, int originOffset, int destLink, int destOffset, double time);

    /**
    * @details Get agent ID
    * @return Agent ID
    */
    int GetID() const { return m_id; }

    /**
     * @details Get origin link ID
     * @return Origin link ID
    */
    int GetOriginLink() const { return m_originLink; }

    /**
     * @details Get origin offset
     * @return Origin offset
    */
    int GetOriginOffset() const { return m_originOffset; }

    /**
     * @details Get destination link ID
     * @return Destination link ID
    */
    int GetDestLink() const { return m_destLink; }

    /**
     * @details Get destination offset
     * @return Destination offset
    */
    int GetDestOffset() const { return m_destOffset; }

    /**
     * @details Get time
     * @return Time
    */
    double GetTime() const { return m_time; }


    /**
     * @details Add a trip to this agent
     * @param origin Origin ID
     * @param dest Destination ID
     * @param mode Transportation mode
    */
    void AddTrip(int origin, int dest, std::string mode);

    /**
     * @details Get all trips
     * @return Vector of trips
    */
    const std::vector<InputAgentPaxTrip>& GetTrips() const { return m_trips; }

private:
    /**
     * @details Agent ID
     */
    int m_id;

    /**
     * @details Origin link ID
     */
    int m_originLink;

    /**
     * @details Origin offset
     */
    int m_originOffset;

    /**
     * @details Destination link ID
     */
    int m_destLink;

    /**
     * @details Destination offset
     */
    int m_destOffset;

    /**
     * @details Time
     */
    double m_time;

    /**
     * @details Vector of trips
     */
    std::vector<InputAgentPaxTrip> m_trips;
};
} // namespace NextSimIO

#endif