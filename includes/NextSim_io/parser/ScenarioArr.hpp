/**
 * NextSim Captain
 * @file : ScenarioArr.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef SCENARIOARR_H
#define SCENARIOARR_H

#include <vector>

namespace NextSimIO
{
/**
 * @class ScenarioArr
 * @brief Class for origin-destination scenario information from odscenario.xml
 */
class ScenarioArr
{
private:
    /**
     * @details Pair of simulation Iter ID and OD matrix ID
     */
    std::vector<std::pair<int, int>> ODscenario;

public:
    /**
     * @details Constructor (Parse OD scenario information from odscenario.xml)
     */
    ScenarioArr();
    
    /**
     * @details Get origin-destination scenario
     * @return OD scenario (Pair of simulation Iter ID and OD matrix ID)
    */
    std::vector<std::pair<int, int>> getScenario() { return ODscenario; }
};
} // namespace NextSimIO

#endif