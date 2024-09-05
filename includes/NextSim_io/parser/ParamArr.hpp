/**
 * NextSim Captain
 * @file : ParamArr.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#include <vector>
#include <string>

namespace NextSimIO
{
/**
 * @class ParamArr
 * @brief Class for whole parameter from param.xml
*/
class ParamArr
{
public:
    /**
     * @details Constructor (Parse parameter information from param.xml)
    */
    ParamArr();

    /**
     * @details Set mean value
     * @param val Mean value
     * @param param Parameter type
    */
    void SetMean(double val, std::string param);

    /**
     * @details Set standard deviation
     * @param val Standard deviation
     * @param param Parameter type
    */
    void SetSd(double val, std::string param);

    /**
     * @details Set simulation parameters to a specific number depending on the model
     * @param model Model type (1: Normal, 2: Lognormal)
     * @param param Parameter type
     */
    void SetModel(std::string model, std::string param);

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
    /**
     * @brief Microscopic vehicle length [m] (for microscopic simulation)
    */
    std::vector<double> micro_veh_len;

    /**
     * @brief Jam gap [m] (for microscopic simulation)
    */
    std::vector<double> jam_gap;

    /**
     * @brief Free flow speed [km/h] (for microscopic simulation)
    */
    std::vector<double> ff_speed;

    /**
     * @brief Reaction time [s] (for microscopic simulation)
    */
    std::vector<double> reaction_time;

    /**
     * @brief Maximum acceleration [m/s^2] (for microscopic simulation)
    */
    std::vector<double> max_acc;

    /**
     * @brief Maximum deceleration [m/s^2] (for microscopic simulation)
    */
    std::vector<double> max_dec;

    /**
     * @brief Maximum flow [veh/hr] (for mesoscopic simulation)
    */
    double max_flow;

    /**
     * @brief Mesoscopic vehicle length [m] (for mesoscopic simulation)
    */
    double meso_veh_len;

    /**
     * @brief Wave speed [km/h] (for mesoscopic simulation)
    */
    double wave_speed;
};
} // namespace NextSimIO
