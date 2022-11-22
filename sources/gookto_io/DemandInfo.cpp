#include <string>
#include <iostream>

#include <gookto_io/DemandInfo.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

DemandInfo::DemandInfo(int id, std::string type, std::vector<Demand> demands)
    : id(id), type(type), demands(demands){};