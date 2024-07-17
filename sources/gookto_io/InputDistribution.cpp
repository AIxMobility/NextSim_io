/**
 * NextSim Captain
 * @file : InputDistribution.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <string>
#include <iostream>

#include <gookto_io/InputDistribution.hpp>

InputDistribution::InputDistribution() {};
InputDistribution::InputDistribution(std::string vehdist, double vehmax, double vehmean, double vehmin, double vehsd): vehdist{vehdist}, vehmax(vehmax), vehmean(vehmean), vehmin(vehmin), vehsd(vehsd) {};