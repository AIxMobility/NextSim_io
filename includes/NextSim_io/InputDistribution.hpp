/**
 * NextSim Captain
 * @file : InputDistribution.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTDISTRIBUTION_H
#define INPUTDISTRIBUTION_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <math.h>

/**
 * @class InputDistribution
 * @brief Class for each distribution information
 */
class InputDistribution
{
private:

    /**
     * @details Distribution type (Normal, LogNormal) ???
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
    InputDistribution();

    /**
     * @details Constructor
     * @param vehdist Distribution type
     * @param vehmax Maximum value
     * @param vehmean Mean value
     * @param vehmin Minimum value
     * @param vehsd Standard deviation
    */
    InputDistribution(std::string vehdist, double vehmax, double vehmean, double vehmin, double vehsd);

    /**
     * @details Generate a random value based on the distribution
     * @return Random value
    */
    double genValue(){
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

    /**
     * @details Get distribution type
     * @return Distribution type (Normal, LogNormal) ???
    */
    std::string getdist()
    {
        return vehdist;
    }

    /**
     * @details Get maximum value
     * @return Maximum value
    */
    double getmax()
    {
        return vehmax;
    }

    /**
     * @details Get mean value
     * @return Mean value
    */
    double getmean()
    {
        return vehmean;
    }

    /**
     * @details Get minimum value
     * @return Minimum value
    */
    double getmin()
    {
        return vehmin;
    }

    /**
     * @details Get standard deviation
     * @return Standard deviation
    */
    double getsd()
    {
        return vehsd;
    }

    /**
     * @details Set distribution type
     * @param newdist Distribution type (Normal, LogNormal)
    */
    void setdist(std::string newdist)
    {
        vehdist = newdist;
    }

    /**
     * @details Set maximum value
     * @param newmax Maximum value
    */
    void setmax(double newmax)
    {
        vehmax = newmax;
    }

    /**
     * @details Set mean value
     * @param newmean Mean value
    */
    void setmean(double newmean)
    {
        vehmean = newmean;
    }

    /**
     * @details Set minimum value
     * @param newmin Minimum value
    */
    void setmin(double newmin)
    {
        vehmin = newmin;
    }

    /**
     * @details Set standard deviation
     * @param newsd Standard deviation
    */
    void setsd(double newsd)
    {
        vehsd = newsd;
    }
};

#endif