/**
 * NextSim Captain
 * @file : InputSegment.hpp
 * @version : 1.0
 * @author : ???
 */

#ifndef INPUTSEGMENT_H
#define INPUTSEGMENT_H

#include "InputSegment.hpp"
#include <utility>

/**
 * @class InputSegment
 * @brief Class for each segment information
 */
class InputSegment
{
private:
    // <segment block="true" end_point="169.15" ID="20000102240301" init_point="0.0" left_lc="false" right_lc="false"/>

    /**
     * @details Whether segment is blocked or not
     */
    bool blocked;

    /**
     * @details Segment ID
     */
    std::size_t id;

    /**
     * @details Start point of segment (from link start point)
     */
    double init_point;

    /**
     * @details End point of segment (from link start point)
     */
    double end_point;

    /**
     * @details Whether left lane change is allowed or not
     */
    bool left_lc;

    /**
     * @details Whether right lane change is allowed or not
     */
    bool right_lc; // change the names for better UI

public:

    /**
     * @details Constructor
     * @param id_val Segment ID
     * @param block Whether segment is blocked or not
     * @param left_lc_val Whether left lane change is allowed or not
     * @param right_lc_val Whether right lane change is allowed or not
     * @param init_point_val Start point of segment
     * @param end_point_val End point of segment
     */
    InputSegment(std::size_t id_val, bool block, bool left_lc_val, bool right_lc_val,
                 double init_point_val, double end_point_val)
    {
        id = id_val;
        blocked = block;
        left_lc = left_lc_val;
        right_lc = right_lc_val;
        init_point = init_point_val;
        end_point = end_point_val;
    }

    // ???
    InputSegment() = default;
    InputSegment(const InputSegment& segment) = default;
    InputSegment& operator=(const InputSegment& segment) = default;
    ~InputSegment() = default;

    /**
     * @details Set segment ID
     * @param id_val Segment ID
    */
    void setID(std::size_t id_val);

    /**
     * @details Set whether segment is blocked or not
     * @param block True(blocked) or False(not)
    */
    void setBlocked(bool block);

    /**
     * @details Set whether left and right lane change is allowed or not
     * @param left_lc_val True(left lane change is allowed) or False(not)
     * @param right_lc_val True(right lane change is allowed) or False(not)
    */
    void setLeftRight_lc(bool left_lc_val, bool right_lc_val);

    /**
     * @details Set start point of segment
     * @param init_point_val Start point of segment (from link start point)
    */
    void setInitialPoint(double init_point_val);

    /**
     * @details Set end point of segment
     * @param end_point_val End point of segment (from link start point)
    */
    void setEndPoint(double end_point_val);

    /**
     * @details Get segment ID
     * @return Segment ID
    */
    std::size_t getID() const { return id; }

    /**
     * @details Get whether segment is blocked or not
     * @return True(blocked) or False(not)
    */
    bool getBlocked() const { return blocked; }

    /**
     * @details Get whether left and right lane change is allowed or not
     * @return Pair of left and right value (True(lane change is allowed) or False(not))
    */
    std::pair<bool, bool>  getLeftRight_lc() const
    {
        return std::make_pair(left_lc, right_lc);
    }

    /**
     * @details Get whether left lane change is allowed or not
     * @return True(left lane change is allowed) or False(not)
    */
    bool getLeft_lc() const { return left_lc; }

    /**
     * @details Get whether right lane change is allowed or not
     * @return True(right lane change is allowed) or False(not)
    */
    bool getRight_lc() const { return right_lc; }

    /**
     * @details Get start point of segment
     * @return Start point of segment (from link start point)
    */
    double getInitialPoint() const { return init_point; }

    /**
     * @details Get end point of segment
     * @return End point of segment (from link start point)
    */
    double getEndPoint() const { return end_point; }
};


#endif
