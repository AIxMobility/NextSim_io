// #include <gookto_io/InputLane.hpp>
// #include <gookto_io/InputSegment.hpp>
// #include <gookto_io/InputCell.hpp>

// #include <iostream>


// // InputLane methods

// InputLane::InputLane(){
//         id = num_cell = 0;

        
// }

// InputLane::InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, int num_cell_val){

//         id = id_val;
//         num_cell = num_cell_val;
//         left_lane_id = new u_ll(left_lane_id_val);
//         right_lane_id = new u_ll(right_lane_id_val);
//         // CellArr = new std::vector<InputCell>();
//         CellArr.resize(num_cell);


// }

// InputLane::InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, 
//                         int num_cell_val, bool RightEmpty, bool LeftEmpty)
// {

//         id = id_val;
//         num_cell = num_cell_val;
//         if (RightEmpty){
//                 right_lane_id = nullptr;}
//         else{
//                 right_lane_id = new u_ll(right_lane_id_val);
//         }

//         if (LeftEmpty){

//                 left_lane_id = nullptr; 
//         }
//         else{          
                
//                 left_lane_id = new u_ll(left_lane_id_val);

//         }
//         // CellArr = new std::vector<InputCell>();
//         CellArr.resize(num_cell);


// }

// InputLane::~InputLane(){

//         id= num_cell = 0;
//         if (left_lane_id){delete left_lane_id;}
//         if (right_lane_id){delete right_lane_id;}
//         CellArr.clear();
//         SegmentArr.clear();
// }


// void InputLane::setLeftLaneID(u_ll left_lane_id_val){
//         *left_lane_id = left_lane_id_val;
// }

// void InputLane::setRightLaneID(u_ll right_lane_id_val){
//         *right_lane_id = right_lane_id_val;
// }
// void InputLane::setNumCell(int num_cell_val){
//         num_cell =num_cell_val;
// }

// void InputLane::pushCell(InputCell *cell){

//         CellArr.push_back(cell);

// }
// void InputLane::pushSegment(InputSegment *segment){

//         SegmentArr.push_back(segment);

// }
