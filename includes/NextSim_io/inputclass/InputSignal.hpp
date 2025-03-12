/**
 * NextSim Captain
 * @file : InputSignal.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef INPUTSIGNAL_H
#define INPUTSIGNAL_H

#include "signal/phase.hpp"
#include "signal/plan.hpp"
#include "signal/turn.hpp"

namespace NextSimIO
{
/**
 * @class InputSignal
 * @brief Class for each signal information
*/
class InputSignal
{
public:
    /**
     * @details Constructor
     * @param nodeId Node ID
    */
    InputSignal(int nodeId);

    /**
     * @details Push turn information
     * @param turn Turn information
    */
    void PushTurn(turn turn) { m_turnList.push_back(turn); }

    /**
     * @details Push signal plan
     * @param plan Signal plan
    */
    void PushPlan(plan plan) { m_planList.push_back(plan); }

    /**
     * @details Get node ID
     * @return Node ID
    */
    int GetNodeId() const { return m_nodeId; }

    /**
     * @details Get vector of turn informations
     * @return Vector of turn informations
    */
    std::vector<turn> GetTurnList() const { return m_turnList; }

    /**
     * @details Get vector of signal plans
     * @return Vector of signal plans
    */
    std::vector<plan> GetPlanList() const { return m_planList; }

private:
    /**
     * @details Node ID
    */
    int m_nodeId;

    /**
     * @details Vector of turn informations
    */
    std::vector<turn> m_turnList;

    /**
     * @details Vector of signal plans
    */
    std::vector<plan> m_planList;
};
} // namespace NextSimIO

#endif