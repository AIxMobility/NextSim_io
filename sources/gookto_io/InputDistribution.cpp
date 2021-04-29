#include <string>
#include <iostream>

#include <gookto_io/InputDistribution.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

InputDistribution::InputDistribution() {};
InputDistribution::InputDistribution(std::string vehdist, double vehmax, double vehmean, double vehmin, double vehsd): vehdist{vehdist}, vehmax(vehmax), vehmean(vehmean), vehmin(vehmin), vehsd(vehsd) {};