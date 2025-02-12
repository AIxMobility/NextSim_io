/**
 * NextSim Captain
 * @file : OutputMetricsArr.hpp
 * @version : 1.0
 * @author : Chaemin Na
 */

#ifndef OUTPUTMETRICSARR_H
#define OUTPUTMETRICSARR_H

#include <vector>
#include <NextSim_io/inputclass/InputRecordMode.hpp>

namespace NextSimIO
{
/**
 * @class OutputMetricsArr
 * @brief Class for output metrics array
 */
class OutputMetricsArr
{
public:
    /**
     * @details Constructor
     * @param recordMode Record mode information
     */
    OutputMetricsArr();
    
    /**
     * @details Get record mode information
     * @return Record mode information
     */
    std::vector<InputRecordMode> GetRecordMode() { return m_recordModes; }

private:
    /**
     * @details Record mode information
     */
    std::vector<InputRecordMode> m_recordModes;
};
} // namespace NextSimIO

#endif