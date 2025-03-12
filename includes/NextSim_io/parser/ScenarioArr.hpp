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
#include <NextSim_io/inputclass/InputScenario.hpp>

namespace NextSimIO
{
/**
 * @class ScenarioArr
 * @brief Class for scenario information from scenario.xml
 */
class ScenarioArr
{
public:
    /**
     * @details Constructor
     */
    ScenarioArr();
    
    /**
     * @details Get scenario information
     * @return Scenario information (Vector of InputScenario)
    */
    std::vector<InputScenario> GetScenarios() { return m_scenarios; }

private:
    /**
     * @details Vector of scenario information
     */
    std::vector<InputScenario> m_scenarios;
};
} // namespace NextSimIO

#endif