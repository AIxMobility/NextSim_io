/**
 * NextSim Captain
 * @file : plan.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#pragma once
#ifndef PLAN_H
#define PLAN_H

#include <vector>
#include <string>
#include <NextSim_io/inputclass/signal/phase.hpp>

namespace NextSimIO
{
/**
 * @class plan
 * @brief Class for intersection plan information
 */
class plan
{
public:
    /**
     * @details Constructor
     * @param id Plan ID
     * @param cycle Cycle of the plan
     * @param offset Offset of the plan
     * @param phaseSeq Sequence of phase
     */
    plan(int id, int cycle, int offset, std::vector<phase> phaseSeq);

    /**
     * @details Get plan ID
     * @return Plan ID
     */
    int GetId() const { return m_id; }

    /**
     * @details Get cycle of the plan
     * @return Cycle of the plan
     */
    int GetCycle() const { return m_cycle; }

    /**
     * @details Get offset of the plan
     * @return Offset of the plan
     */
    int GetOffset() const { return m_offset; }

    /**
     * @details Get sequence of phase
     * @return Sequence of phase
     */
    std::vector<phase> GetPhaseSeq() const { return m_phaseList; }

private:
    /**
     * @details Plan ID
    */
    int m_id;
    
    /**
     * @details Cycle of the plan
     */
    int m_cycle;

    /**
     * @details Offset of the plan
     */
    int m_offset;

    /**
     * @details List of phase
     */
    std::vector<phase> m_phaseList;
};
} // namespace NextSimIO

#endif