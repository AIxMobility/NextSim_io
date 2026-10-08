//! NextSim IO
//! \file : RunErrors.hpp
//! \brief Count of errors that make a run's output unusable (a required input
//! file that did not load, a database write that failed). The simulation
//! entry fails the run when the count is not zero, so callers see a non-zero
//! exit code instead of a "successful" run with missing data.

#ifndef NEXTSIM_IO_RUN_ERRORS_HPP
#define NEXTSIM_IO_RUN_ERRORS_HPP

#include <atomic>
#include <cstdio>
#include <string>

namespace NextSimIO
{
inline std::atomic<int>& RunErrorCount()
{
    static std::atomic<int> count{ 0 };
    return count;
}

/**
 * @details Counts one run error and prints it (only the first few, so a
 * failing insert in a loop does not flood the log). Safe on any thread: it
 * writes with fprintf, not std::cerr.
 */
inline void ReportRunError(const std::string& message)
{
    constexpr int MaxPrinted = 20;
    const int previous = RunErrorCount().fetch_add(1, std::memory_order_relaxed);
    if (previous < MaxPrinted)
        std::fprintf(stderr, "Error: %s\n", message.c_str());
    else if (previous == MaxPrinted)
        std::fprintf(stderr, "Error: further run errors are not printed\n");
}
}  // namespace NextSimIO

#endif
