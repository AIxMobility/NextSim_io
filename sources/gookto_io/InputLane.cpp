#include <gookto_io/InputLane.hpp>
#include <iostream>


// InputLane methods


InputLane::InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, int num_cell_val){

        id = id_val;
        num_cell = num_cell_val;
        left_lane_id = (left_lane_id_val);
        right_lane_id = (right_lane_id_val);
        // CellArr.resize(num_cell);

}

InputLane::InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, 
                        int num_cell_val, bool RightEmpty, bool LeftEmpty)
{

        id = id_val;
        num_cell = num_cell_val;
        if (RightEmpty){
                right_lane_id = 0;}
        else{
                right_lane_id = (right_lane_id_val);
        }

        if (LeftEmpty){

                left_lane_id = 0; 
        }
        else{          
                
                left_lane_id = (left_lane_id_val);

        }
        // CellArr = new std::vector<InputCell>();
        // CellArr.resize(num_cell);


}



void InputLane::setLeftLaneID(u_ll left_lane_id_val){
        left_lane_id = left_lane_id_val;
}

void InputLane::setRightLaneID(u_ll right_lane_id_val){
        right_lane_id = right_lane_id_val;
}
void InputLane::setNumCell(int num_cell_val){
        num_cell =num_cell_val;
}

void InputLane::pushCell(InputCell cell){

        CellArr.push_back(cell);

}
void InputLane::pushSegment(InputSegment segment){

        SegmentArr.push_back(segment);

}
