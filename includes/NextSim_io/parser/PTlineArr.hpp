/**
 * NextSim Captain
 * @file : PTlineArr.hpp
 * @version : 1.1
 * @author : Sujae Jeon, Yeonwoo Yu
 */

#ifndef PTROUTEARR_H
#define PTROUTEARR_H

#include <vector>
#include <NextSim_io/inputclass/InputPTline.hpp>

namespace NextSimIO
{
/**
 * @class PTlineArr
 * @brief Class for road public transit line information
 */
class PTlineArr
{
public:
    /**
     * @details Constructor (Parse public transit line information from roadptline.xml)
    */
    PTlineArr();
    
    /**
     * @details Get vector of public transit lines
     * @return Vector of public transit lines
    */
    std::vector<InputPTline> GetBusLines() const
    {
        return m_busLines;
    }

    /**
     * @details Get vector of public transit lines for autonomous bus
     * @return Vector of public transit lines for autonomous bus
    */
    std::vector<InputPTline> GetAutonomousBusLines() const
    {
        return m_autonomousBusLines;
    }

    /**
     * @details Get vector of public transit lines for TRT
     * @return Vector of public transit lines for TRT
    */
    std::vector<InputPTline> GetTRTLines() const
    {
        return m_trtLines;
    }

    /**
     * @details Get vector of public transit lines for Tram
     * @return Vector of public transit lines for Tram
    */
    std::vector<InputPTline> GetTramLines() const
    {
        return m_tramLines;
    }

private:
    /**
     * @details Vector of public transit lines for normal bus
    */
    std::vector<InputPTline> m_busLines;

    /**
     * @details Vector of public transit lines for autonomous bus
     */
    std::vector<InputPTline> m_autonomousBusLines;

    /**
     * @details Vector of public transit lines for TRT
    */
    std::vector<InputPTline> m_trtLines;

    /**
     * @details Vector of public transit lines for Tram
    */
    std::vector<InputPTline> m_tramLines;
};
} // namespace NextSimIO

#endif
