#ifndef SCENARIO_H
#define SCENARIO_H

#include <vector>

class Scenario
{
private:
    std::vector<std::pair<int, int>> ODscenario;

public:
    Scenario();
    
    //access function
    std::vector<std::pair<int, int>> getScenario() { return ODscenario; }
};

#endif