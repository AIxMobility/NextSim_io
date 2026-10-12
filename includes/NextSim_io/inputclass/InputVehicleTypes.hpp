/**
 * NextSim Captain
 * @file : InputVehicleTypes.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#pragma once
#ifndef INPUTVEHICLETYPES_H
#define INPUTVEHICLETYPES_H

#include <array>
#include <random>
#include <string>
#include <vector>

#include "InputDistribution.hpp"

namespace NextSimIO
{
/**
 * @class InputVehicleTypes
 * @brief Class for agent types information from agenttypes.xml
*/
class InputVehicleTypes
{
public:
    /**
     * @details Constructor
     * @param vehType Vehicle type
     * @param maxPax Maximum number of passengers
     * @param v2xActive Whether V2X is active or not
     * @param vehLen Vehicle length
     * @param vehWidth Vehicle width
     * @param jamgap Jam gap
     * @param vf Free flow speed
     * @param reactionTime Reaction time
     * @param maxAcc Maximum acceleration
     * @param maxDec Maximum deceleration
     * @param lcParam1 Lane change parameter 1
     * @param lcParam2 Lane change parameter 2
     * @param lcSensitivity Lane change sensitivity
     * @param powertrainRatios ICE, PHEV, and BEV ratios in that order
    */
    InputVehicleTypes(
        std::string vehType, 
        int maxPax, 
        bool v2xActive, 
        InputDistribution vehLen, 
        InputDistribution vehWidth,
        InputDistribution jamgap, 
        InputDistribution vf, 
        InputDistribution reactionTime, 
        InputDistribution maxAcc, 
        InputDistribution maxDec,
        InputDistribution lcParam1,
        InputDistribution lcParam2,
        InputDistribution lcSensitivity,
        std::array<double, 3> powertrainRatios = {1.0, 0.0, 0.0});

    /**
     * @details Get vehicle type
     * @return Vehicle type (NV: Normal Vehicle, AV: Autonomous Vehicle, TR: Truck)
    */
    std::string GetVehType() { return m_vehType; }

    /**
     * @details Get maximum number of passengers
     * @return Maximum number of passengers
    */
    int GetMaxPax() { return m_maxPax; }

    /**
     * @details Get whether V2X is active or not
     * @return True(active) or False(not active)
    */
    bool GetV2XActive() { return m_v2xActive; }

    /**
     * @details Get ICE, PHEV, and BEV ratios in that order
     * @return Powertrain ratios
    */
    const std::array<double, 3>& GetPowertrainRatios() const
    {
        return m_powertrainRatios;
    }

    /**
     * @details Generate vehicle length
     * @param generator Random generator
     * @return Vehicle length [m]
    */
    double GenVehLen(std::mt19937& generator) { return m_vehLen.GenValue(generator); }

    /**
     * @details Generate vehicle width
     * @param generator Random generator
     * @return Vehicle width [m]
    */
    double GenVehWidth(std::mt19937& generator) { return m_vehWidth.GenValue(generator); }

    /**
     * @details Generate jam gap
     * @param generator Random generator
     * @return Jam gap [m]
    */
    double GenJamgap(std::mt19937& generator) { return m_jamgap.GenValue(generator); }

    /**
     * @details Generate free flow speed
     * @param generator Random generator
     * @return Free flow speed [m/s]
    */
    double GenVf(std::mt19937& generator) { return m_vf.GenValue(generator) / 3.6; }
    
    /**
     * @details Generate reaction time
     * @param generator Random generator
     * @return Reaction time [s]
    */
    double GenReactionTime(std::mt19937& generator) { return m_reactionTime.GenValue(generator); }

    /**
     * @details Generate maximum acceleration
     * @param generator Random generator
     * @return Maximum acceleration [m/s^2]
    */
    double GenMaxAcc(std::mt19937& generator) { return m_maxAcc.GenValue(generator); }

    /**
     * @details Generate maximum deceleration
     * @param generator Random generator
     * @return Maximum deceleration [m/s^2]
    */
    double GenMaxDec(std::mt19937& generator) { return m_maxDec.GenValue(generator); }

    /**
     * @details Generate lane change parameter 1 and 2
     * @param generator Random generator
     * @return Pair of lane change parameter 1 and 2 [m/veh, s/m]
    */
    std::pair<double, double> GenLcParam(std::mt19937& generator)
    {
        const auto lcParam1 = m_lcParam1.GenValue(generator);
        const auto lcParam2 = m_lcParam2.GenValue(generator);
        return std::make_pair(lcParam1, lcParam2);
    }

    /**
     * @details Generate lane change sensitivity
     * @param generator Random generator
     * @return Lane change sensitivity [.]
    */
    double GenLcSensitivity(std::mt19937& generator) { return m_lcSensitivity.GenValue(generator); }
    
    // double GenDeltaJamgap()
    // {
    //     return m_deltaJamgap.GenValue();
    // }
    // double Genb1()
    // {
    //     return m_b1.GenValue();
    // }
    // double Genb2()
    // {
    //     return m_b2.GenValue();
    // }
    // double Genc1()
    // {
    //     return m_c1.GenValue();
    // }
    // double Genc2()
    // {
    //     return m_c2.GenValue();
    // }
    // double Genc3()
    // {
    //     return m_c3.GenValue();
    // }

private:
    /**
     * @details Vehicle type (NV: Normal Vehicle, AV: Autonomous Vehicle, TR: Truck)
    */
    std::string m_vehType;

    /**
     * @details Maximum number of passengers
    */
    int m_maxPax;

    /**
     * @details Whether V2X is active or not
    */
    bool m_v2xActive;

    /**
     * @details ICE, PHEV, and BEV ratios in that order
    */
    std::array<double, 3> m_powertrainRatios;

    /**
     * @details Vehicle length [m]
    */
    InputDistribution m_vehLen;

    /**
     * @details Vehicle width [m]
    */
    InputDistribution m_vehWidth;

    /**
     * @details Jam gap [m]
    */
    InputDistribution m_jamgap;

    /**
     * @details Free flow speed [km/h]
    */
    InputDistribution m_vf;

    /**
     * @details Reaction time [s]
    */
    InputDistribution m_reactionTime;

    /**
     * @details Maximum acceleration [m/s^2]
    */
    InputDistribution m_maxAcc;

    /**
     * @details Maximum deceleration [m/s^2]
    */
    InputDistribution m_maxDec;

    /**
     * @details Lane change parameter 1 [m/veh]
    */
    InputDistribution m_lcParam1;

    /**
     * @details Lane change parameter 2 [s/m]
    */
    InputDistribution m_lcParam2;

    /**
     * @details Lane change sensitivity [.]
    */
    InputDistribution m_lcSensitivity;

    // InputDistribution m_deltaJamgap;
    // InputDistribution m_b1;
    // InputDistribution m_b2;
    // InputDistribution m_c1;
    // InputDistribution m_c2;
    // InputDistribution m_c3;
};
} // namespace NextSimIO

#endif
