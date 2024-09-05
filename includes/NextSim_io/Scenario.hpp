/**
 * NextSim Captain
 * @file : Scenario.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef SCENARIO_H
#define SCENARIO_H

#include <vector>

namespace NextSimIO
{
/**
 * @class Scenario
 * @brief Class for each origin-destination scenario information from odscenario.xml
 */
class Scenario
{
private:
    /**
     * @details Pair of origin and destination node ID
     */
    // ??? ODscenario는 matrix용인가? pt line 용인가? 우선 matrix 같아서 node ID로 적어놓음
    std::vector<std::pair<int, int>> ODscenario;

public:
    /**
     * @details Constructor
     * @param ODscenario Pair of origin and destination node ID
     */
    Scenario();
    
    /**
     * @details Get origin-destination scenario
     * @return Pair of origin and destination node ID
    */
    std::vector<std::pair<int, int>> getScenario() { return ODscenario; }
};
} // namespace NextSimIO

#endif