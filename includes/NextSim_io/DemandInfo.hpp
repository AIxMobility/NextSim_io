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
    std::vector<Demand> demands;


public:
    DemandInfo(int id,
               std::vector<Demand> demands);

    int getId() { return id; }
    std::vector<Demand> getDemands() { return demands; }
};

#endif