/**
 * NextSim Captain
 * @file : InputSignalControl.hpp
 * @version : 1.0
 * @author : Chaemin Na
*/

#pragma once
#ifndef INPUTSIGNALCONTROL_H
#define INPUTSIGNALCONTROL_H

#include "signal/plan.hpp"
#include "signal/turn.hpp"
#include <captain/Structs/GeneralStructs.hpp>

namespace NextSimIO
{
/**
 * @class InputSignalControl
 * @brief Class for each signal information
*/
class InputSignalControl
{
public:

    /**
     * @details Default constructor
     */
    InputSignalControl() = default; 
    /**
     * @details Constructor
     * @param nodeId Node ID
    */
    InputSignalControl(int nodeId);

    /**
     * @details Get node ID
     * @return Node ID
     */
    int GetNodeId() const { return m_nodeId; }

    /**
     * @details Set cycle time
     * @param cycle Cycle time in seconds
     */
    void SetCycle(int cycle) { m_cycle = cycle; }

    /**
     * @details Get cycle time
     * @return Cycle time in seconds
     */
    int GetCycle() const { return m_cycle; }

    /**
     * @details Set changed status
     * @param changed True if the signal control has changed, false otherwise
     */
    void SetChanged(bool changed) { m_changed = changed; }

    /**
     * @details Get changed status
     * @return True if the signal control has changed, false otherwise
     */
    bool IsChanged() const { return m_changed; }

    /**
     * @details Set sequence of phase
     * @param phaseList Sequence of phase
    */
    void SetPhaseList(std::vector<phase> phaseList) { m_phaseList = phaseList; }

    /**
     * @details Get sequence of phase
     * @return Sequence of phase
     */
    std::vector<phase> GetPhaseList() const { return m_phaseList; }

private:
    /**
     * @details Node ID
     */
    int m_nodeId;

    /**
     * @details cycle time
     */

    int m_cycle;

    /**
     * @details changed status
     */
    bool m_changed;

    /**
     * @details phase sequence
     */
    std::vector<phase> m_phaseList;
};
} // namespace NextSimIO

#endif