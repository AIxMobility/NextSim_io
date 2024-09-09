/**
 * NextSim Captain
 * @file : InputDistribution.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <random>
#include <math.h>

#include <NextSim_io/inputclass/InputDistribution.hpp>

namespace NextSimIO
{

InputDistribution::InputDistribution(std::string vehdist, double vehmax, 
                      double vehmean, double vehmin, double vehsd)
    : vehdist{vehdist}, vehmax(vehmax), 
      vehmean(vehmean), vehmin(vehmin), vehsd(vehsd) {};

double InputDistribution::genValue(){
    std::random_device rd;
    std::mt19937 gen(rd());
    double value = -1;

    if (vehdist == "Normal")
    {
        std::normal_distribution<double> Ndist(vehmean, vehsd);
        while (value < vehmin || vehmax < value) {
            value = Ndist(gen);
        }
    }
    else if (vehdist == "LogNormal")
    {
        std::lognormal_distribution<double> LNdist(vehmean, vehsd);
        while (value < vehmin || vehmax < value) {
            value = LNdist(gen);
            value = log (value);
        }
    }

    return value;
}
} // namespace NextSimIO