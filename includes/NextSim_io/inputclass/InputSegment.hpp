/**
 * NextSim Captain
 * @file : InputSegment.hpp
 * @version : 1.0
 * @author : ???
 */

#pragma once
#ifndef INPUTSEGMENT_H
#define INPUTSEGMENT_H

#include <utility>

namespace NextSimIO
{
/**
 * @class InputSegment
 * @brief Class for each segment information
 */
class InputSegment
{
public:

    /**
     * @details Constructor
     * @param id Segment ID
     * @param block Whether segment is blocked or not
     * @param init_point Start point of segment
     * @param end_point End point of segment
     */
    InputSegment(std::size_t id, bool block, double init_point, double end_point);

    /** @cond EXCLUDE */
    InputSegment() = default;
    InputSegment(const InputSegment& segment) = default;
    InputSegment& operator=(const InputSegment& segment) = default;
    ~InputSegment() = default;
    /** @endcond */

    /**
     * @details Set segment ID
     * @param id Segment ID
    */
    void SetID(std::size_t id) { m_id = id; }

    /**
     * @details Set whether segment is blocked or not
     * @param block True(blocked) or False(not)
    */
    void SetBlocked(bool block) { m_blocked = block; }

    /**
     * @details Set start point of segment
     * @param initPoint Start point of segment (from link start point)
    */
    void SetInitialPoint(double initPoint) { m_initPoint = initPoint; }

    /**
     * @details Set end point of segment
     * @param endPoint End point of segment (from link start point)
    */
    void SetEndPoint(double endPoint) { m_endPoint = endPoint; }

    /**
     * @details Get segment ID
     * @return Segment ID
    */
    std::size_t GetID() const { return m_id; }

    /**
     * @details Get whether segment is blocked or not
     * @return True(blocked) or False(not)
    */
    bool GetBlocked() const { return m_blocked; }

    /**
     * @details Get start point of segment
     * @return Start point of segment (from link start point)
    */
    double GetInitialPoint() const { return m_initPoint; }

    /**
     * @details Get end point of segment
     * @return End point of segment (from link start point)
    */
    double GetEndPoint() const { return m_endPoint; }

private:

    /**
     * @details Segment ID
     */
    std::size_t m_id;

    /**
     * @details Whether segment is blocked or not
     */
    bool m_blocked;

    /**
     * @details Start point of segment (from link start point)
     */
    double m_initPoint;

    /**
     * @details End point of segment (from link start point)
     */
    double m_endPoint;
};
} // namespace NextSimIO

#endif
