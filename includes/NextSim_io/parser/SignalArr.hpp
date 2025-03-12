/**
 * NextSim Captain
 * @file : SignalArr.hpp
 * @version : 1.0
 * @author : Sujae Jeon
*/

#ifndef SIGNALARR_H
#define SIGNALARR_H

#include <NextSim_io/inputclass/InputSignal.hpp>
#include <NextSim_io/inputclass/InputTOD.hpp>

namespace NextSimIO
{
/**
 * @class SignalArr
 * @brief Class for whole signal information from network.xml
 */
class SignalArr
{
public:
    /**
     * @details Constructor (Parse signal information from network.xml)
    */
    SignalArr();

    /**
     * @details Get vector of all signal plans
     * @return Vector of all signal plans
    */
    std::vector<InputSignal> GetSignals() { return m_signals; }

    /**
     * @details Get vector of all signal TODs
     * @return Vector of all signal TODs
    */
    std::vector<InputTOD> GetSignalTODs() { return m_signalTODs; }

private:
    /**
     * @details Vector of all signal plans
    */
    std::vector<InputSignal> m_signals;

    /**
     * @details Vector of all signal TODs
    */
    std::vector<InputTOD> m_signalTODs;
};
} // namespace NextSimIO

#endif