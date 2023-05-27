/**
 * STS19 Captain
 * @file : InputAgentTypes.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#ifndef INPUTAGENTTYPES_H
#define INPUTAGENTTYPES_H

#include <iostream>
#include <string>
#include <vector>

#include "InputDistribution.hpp"

class InputAgentTypes
{
private:
    std::string vehType;
    int max_pax;
    bool v2xActive;
    InputDistribution veh_len;
    InputDistribution jamgap;
    InputDistribution vf;
    InputDistribution reaction_time;
    InputDistribution max_acc;
    InputDistribution max_dec;
    // InputDistribution delta_jamgap;
    // InputDistribution b1;
    // InputDistribution b2;
    // InputDistribution c1;
    // InputDistribution c2;
    // InputDistribution c3;

public:
    // Constructor
    InputAgentTypes(std::string vehType, int max_pax, bool v2xActive, InputDistribution veh_len, InputDistribution jamgap, InputDistribution vf, InputDistribution reaction_time, InputDistribution max_acc, InputDistribution max_dec);

    // access functions
    std::string getvehType()
    {
        return vehType;
    }
    int getmax_pax()
    {
        return max_pax;
    }
    bool getv2xActive()
    {
        return v2xActive;
    }
    double genveh_len()
    {
        return veh_len.genValue();
    }
    double genjamgap()
    {
        return jamgap.genValue();
    }
    double genvf()
    {
        double newvf = vf.genValue();
        return newvf / 3.6;
    }
    double genreaction_time()
    {
        return reaction_time.genValue();
    }
    double genmax_acc()
    {
        return max_acc.genValue();
    }
    double genmax_dec()
    {
        return max_dec.genValue();
    }
    // double gendelta_jamgap()
    // {
    //     return delta_jamgap.genValue();
    // }
    // double genb1()
    // {
    //     return b1.genValue();
    // }
    // double genb2()
    // {
    //     return b2.genValue();
    // }
    // double genc1()
    // {
    //     return c1.genValue();
    // }
    // double genc2()
    // {
    //     return c2.genValue();
    // }
    // double genc3()
    // {
    //     return c3.genValue();
    // }
};

#endif