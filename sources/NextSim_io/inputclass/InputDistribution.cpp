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
std::mt19937& DistributionEngine()
{
    static thread_local std::mt19937 engine(std::random_device {}());
    return engine;
}

void SeedDistributionEngine(std::uint32_t seed)
{
    DistributionEngine().seed(seed);
}

InputDistribution::InputDistribution(std::string vehdist, double vehmax, 
                      double vehmean, double vehmin, double vehsd)
    : m_vehDist(vehdist), m_vehMax(vehmax), m_vehMean(vehmean), m_vehMin(vehmin), m_vehSD(vehsd) {}

double InputDistribution::GenValue(){
    auto& gen = DistributionEngine();
    double value = -1;

    if (m_vehDist == "Normal")
    {
        std::normal_distribution<double> Ndist(m_vehMean, m_vehSD);
        while (value < m_vehMin || m_vehMax < value) {
            value = Ndist(gen);
        }
    }
    else if (m_vehDist == "LogNormal")
    {
        std::lognormal_distribution<double> LNdist(m_vehMean, m_vehSD);
        while (value < m_vehMin || m_vehMax < value) {
            value = LNdist(gen);
            value = log (value);
        }
    }

    return value;
}
} // namespace NextSimIO