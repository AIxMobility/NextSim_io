/**
 * NextSim Captain
 * @file : InputLaneLine.hpp
 * @brief One stretch of lane marking from network.xml:
 *        <line side="right" init_point="0" end_point="150" type="solid"/> inside a <lane>.
 *
 * Each boundary is written once, on the lane to its left: lane i's right line
 * is the boundary between lane i and its right_lane_id. Positions are metres
 * from the link start (like <segment>). Where no line is given the boundary is
 * dashed.
 */
#pragma once
#ifndef INPUTLANELINE_H
#define INPUTLANELINE_H

#include <string>

namespace NextSimIO
{
struct InputLaneLine
{
    double InitPoint = 0.0;
    double EndPoint = 0.0;
    //! dashed | solid | dashed_solid (lane i may cross to the right, not back) | solid_dashed (the reverse)
    std::string Type = "dashed";
};
}  // namespace NextSimIO

#endif
