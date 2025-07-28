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
    std::unordered_map<Captain::UnitIdentifier, InputSignalControl> GetSignalControlMap() const { return m_signalControlMap; }

    /**
     * @details Get signal control for a specific node
     * @param nodeIdentifier Node identifier to get the signal control for
     * @return InputSignalControl for the specified node
     */
    InputSignalControl GetSignalControlMap(Captain::UnitIdentifier nodeIdentifier) const   
    {
        auto it = m_signalControlMap.find(nodeIdentifier);
        if (it != m_signalControlMap.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("Signal control for the specified node not found");
        }
    }

    /**
     * @details Set vector of signal control
     * @param nodeIdentifier Node identifier to set the signal control for
     * @param inputSignalControl InputSignalControl object containing signal control information
     */
    void SetSignalControlMap(Captain::UnitIdentifier nodeIdentifier, const InputSignalControl& inputSignalControl)
    {
        m_signalControlMap[nodeIdentifier] = inputSignalControl;
    }

private:
    
    /**
     * @details map of signal control information
     * Key: Node Identifier \n
     * Value: InputSignalControl object containing signal control information
     */
   std::unordered_map<Captain::UnitIdentifier, InputSignalControl> m_signalControlMap;
};
} // namespace NextSimIO

#endif