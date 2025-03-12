/**
 * NextSim Captain
 * @file : RecordModeArr.hpp
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
 * @class RecordModeArr
 * @brief Class for output metrics array
 */
class RecordModeArr
{
public:
    /**
     * @details Constructor
     * @param recordMode Record mode information
     */
    RecordModeArr();
    
    /**
     * @details Get record mode information
     * @return Record mode information
     */
    std::vector<InputRecordMode> GetRecordModes() { return m_recordModes; }

private:
    /**
     * @details Record mode information
     */
    std::vector<InputRecordMode> m_recordModes;
};
} // namespace NextSimIO

#endif