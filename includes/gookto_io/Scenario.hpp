#ifndef SCENARIO_H
#define SCENARIO_H

#include <vector>

class Scenario
{
private:
    std::vector<std::pair<int, int>> ODscenario;

public:
    Scenario(const std::string& userName);
    
    //access function
    std::vector<std::pair<int, int>> getScenario() { return ODscenario; }
};

#endif