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
    void SetMaxFlow(double val) { m_maxFlow = val; }

    /**
     * @details Set mesoscopic vehicle length
     * @param val Mesoscopic vehicle length [m]
    */
    void SetMesoVehLen(double val) { m_mesoVehLen = val; }

    /**
     * @details Set wave speed
     * @param val Wave speed [km/h]
    */
    void SetWaveSpeed(double val) { m_waveSpeed = val; }

    /**
     * @details Get microscopic vehicle length
     * @return Microscopic vehicle length [m]
    */
    [[nodiscard]] const std::vector<double>& GetMicroVehLen() const
    {
        return m_microVehLen;
    }

    /**
     * @details Get jam gap
     * @return Jam gap [m]
    */
    [[nodiscard]] const std::vector<double>& GetJamgap() const
    {
        return m_jamgap;
    }

    /**
     * @details Get free flow speed
     * @return Free flow speed [km/h]
    */
    [[nodiscard]] const std::vector<double>& GetFFSpeed() const
    {
        return m_ffSpeed;
    }

    /**
     * @details Get reaction time
     * @return Reaction time [s]
    */
    [[nodiscard]] const std::vector<double>& GetReactionTime() const { return m_reactionTime; }

    /**
     * @details Get maximum acceleration
     * @return Maximum acceleration [m/s^2]
    */
    [[nodiscard]] const std::vector<double>& GetMaxAcc() const { return m_maxAcc; }

    /**
     * @details Get maximum deceleration
     * @return Maximum deceleration [m/s^2]
    */
    [[nodiscard]] const std::vector<double>& GetMaxDec() const { return m_maxDec; }

    /**
     * @details Get maximum flow
     * @return Maximum flow [veh/hr]
    */
    [[nodiscard]] double GetMaxFlow() const { return m_maxFlow; }

    /**
     * @details Get mesoscopic vehicle length
     * @return Mesoscopic vehicle length [m]
    */
    [[nodiscard]] double GetMesoVehLen() const { return m_mesoVehLen; }

    /**
     * @details Get wave speed
     * @return Wave speed [km/h]
    */
    [[nodiscard]] double GetWaveSpeed() const { return m_waveSpeed; }

private:
    /**
     * @brief Microscopic vehicle length [m] (for microscopic simulation)
    */
    std::vector<double> m_microVehLen;

    /**
     * @brief Jam gap [m] (for microscopic simulation)
    */
    std::vector<double> m_jamgap;

    /**
     * @brief Free flow speed [km/h] (for microscopic simulation)
    */
    std::vector<double> m_ffSpeed;

    /**
     * @brief Reaction time [s] (for microscopic simulation)
    */
    std::vector<double> m_reactionTime;

    /**
     * @brief Maximum acceleration [m/s^2] (for microscopic simulation)
    */
    std::vector<double> m_maxAcc;

    /**
     * @brief Maximum deceleration [m/s^2] (for microscopic simulation)
    */
    std::vector<double> m_maxDec;

    /**
     * @brief Maximum flow [veh/hr] (for mesoscopic simulation)
    */
    double m_maxFlow;

    /**
     * @brief Mesoscopic vehicle length [m] (for mesoscopic simulation)
    */
    double m_mesoVehLen;

    /**
     * @brief Wave speed [km/h] (for mesoscopic simulation)
    */
    double m_waveSpeed;
};
} // namespace NextSimIO
