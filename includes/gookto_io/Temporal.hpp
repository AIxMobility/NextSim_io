#ifndef TEMPORAL_H
#define TEMPORAL_H
#include <vector>
typedef unsigned long long u_ll;


class MetadataBase{
    private:
        u_ll id;
        float _freeFlowSpeed, _max_spd,  _min_spd, _waveSpeed;
        float _length, _width, _Qmax;
        size_t _maxVehicle;
        
    public:
        MetadataBase(){}
        MetadataBase(u_ll id_val){
            id = id_val;
        }
        MetadataBase(u_ll id_val, float length_val){
            id = id_val;
            _length = length_val;
        }
        MetadataBase(u_ll id_val, float length_val, float width_val){
            id = id_val;
            _length = length_val;
            _width = width_val;
        }
        MetadataBase(u_ll id_val, float length_val, float freeFlowSpeed_val, float max_spd_val, float  min_spd_val, float waveSpeed_val, size_t maxVehicle_val, float Qmax_val){
            id = id_val;
            _length = length_val;
            _freeFlowSpeed = freeFlowSpeed_val;
            _max_spd = max_spd_val;
            _min_spd = min_spd_val;
            _waveSpeed = waveSpeed_val;
            _maxVehicle = maxVehicle_val;
            _Qmax = Qmax_val;
            _width = -1;
        }
        // common for every other class
        void setID(u_ll id_val){id = id_val;}
        u_ll getID(){return id;}
        void setLength(float length_val){_length = length_val;}
        float getLength(){return _length;}
        void setWidth(float width_val){ _width = width_val;}
        float getWidth(){return _width;}


        // for link and cell 
        virtual void setFreeFlowSpeed(float val){ _freeFlowSpeed = val;}
        virtual void setQmax(float val){_Qmax = val;}
        virtual void setWaveSpeed(float val){ _waveSpeed = val;}
        virtual void setMaxVehicle(size_t val){_maxVehicle = val;}
        virtual void setMaxSpeed(float val){_max_spd = val;}
        virtual void setMinSpeed(float val){_min_spd = val;}

        
        virtual float getFreeFlowSpeed(){return _freeFlowSpeed;}
        virtual float getQmax(){return _Qmax;}
        virtual float getWaveSpeed(){return _waveSpeed;}
        virtual size_t getMaxVehicle(){return _maxVehicle;}
        virtual float getMaxSpeed(){return _max_spd;}
        virtual float getMinSpeed(){return _min_spd;}
};


class InputCell: public MetadataBase
{
    private:
        //Data Members for the cell
        float offset;
    public:
        // Constructor and destructor for the cell
        InputCell(u_ll id_val, float offset_val, float length_val) : MetadataBase(id_val, length_val)
        {
            offset = offset_val;
        }

        
        // InputCell(u_ll id_val, float offset_val, float length_val, InputLink* parent_link): 
        //     MetadataBase(id_val, length_val, parent_link->getFreeFlowSpeed(),
        //                 parent_link->getMaxSpeed(),parent_link->getMinSpeed(), 
        //                 parent_link->getWaveSpeed(),parent_link->getMaxVehicle(), parent_link->getQmax())
        // {
        //     offset = offset_val;


        // }
        InputCell(u_ll id_val, float offset_val, float length_val, void* parent_link);
        
        // : 
        //     MetadataBase(id_val, length_val, parent_link->getFreeFlowSpeed(),
        //                 parent_link->getMaxSpeed(),parent_link->getMinSpeed(), 
        //                 parent_link->getWaveSpeed(),parent_link->getMaxVehicle(), parent_link->getQmax())
        // {
        //     offset = offset_val;


        // }
        InputCell() : MetadataBase(){}
        ~InputCell(){};


        void setOffset(float offset_val){offset = offset_val;}
        float getOffset(){return offset;}
};

class InputSegment
{
    private:
                // <segment block="true" end_point="169.15" id="20000102240301" init_point="0.0" left_lc="false" right_lc="false"/>
        bool blocked;
        u_ll id;
        float init_point, end_point;
        bool left_lc, right_lc; // change the names for better UI

    public:
        InputSegment(u_ll id_val, bool block, bool left_lc_val, bool right_lc_val, float init_point_val, float end_point_val):
            id{id_val},
            blocked {block},
            left_lc{left_lc_val},
            right_lc{right_lc_val},
            init_point{init_point_val},
            end_point{end_point_val}
        {
        }
        InputSegment(){}
        ~InputSegment();
        
        void setID(u_ll id_val);
        void setBlocked(bool block);
        void setLeftRight_lc(bool left_lc_val, bool right_lc_val);
        void setInitialPoint(float init_point_val);
        void setEndPoint(float end_point_val);
        
        u_ll getID(){return id;}
        bool getBlocked(){return blocked;}
        std::pair<bool, bool> getLeftRight_lc(){return std::make_pair(left_lc, right_lc);}
        bool getLeft_lc(){return left_lc;}
        bool getRight_lc(){return right_lc;}
        float getInitialPoint(){return init_point;}
        float getEndPoint(){return end_point;}
};

class InputLane
{
    private:
        u_ll id;
        // pointers to make them nullptrs if needed
        u_ll *left_lane_id, *right_lane_id;
        int num_cell;
        // Arrays of cells and segments;
        std::vector<InputCell *> CellArr;
        std::vector<InputSegment *> SegmentArr;

    public:
        //constructors
        InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, int num_cell_val);
        InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val, int num_cell_val, bool RightEmpty, bool LeftEmpty);
        
        InputLane();
        ~InputLane();

        void setID(u_ll val);
        void setLeftLaneID(u_ll left_lane_id_val);
        void setRightLaneID(u_ll right_lane_id_val);
        void setNumCell(int num_cell_val);
        void pushCell(InputCell *cell);
        void pushSegment(InputSegment *segment);

        u_ll getID(){return id;}
        u_ll getLeftLaneID(){return *left_lane_id;}
        u_ll getRightLaneID(){return *right_lane_id;}
        int getNumCell(){return num_cell;}

        std::vector<InputCell*>getCells(){return CellArr;}
        std::vector<InputSegment*> getSegments(){return SegmentArr;}


};





#endif