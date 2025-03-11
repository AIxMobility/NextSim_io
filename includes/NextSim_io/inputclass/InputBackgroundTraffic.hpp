/**
 * NextSim Captain
 * @file : InputBackgroundTraffic.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef INPUTBACKGROUNDTRAFFIC_H
#define INPUTBACKGROUNDTRAFFIC_H

#include "InputFlow.hpp"

namespace NextSimIO
{
/**
 * @class InputBackgroundTraffic
 * @brief Class for background traffic state
*/
class InputBackgroundTraffic
{
public:

    /**
     * @details Constructor
     * @param id Link ID
     * @param avgSpd Average speed of link
     * @param density Density of link
    */
    InputBackgroundTraffic(int id, double avgSpd, double density);
    
    /**
     * @details Get link ID
     * @return Link ID
    */
    int GetId() { return m_id; }

    /**
     * @details Get average speed of link
     * @return Average speed of link
    */
    double GetAvgSpd() { return m_avgSpd; }

    /**
     * @details Get density of link
     * @return Density of link
    */
    double GetDensity() { return m_density; }

private:

    /**
     * @details Link ID
    */
    int m_id;

    /**
     * @details Average speed of link
    */
    double m_avgSpd;

    /**
     * @details Density of link
    */
    double m_density;
};
} // namespace NextSimIO

#endif