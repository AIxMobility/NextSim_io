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

class InputDistribution
{
private:
    std::string vehdist;
    double vehmax;
    double vehmean;
    double vehmin;
    double vehsd;

public:
    // Constructor
    InputDistribution();
    InputDistribution(std::string vehdist, double vehmax, double vehmean, double vehmin, double vehsd);

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

    // access functions
    std::string getdist()
    {
        return vehdist;
    }
    double getmax()
    {
        return vehmax;
    }
    double getmean()
    {
        return vehmean;
    }
    double getmin()
    {
        return vehmin;
    }
    double getsd()
    {
        return vehsd;
    }
    void setdist(std::string newdist)
    {
        vehdist = newdist;
    }
    void setmax(double newmax)
    {
        vehmax = newmax;
    }
    void setmean(double newmean)
    {
        vehmean = newmean;
    }
    void setmin(double newmin)
    {
        vehmin = newmin;
    }
    void setsd(double newsd)
    {
        vehsd = newsd;
    }
};

#endif