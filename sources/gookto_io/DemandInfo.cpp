#include <string>
#include <iostream>

#include <gookto_io/DemandInfo.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

DemandInfo::DemandInfo(int id, std::vector<Demand> demands)
    : id(id), demands(demands) {};