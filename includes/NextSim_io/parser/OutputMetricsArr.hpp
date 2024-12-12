/**
 * NextSim Captain
 * @file : OutputMetricsArr.hpp
 * @version : 1.0
 * @author : Chaemin Na
 */

#ifndef OUTPUTMETRICSARR_H
#define OUTPUTMETRICSARR_H

#include <vector>

namespace NextSimIO
{
class OutputMetricsArr
{

public:
    OutputMetricsArr();
    
    std::vector<std::pair<std::string, bool>> GetRecordMode() { return RecordMode; }

    void SetRecordMode(std::vector<std::pair<std::string, bool>> recordMode) 
        { RecordMode = recordMode; }

private:
    std::vector<std::pair<std::string, bool>> RecordMode;
};
} // namespace NextSimIO

#endif