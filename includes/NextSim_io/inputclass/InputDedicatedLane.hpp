/**
 * NextSim Captain
 * @file : InputDedicatedLane.hpp
 * @brief One lane of dedicatedLane.xml: who the lane is for, and when and
 * where other vehicles may still use it.
 */
#pragma once
#ifndef INPUTDEDICATEDLANE_H
#define INPUTDEDICATEDLANE_H

#include <string>
#include <utility>
#include <vector>

namespace NextSimIO
{
/**
 * @details Road at each end of a dedicated lane where other vehicles may use
 * it when entry_end / entry_start are not given [m]
 */
constexpr double DefaultDedicatedEntryLength = 30.0;

struct InputDedicatedLane
{
    //! BusOnly, TramOnly, HOVOnly or BikeOnly
    std::string Type = "All";
    //! Other vehicles never use the lane (tram tracks, separated busways)
    bool Strict = false;
    //! Other vehicles may move into the lane this far before the link end [m]
    double EntryEnd = DefaultDedicatedEntryLength;
    //! Vehicles that turned into the lane leave it within this far from the link start [m]
    double EntryStart = DefaultDedicatedEntryLength;
    //! Operating windows as [start, end) seconds since midnight; empty means always
    std::vector<std::pair<int, int>> Hours;
};
}  // namespace NextSimIO

#endif
