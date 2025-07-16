/**
 * NextSim Captain
 * @file : InputVehicleTypes.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#pragma once
#ifndef INPUTVEHICLETYPES_H
#define INPUTVEHICLETYPES_H

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
        InputDistribution lcSensitivity);

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
    bool GetV2xActive() { return m_v2xActive; }

    /**
     * @details Generate vehicle length
     * @return Vehicle length [m]
    */
    double GenVehLen() { return m_vehLen.GenValue(); }

    /**
     * @details Generate vehicle width
     * @return Vehicle width [m]
    */
    double GenVehWidth() { return m_vehWidth.GenValue(); }

    /**
     * @details Generate jam gap
     * @return Jam gap [m]
    */
    double GenJamgap() { return m_jamgap.GenValue(); }

    /**
     * @details Generate free flow speed
     * @return Free flow speed [m/s]
    */
    double GenVf() { return m_vf.GenValue() / 3.6; }
    
    /**
     * @details Generate reaction time
     * @return Reaction time [s]
    */
    double GenReactionTime() { return m_reactionTime.GenValue(); }

    /**
     * @details Generate maximum acceleration
     * @return Maximum acceleration [m/s^2]
    */
    double GenMaxAcc() { return m_maxAcc.GenValue(); }

    /**
     * @details Generate maximum deceleration
     * @return Maximum deceleration [m/s^2]
    */
    double GenMaxDec() { return m_maxDec.GenValue(); }

    /**
     * @details Generate lane change parameter 1 and 2
     * @return Pair of lane change parameter 1 and 2 [m/veh, s/m]
    */
    std::pair<double, double> GenLcParam()
    {
        return std::make_pair(
            m_lcParam1.GenValue(), m_lcParam2.GenValue());
    }

    /**
     * @details Generate lane change sensitivity
     * @return Lane change sensitivity [.]
    */
    double GenLcSensitivity() { return m_lcSensitivity.GenValue(); }
    
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