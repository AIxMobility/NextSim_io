/**
 * NextSim Captain
 * @file : ScenarioArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef SCENARIOARR_H
#define SCENARIOARR_H

#include <vector>

#include <NextSim_io/inputclass/InputTOD.hpp>

namespace NextSimIO
{
/**
 * @class ScenarioArr
 * @brief Class for origin-destination scenario information from odscenario.xml
 */
class ScenarioArr
{
public:
    /**
     * @details Constructor (Parse OD scenario information from odscenario.xml)
     */
    ScenarioArr();
    
    /**
     * @details Get origin-destination scenario
     * @return OD scenario (Pair of simulation Iter ID and OD matrix ID)
    */
    std::vector<std::pair<int, int>> GetODScenarios() { return m_odScenarios; }

    /**
     * @details Get signal TOD information
     * @return Signal TOD information
    */
    std::vector<InputTOD> GetSignalTOD() { return m_signalTODs; }

private:
    /**
     * @details Pair of simulation Iter ID and OD matrix ID
     */
    std::vector<std::pair<int, int>> m_odScenarios;

    /**
     * @details Vector of signal TOD information
     */
    std::vector<InputTOD> m_signalTODs;
};
} // namespace NextSimIO

#endif