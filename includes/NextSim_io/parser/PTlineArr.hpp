/**
 * NextSim Captain
 * @file : PTlineArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef PTROUTEARR_H
#define PTROUTEARR_H

#include <vector>
#include <NextSim_io/inputclass/InputPTline.hpp>

namespace NextSimIO
{
/**
 * @class PTlineArr
 * @brief Class for whole public transit line information from roadptline.xml
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
    std::vector<InputPTline> GetBusLines()
    {
        return m_busLines;
    }

    /**
     * @details Get vector of public transit lines for TRT
     * @return Vector of public transit lines for TRT
    */
    std::vector<InputPTline> GetTRTLines()
    {
        return m_trtLines;
    }

    /**
     * @details Get vector of public transit lines for Tram
     * @return Vector of public transit lines for Tram
    */
    std::vector<InputPTline> GetTramLines()
    {
        return m_tramLines;
    }

private:
    /**
     * @details Vector of public transit lines
    */
    std::vector<InputPTline> m_busLines;

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