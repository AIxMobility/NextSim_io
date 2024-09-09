/**
 * NextSim Captain
 * @file : InputDistribution.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

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
private:

    /**
     * @details Distribution type (Normal, LogNormal)
     */
    std::string vehdist;

    /**
     * @details Maximum value
     */
    double vehmax;

    /**
     * @details Mean value
     */
    double vehmean;

    /**
     * @details Minimum value
     */
    double vehmin;

    /**
     * @details Standard deviation
     */
    double vehsd;

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
    double genValue();

    /**
     * @details Get distribution type
     * @return Distribution type (Normal, LogNormal)
    */
    std::string getdist() { return vehdist; }

    /**
     * @details Get maximum value of the distribution
     * @return Maximum value
    */
    double getmax() { return vehmax; }

    /**
     * @details Get mean value of the distribution
     * @return Mean value
    */
    double getmean() { return vehmean; }

    /**
     * @details Get minimum value of the distribution
     * @return Minimum value
    */
    double getmin() { return vehmin; }

    /**
     * @details Get standard deviation of the distribution
     * @return Standard deviation
    */
    double getsd() { return vehsd; }

    /**
     * @details Set distribution type
     * @param newdist Distribution type (Normal, LogNormal)
    */
    void setdist(std::string newdist) { vehdist = newdist; }

    /**
     * @details Set maximum value of the distribution
     * @param newmax Maximum value
    */
    void setmax(double newmax) { vehmax = newmax; }

    /**
     * @details Set mean value of the distribution
     * @param newmean Mean value
    */
    void setmean(double newmean) { vehmean = newmean; }

    /**
     * @details Set minimum value of the distribution
     * @param newmin Minimum value
    */
    void setmin(double newmin) { vehmin = newmin; }

    /**
     * @details Set standard deviation of the distribution
     * @param newsd Standard deviation
    */
    void setsd(double newsd) { vehsd = newsd; }
};
} // namespace NextSimIO

#endif