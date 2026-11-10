/**
 * NextSim Captain
 * @file : InputAgents.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#pragma once
#ifndef INPUTAGENTS_H
#define INPUTAGENTS_H

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class InputAgents
 * @brief Class for information of each agent from agents.xml
 */
class InputAgents
{
public:
    /**
     * @details Constructor
     * @param id Agent ID
     * @param type Agent type ID
     * @param dpt_time Departure time
     */
    InputAgents(int id, int typeID, double dptTime);

    /**
     * @details Set sequence of links
     * @param linkSeq Sequence of links
     */
    void SetLinkSeq(std::string linkSeq);

    /**
     * @details Set sequence of nodes
     * @param nodeSeq Sequence of nodes
     */
    void SetNodeSeq(std::string nodeSeq);

    /**
     * @details Set sequence of stations
     * @param stationSeq Sequence of stations
     */
    void SetStationSeq(std::string stationSeq);

    /**
     * @details Set sequence of distance between stations
     * @param stationDistanceSeq Sequence of distance between stations
     */
    void SetStationDistanceSeq(std::string stationDistanceSeq);

    /**
     * @details Set source and sink terminals of an agent given without a route
     * @param sourceNode Source terminal node ID
     * @param sinkNode Sink terminal node ID
     */
    void SetEndpoints(int sourceNode, int sinkNode);

    /**
     * @details Set the demand model's trip key (person, tour and stop of the trip)
     * @param personId Person ID
     * @param tourNo Tour number of the person
     * @param stopNo Stop number in the tour
     */
    void SetTripKey(std::string personId, int tourNo, int stopNo);

    /**
     * @details Get agent ID
     * @return Agent ID
     */
    int GetId() const { return m_id; }

    /**
     * @details Get agent type ID
     * @return Agent type ID
     */
    int GetTypeId() const { return m_typeID; }

    /**
     * @details Get Departure time
     * @return Departure time [s]
     */
    double GetDepartureTime() const { return m_dptTime; }

    /**
     * @details Get sequence of links
     * @return Sequence of links that agent passes
     */
    std::vector<int> GetLinkSeq() const { return m_linkSeq; }

    /**
     * @details Get sequence of links without copying
     * @return Sequence of links that agent passes
     */
    const std::vector<int>& GetLinkSeqRef() const { return m_linkSeq; }

    /**
     * @details Get sequence of nodes
     * @return Sequence of nodes that agent passes
     */
    std::vector<int> GetNodeSeq() const { return m_nodeSeq; }

    /**
     * @details Get sequence of nodes without copying
     * @return Sequence of nodes that agent passes
     */
    const std::vector<int>& GetNodeSeqRef() const { return m_nodeSeq; }

    /**
     * @details Get sequence of stations
     * @return Sequence of stations that agent passes
     */
    std::vector<int> GetStationSeq() const { return m_stationSeq; }

    /**
     * @details Get sequence of distance between stations
     * @return Sequence of distance between stations
     */
    std::vector<double> GetStationDistanceSeq() const { return m_stationDistanceSeq; }

    /**
     * @details Get source terminal of an agent given without a route
     * @return Source node ID, -1 if not given
     */
    int GetSourceNode() const { return m_sourceNode; }

    /**
     * @details Get sink terminal of an agent given without a route
     * @return Sink node ID, -1 if not given
     */
    int GetSinkNode() const { return m_sinkNode; }

    /**
     * @details Get person ID of the trip key
     * @return Person ID, empty if not given
     */
    const std::string& GetPersonId() const { return m_personId; }

    /**
     * @details Get tour number of the trip key
     * @return Tour number, -1 if not given
     */
    int GetTourNo() const { return m_tourNo; }

    /**
     * @details Get stop number of the trip key
     * @return Stop number, -1 if not given
     */
    int GetStopNo() const { return m_stopNo; }

private:

    /**
     * @details Agent ID
     */
    int m_id;

    /**
     * @details Agent type ID
     */
    int m_typeID;

    /**
     * @details Departure time [s]
     */
    double m_dptTime;

    /**
     * @details Sequence of links that agent passes
     */
    std::vector<int> m_linkSeq;

    /**
     * @details Sequence of nodes that agent passes
     */
    std::vector<int> m_nodeSeq;

    /**
     * @details Sequence of stations that agent passes
     */
    std::vector<int> m_stationSeq;

    /**
     * @details Sequence of distance between stations
     */
    std::vector<double> m_stationDistanceSeq;

    /**
     * @details Source terminal of an agent given without a route
     */
    int m_sourceNode = -1;

    /**
     * @details Sink terminal of an agent given without a route
     */
    int m_sinkNode = -1;

    /**
     * @details Person ID of the trip key
     */
    std::string m_personId;

    /**
     * @details Tour number of the trip key
     */
    int m_tourNo = -1;

    /**
     * @details Stop number of the trip key
     */
    int m_stopNo = -1;
};
} // namespace NextSimIO

#endif
