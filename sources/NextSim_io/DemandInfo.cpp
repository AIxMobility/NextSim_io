#include <string>
#include <iostream>

#include <NextSim_io/DemandInfo.hpp>

#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/tinyapi/tinystr.h>

DemandInfo::DemandInfo(int id, std::vector<Demand> demands)
    : id(id), demands(demands) {};