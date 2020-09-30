#include <gookto_io/InputSegment.hpp>

// InputSegment methods 

void InputSegment::setBlocked(bool block){
        block = block;
}
void InputSegment::setLeftRight_lc(bool left_lc_val, bool right_lc_val){
        left_lc = left_lc_val;
        right_lc = right_lc_val;
}
void InputSegment::setInitialPoint(float init_point_val){
        init_point = init_point_val;
}
void InputSegment::setEndPoint(float end_point_val){
        end_point = end_point_val;
}

void InputSegment::setID(u_ll id_val){
        id = id_val;
}
