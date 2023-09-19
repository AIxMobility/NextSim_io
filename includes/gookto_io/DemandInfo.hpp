#ifndef DEMANDINFO_H
#define DEMANDINFO_H

#include <vector>
#include <string>
#include <iostream>
#include "Demand.hpp"

class DemandInfo
{
private:
    int id;
    std::vector<NVdemand> nvdemands;
    std::vector<PVdemand> pvdemands;

public:
    DemandInfo(int id,
               std::vector<NVdemand> nvdemands, 
               std::vector<PVdemand> pvdemands);

    int getId() { return id; }
    std::vector<NVdemand> getNVdemands() { return nvdemands; }
    std::vector<PVdemand> getPVdemands() { return pvdemands; }
};

#endif