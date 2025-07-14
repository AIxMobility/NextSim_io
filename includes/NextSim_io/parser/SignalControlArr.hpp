/**
 * NextSim Captain
 * @file : SignalControlArr.hpp
 * @version : 1.0
 * @author : Chaemin Na
*/

#ifndef SIGNALCONTROLARR_H
#define SIGNALCONTROLARR_H

#include <NextSim_io/inputclass/InputSignalControl.hpp>

namespace NextSimIO
{
/**
 * @class SignalControlArr
 * @brief Class for signal controlled information 
 */
class SignalControlArr
{
public:
    /**
     * @details Constructor
    */
    SignalControlArr();
    
    /**
     * @details Get vector of all signal control
     * @return Vector of all signal control
    */
    std::vector<InputSignalControl> GetSignalControls() const { return m_signalControls; }

    /**
     * @details Set vector of signal control
     * @param signalControlList Vector of signal control
     */
    void SetSignalControls(const std::vector<InputSignalControl>& signalControls)
    {
        m_signalControls = signalControls;
    }

private:
    
    /**
     * @details sequence of signal control (node)
     */
    std::vector<InputSignalControl> m_signalControls;
};
} // namespace NextSimIO

#endif