#ifndef INPUTLANE_H
#define INPUTLANE_H

#include <vector>
#include "InputCell.hpp"
#include "InputSegment.hpp"

class InputLane
{
    private:
        u_ll id;
        // pointers to make them nullptrs if needed
        u_ll left_lane_id = 0, right_lane_id = 0; // Lane ID should be more than 0
        int num_cell;
        // Arrays of cells and segments;
        std::vector<InputCell> CellArr;
        std::vector<InputSegment> SegmentArr;

    public:
        //constructors
        InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, int num_cell_val);
        InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, int num_cell_val, bool RightEmpty, bool LeftEmpty);
        
        InputLane() = default;
        ~InputLane() = default;
        InputLane(const InputLane& lane) = default;
        InputLane& operator=( const InputLane& lane) = default;

        
        void setID(u_ll val);
        void setLeftLaneID(u_ll left_lane_id_val);
        void setRightLaneID(u_ll right_lane_id_val);
        void setNumCell(int num_cell_val);
        void pushCell(InputCell cell);
        void pushSegment(InputSegment segment);

        u_ll getID(){return id;}
        u_ll getLeftLaneID(){return left_lane_id;}
        u_ll getRightLaneID(){return right_lane_id;}
        int getNumCell(){return num_cell;}

        std::vector<InputCell> getCells(){return CellArr;}
        std::vector<InputSegment> getSegments(){return SegmentArr;}


};


#endif