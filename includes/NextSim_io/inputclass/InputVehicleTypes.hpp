/**
 * NextSim Captain
 * @file : InputVehicleTypes.hpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

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
private:

    /**
     * @details Vehicle type (NV: Normal Vehicle, AV: Autonomous Vehicle, TR: Truck)
    */
    std::string vehType;

    /**
     * @details Maximum number of passengers
    */
    int max_pax;

    /**
     * @details Whether V2X is active or not
    */
    bool v2xActive;

    /**
     * @details Vehicle length [m]
    */
    InputDistribution veh_len;

    /**
     * @details Jam gap [m]
    */
    InputDistribution jamgap;

    /**
     * @details Free flow speed [km/h]
    */
    InputDistribution vf;

    /**
     * @details Reaction time [s]
    */
    InputDistribution reaction_time;

    /**
     * @details Maximum acceleration [m/s^2]
    */
    InputDistribution max_acc;

    /**
     * @details Maximum deceleration [m/s^2]
    */
    InputDistribution max_dec;

    /**
     * @details Lane change parameter 1 [m/veh]
    */
    InputDistribution lc_param1;

    /**
     * @details Lane change parameter 2 [s/m]
    */
    InputDistribution lc_param2;

    /**
     * @details Lane change sensitivity [.]
    */
    InputDistribution lc_sensitivity;

    // InputDistribution delta_jamgap;
    // InputDistribution b1;
    // InputDistribution b2;
    // InputDistribution c1;
    // InputDistribution c2;
    // InputDistribution c3;

public:
    /**
     * @details Constructor
     * @param vehType Vehicle type
     * @param max_pax Maximum number of passengers
     * @param v2xActive Whether V2X is active or not
     * @param veh_len Vehicle length
     * @param jamgap Jam gap
     * @param vf Free flow speed
     * @param reaction_time Reaction time
     * @param max_acc Maximum acceleration
     * @param max_dec Maximum deceleration
     * @param lc_param1 Lane change parameter 1
     * @param lc_param2 Lane change parameter 2
     * @param lc_sensitivity Lane change sensitivity
    */
    InputVehicleTypes(
        std::string vehType, 
        int max_pax, 
        bool v2xActive, 
        InputDistribution veh_len, 
        InputDistribution jamgap, 
        InputDistribution vf, 
        InputDistribution reaction_time, 
        InputDistribution max_acc, 
        InputDistribution max_dec,
        InputDistribution lc_param1,
        InputDistribution lc_param2,
        InputDistribution lc_sensitivity);

    /**
     * @details Get vehicle type
     * @return Vehicle type (NV: Normal Vehicle, AV: Autonomous Vehicle, TR: Truck)
    */
    std::string getvehType() { return vehType; }

    /**
     * @details Get maximum number of passengers
     * @return Maximum number of passengers
    */
    int getmax_pax() { return max_pax; }

    /**
     * @details Get whether V2X is active or not
     * @return True(active) or False(not active)
    */
    bool getv2xActive() { return v2xActive; }

    /**
     * @details Generate vehicle length
     * @return Vehicle length [m]
    */
    double genveh_len() { return veh_len.genValue(); }

    /**
     * @details Generate jam gap
     * @return Jam gap [m]
    */
    double genjamgap() { return jamgap.genValue(); }

    /**
     * @details Generate free flow speed
     * @return Free flow speed [m/s]
    */
    double genvf() { return vf.genValue() / 3.6; }
    
    /**
     * @details Generate reaction time
     * @return Reaction time [s]
    */
    double genreaction_time() { return reaction_time.genValue(); }

    /**
     * @details Generate maximum acceleration
     * @return Maximum acceleration [m/s^2]
    */
    double genmax_acc() { return max_acc.genValue(); }

    /**
     * @details Generate maximum deceleration
     * @return Maximum deceleration [m/s^2]
    */
    double genmax_dec() { return max_dec.genValue(); }

    /**
     * @details Generate lane change parameter 1 and 2
     * @return Pair of lane change parameter 1 and 2 [m/veh, s/m]
    */
    std::pair<double, double> genLCparam()
    {
        return std::make_pair(
            lc_param1.genValue(), lc_param2.genValue());
    }

    /**
     * @details Generate lane change sensitivity
     * @return Lane change sensitivity [.]
    */
    double genLCsensitivity() { return lc_sensitivity.genValue(); }
    
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
} // namespace NextSimIO

#endif