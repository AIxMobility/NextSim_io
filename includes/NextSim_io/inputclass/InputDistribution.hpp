/**
 * NextSim Captain
 * @file : InputDistribution.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#pragma once
#ifndef INPUTDISTRIBUTION_H
#define INPUTDISTRIBUTION_H

#include <string>
#include <vector>

namespace NextSimIO
{
/**
 * @class InputDistribution
 * @brief Class for distribution information for each vehicle characteristic
 */
class InputDistribution
{
public:

    /**
     * @details Constructor
    */
    InputDistribution() {};

    /**
     * @details Constructor
     * @param vehdist Distribution type
     * @param vehmax Maximum value
     * @param vehmean Mean value
     * @param vehmin Minimum value
     * @param vehsd Standard deviation
    */
    InputDistribution(std::string vehdist, double vehmax, 
                      double vehmean, double vehmin, double vehsd);

    /**
     * @details Generate a random value based on the distribution
     * @return Random characteristic value
    */
    double GenValue();

    /**
     * @details Get distribution type
     * @return Distribution type (Normal, LogNormal)
    */
    std::string GetDist() { return m_vehDist; }

    /**
     * @details Get maximum value of the distribution
     * @return Maximum value
    */
    double GetMax() { return m_vehMax; }

    /**
     * @details Get mean value of the distribution
     * @return Mean value
    */
    double GetMean() { return m_vehMean; }

    /**
     * @details Get minimum value of the distribution
     * @return Minimum value
    */
    double GetMin() { return m_vehMin; }

    /**
     * @details Get standard deviation of the distribution
     * @return Standard deviation
    */
    double GetSD() { return m_vehSD; }

    /**
     * @details Set distribution type
     * @param newdist Distribution type (Normal, LogNormal)
    */
    void SetDist(std::string newdist) { m_vehDist = newdist; }

    /**
     * @details Set maximum value of the distribution
     * @param newmax Maximum value
    */
    void SetMax(double newmax) { m_vehMax = newmax; }

    /**
     * @details Set mean value of the distribution
     * @param newmean Mean value
    */
    void SetMean(double newmean) { m_vehMean = newmean; }

    /**
     * @details Set minimum value of the distribution
     * @param newmin Minimum value
    */
    void SetMin(double newmin) { m_vehMin = newmin; }

    /**
     * @details Set standard deviation of the distribution
     * @param newsd Standard deviation
    */
    void SetSD(double newsd) { m_vehSD = newsd; }

private:

    /**
     * @details Distribution type (Normal, LogNormal)
     */
    std::string m_vehDist;

    /**
     * @details Maximum value
     */
    double m_vehMax;

    /**
     * @details Mean value
     */
    double m_vehMean;

    /**
     * @details Minimum value
     */
    double m_vehMin;

    /**
     * @details Standard deviation
     */
    double m_vehSD;
};
} // namespace NextSimIO

#endif