// #ifndef INPUTSEGMENT_H
// #define INPUTSEGMENT_H

// #include "InputSegment.hpp"
// #include <utility>

// typedef unsigned long long u_ll;

// class InputSegment
// {
//     private:
//                 // <segment block="true" end_point="169.15" id="20000102240301" init_point="0.0" left_lc="false" right_lc="false"/>
//         bool blocked;
//         u_ll id;
//         float init_point, end_point;
//         bool left_lc, right_lc; // change the names for better UI

//     public:
//         InputSegment(u_ll id_val, bool block, bool left_lc_val, bool right_lc_val, float init_point_val, float end_point_val):
//             id{id_val},
//             blocked {block},
//             left_lc{left_lc_val},
//             right_lc{right_lc_val},
//             init_point{init_point_val},
//             end_point{end_point_val}
//         {
//         }
//         InputSegment(){}
//         ~InputSegment();
        
//         void setID(u_ll id_val);
//         void setBlocked(bool block);
//         void setLeftRight_lc(bool left_lc_val, bool right_lc_val);
//         void setInitialPoint(float init_point_val);
//         void setEndPoint(float end_point_val);
        
//         u_ll getID(){return id;}
//         bool getBlocked(){return blocked;}
//         std::pair<bool, bool> getLeftRight_lc(){return std::make_pair(left_lc, right_lc);}
//         bool getLeft_lc(){return left_lc;}
//         bool getRight_lc(){return right_lc;}
//         float getInitialPoint(){return init_point;}
//         float getEndPoint(){return end_point;}
// };


// #endif