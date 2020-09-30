#include <gookto_io/InputLink.hpp>
#include <gookto_io/Temporal.hpp>

InputCell::InputCell(u_ll id_val, float offset_val, float length_val,
                     void *parent_link)
    : MetadataBase(id_val, length_val)
{
    InputLink *_parent_link = static_cast<InputLink *>(parent_link);
    offset = offset_val;
    this->setFreeFlowSpeed(_parent_link->getFreeFlowSpeed());
    this->setMaxSpeed(_parent_link->getMaxSpeed());
    this->setMinSpeed(_parent_link->getMinSpeed());
    this->setMaxVehicle(_parent_link->getMaxVehicle());
    this->setQmax(_parent_link->getQmax());
    this->setWaveSpeed(_parent_link->getWaveSpeed());
    this->setWidth(-1);
}

// InputSegment methods

InputSegment::~InputSegment()
{
    blocked = left_lc = right_lc = false;
    init_point = end_point = id = 0;
}
void InputSegment::setBlocked(bool block)
{
    block = block;
}
void InputSegment::setLeftRight_lc(bool left_lc_val, bool right_lc_val)
{
    left_lc = left_lc_val;
    right_lc = right_lc_val;
}
void InputSegment::setInitialPoint(float init_point_val)
{
    init_point = init_point_val;
}
void InputSegment::setEndPoint(float end_point_val)
{
    end_point = end_point_val;
}

void InputSegment::setID(u_ll id_val)
{
    id = id_val;
}

// InputLane methods

InputLane::InputLane()
{
    id = num_cell = 0;
}

InputLane::InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val,
                     int num_cell_val)
{
    id = id_val;
    num_cell = num_cell_val;
    left_lane_id = new u_ll(left_lane_id_val);
    right_lane_id = new u_ll(right_lane_id_val);
    // CellArr = new std::vector<InputCell>();
    CellArr.resize(num_cell);
}

InputLane::InputLane(u_ll id_val, u_ll left_lane_id_val, u_ll right_lane_id_val,
                     int num_cell_val, bool RightEmpty, bool LeftEmpty)
{
    id = id_val;
    num_cell = num_cell_val;
    if (RightEmpty)
    {
        right_lane_id = nullptr;
    }
    else
    {
        right_lane_id = new u_ll(right_lane_id_val);
    }

    if (LeftEmpty)
    {
        left_lane_id = nullptr;
    }
    else
    {
        left_lane_id = new u_ll(left_lane_id_val);
    }
    // CellArr = new std::vector<InputCell>();
    // CellArr.resize(num_cell);
}

InputLane::~InputLane()
{
    id = num_cell = 0;
    if (left_lane_id)
    {
        delete left_lane_id;
    }
    if (right_lane_id)
    {
        delete right_lane_id;
    }
    /* for (auto itr : CellArr)
    {
            delete itr;
    }
    for (auto itr : SegmentArr)
    {
            delete itr;
    } */

    CellArr.clear();
    SegmentArr.clear();
}

void InputLane::setLeftLaneID(u_ll left_lane_id_val)
{
    *left_lane_id = left_lane_id_val;
}

void InputLane::setRightLaneID(u_ll right_lane_id_val)
{
    *right_lane_id = right_lane_id_val;
}
void InputLane::setNumCell(int num_cell_val)
{
    num_cell = num_cell_val;
}

void InputLane::pushCell(InputCell *cell)
{
    CellArr.push_back(cell);
}
void InputLane::pushSegment(InputSegment *segment)
{
    SegmentArr.push_back(segment);
}
