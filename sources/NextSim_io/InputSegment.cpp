#include <NextSim_io/InputSegment.hpp>

// InputSegment methods 

void InputSegment::setBlocked(bool block){
        block = block;
}
void InputSegment::setLeftRight_lc(bool left_lc_val, bool right_lc_val){
        left_lc = left_lc_val;
        right_lc = right_lc_val;
}
void InputSegment::setInitialPoint(double init_point_val){
        init_point = init_point_val;
}
void InputSegment::setEndPoint(double end_point_val){
        end_point = end_point_val;
}

void InputSegment::setID(std::size_t id_val){
        id = id_val;
}
