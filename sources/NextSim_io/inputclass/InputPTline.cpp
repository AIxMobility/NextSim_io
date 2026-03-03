/**
 * NextSim Captain
 * @file : InputPTline.cpp
 * @version : 1.1
 * @author : Sujae Jeon, Dongheon Lee
 */

#include <sstream>

#include <NextSim_io/inputclass/InputPTline.hpp>

namespace NextSimIO
{
//class InputPTlink
InputPTlink::InputPTlink(int id, int sequence, bool usePTlane)
    : m_id(id), m_sequence(sequence), m_usePTlane(usePTlane) {}


//class InputPTline
InputPTline::InputPTline(std::string id, double fee, double interval) 
    : m_id(std::move(id)), m_fee(fee), m_interval(interval) {}

/**
 * @details Push a PTlink to the PTlink sequence
 * @param ptlink InputPTlink object to be added
 */
void InputPTline::PushPTlink(InputPTlink ptlink)
{
    m_PTlinkSeq.push_back(ptlink);
}

/**
 * @details Set sequence of links
 * @param stationSeq Space-separated sequence of station IDs
 */
void InputPTline::SetStationSeq(std::string stationSeq)
{
    std::stringstream ss(stationSeq);
    int stationid;

    while (ss >> stationid)
        m_stationSeq.push_back(stationid);
}

void InputPTline::PushStationSeq(int stationID)
{
    m_stationSeq.push_back(stationID);
}

/**
 * @details Set sequence of garages for rail transit
 * @param garageSeq Space-separated sequence of garage IDs
 */
void InputPTline::SetGarageSeq(std::string garageSeq)
{
    std::stringstream ss(garageSeq);
    int garageID;
    while (ss >> garageID)
        m_garageSeq.push_back(garageID);
}

void InputPTline::PushGarageSeq(int garageID)
{
    m_garageSeq.push_back(garageID);
} 
}// namespace NextSimIO