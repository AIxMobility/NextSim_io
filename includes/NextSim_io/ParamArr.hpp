/**
 * NextSim Captain
 * @file : ParamArr.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#include <vector>
#include <string>

/**
 * @class ParamArr
 * @brief Class for whole parameter from param.xml
*/
class ParamArr
{
public:
    /**
     * @details Constructor
    */
    ParamArr();

    /**
     * @details Set mean value
     * @param val Mean value
     * @param str ???
    */
    void SetMean(double val, const char* str);
    void SetSd(double val, const char* str);

    /*
    SetModel
    description: set Dist value to a specific number depending on the model

    Model --> Type #
    
    Normal       --> 1
    Lognormal    --> 2

     */

    // ???
    void SetModel(const char* model, const char* str);

    /**
     * @details Set maximum flow
     * @param val Maximum flow [veh/hr]
    */
    void SetMaxFlow(double val) { max_flow = val; }

    /**
     * @details Set mesoscopic vehicle length
     * @param val Mesoscopic vehicle length [m]
    */
    void SetMesoVehLen(double val) { meso_veh_len = val; }

    /**
     * @details Set wave speed
     * @param val Wave speed [km/h]
    */
    void SetWaveSpeed(double val) { wave_speed = val; }

    //access functions
    /**
     * @details Get microscopic vehicle length
     * @return Microscopic vehicle length [m]
    */
    [[nodiscard]] const std::vector<double>& GetMicroVehLen() const
    {
        return micro_veh_len;
    }

    /**
     * @details Get jam gap
     * @return Jam gap [m]
    */
    [[nodiscard]] const std::vector<double>& GetJamGap() const
    {
        return jam_gap;
    }

    /**
     * @details Get free flow speed
     * @return Free flow speed [km/h]
    */
    [[nodiscard]] const std::vector<double>& GetFFSpeed() const
    {
        return ff_speed;
    }

    /**
     * @details Get reaction time
     * @return Reaction time [s]
    */
    [[nodiscard]] const std::vector<double>& GetReactionTime() const { return reaction_time; }

    /**
     * @details Get maximum acceleration
     * @return Maximum acceleration [m/s^2]
    */
    [[nodiscard]] const std::vector<double>& GetMaxAcc() const { return max_acc; }

    /**
     * @details Get maximum deceleration
     * @return Maximum deceleration [m/s^2]
    */
    [[nodiscard]] const std::vector<double>& GetMaxDec() const { return max_dec; }

    /**
     * @details Get maximum flow
     * @return Maximum flow [veh/hr]
    */
    [[nodiscard]] double GetMaxFlow() const { return max_flow; }

    /**
     * @details Get mesoscopic vehicle length
     * @return Mesoscopic vehicle length [m]
    */
    [[nodiscard]] double GetMesoVehLen() const { return meso_veh_len; }

    /**
     * @details Get wave speed
     * @return Wave speed [km/h]
    */
    [[nodiscard]] double GetWaveSpeed() const { return wave_speed; }

private:
    // Micro Param
    /**
     * @brief Microscopic vehicle length [m]
    */
    std::vector<double> micro_veh_len;

    /**
     * @brief Jam gap [m]
    */
    std::vector<double> jam_gap;

    /**
     * @brief Free flow speed [km/h]
    */
    std::vector<double> ff_speed;

    /**
     * @brief Reaction time [s]
    */
    std::vector<double> reaction_time;

    /**
     * @brief Maximum acceleration [m/s^2]
    */
    std::vector<double> max_acc;

    /**
     * @brief Maximum deceleration [m/s^2]
    */
    std::vector<double> max_dec;

    // Meso Param
    /**
     * @brief Maximum flow [veh/hr]
    */
    double max_flow;

    /**
     * @brief Mesoscopic vehicle length [m]
    */
    double meso_veh_len;

    /**
     * @brief Wave speed [km/h]
    */
    double wave_speed;
};
