#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/LinkArr.hpp>
#include <NextSim_io/includes/NextSim_io/FilePath.hpp>

// tool functions
void SetCellAttrs(const InputLink& parentLink, InputCell& cell);
bool a_to_bool(const char* val);

// Note: All IDs of all objects should be more than 0, if ID is 0 the object is
// not valid

// LinkArr Constructor
LinkArr::LinkArr()
{
    TiXmlDocument doc("");
    bool loadOkay = doc.LoadFile(STSIO::NetworkXMLPath.string().c_str());
    // std::cout << "Loading LinkArr" << std::endl;

    if (!loadOkay)
    {
        std::cout << "Loading failed (LinkArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "links")
        {
            for (TiXmlElement* e = elem->FirstChildElement(); e != nullptr;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "link")
                {
                    const char *linkId = e->Attribute("id");
                    const char *num_lane = e->Attribute("num_lane");
                    const char *linkLength = e->Attribute("length");
                    const char *width = e->Attribute("width");
                    const char *stop_line = e->Attribute("stop_line");

                    if (!linkId)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!num_lane)   throw std::runtime_error ("Element should have 'num_lane' attribute");
                    if (!linkLength)   throw std::runtime_error ("Element should have 'length' attribute");
                    if (!width)   throw std::runtime_error ("Element should have 'width' attribute");
                    if (!stop_line)   throw std::runtime_error ("Element should have 'stop_line' attribute");

                    InputLink demoLink(
                        static_cast<std::size_t>(
                            atoll(linkId)),
                            atoi(num_lane),
                            atof(linkLength),
                            atof(width),
                            atof(stop_line));

                    // set the Link 2d, 1d values here.
                    // TODO: add set min max speed

                    const char *ffspeed = e->Attribute("ff_spd");  // km/h
                    const char *qmax = e->Attribute("qmax");  // veh/hr
                    const char *waveSpd = e->Attribute("wave_spd");  // km/h
                    const char *maxVeh = e->Attribute("max_veh");  // veh/link
                    const char *from_node = e->Attribute("from_node");
                    const char *to_node = e->Attribute("to_node");
                    const char *maxSpd = e->Attribute("max_spd");  // km/h
                    const char *minSpd = e->Attribute("min_spd");  // km/h

                    if (!ffspeed)   throw std::runtime_error ("Element should have 'ffspeed' attribute");
                    if (!qmax)   throw std::runtime_error ("Element should have 'qmax' attribute");
                    if (!waveSpd)   throw std::runtime_error ("Element should have 'waveSpd' attribute");
                    if (!maxVeh)   throw std::runtime_error ("Element should have 'maxVeh' attribute");
                    if (!from_node)   throw std::runtime_error ("Element should have 'from_node' attribute");
                    if (!to_node)   throw std::runtime_error ("Element should have 'to_node' attribute");
                    if (!maxSpd)   throw std::runtime_error ("Element should have 'max_spd' attribute");
                    if (!minSpd)   throw std::runtime_error ("Element should have 'min_spd' attribute");

                    demoLink.FreeFlowSpeed = std::atof(ffspeed);
                    demoLink.Qmax = std::atof(qmax);
                    demoLink.WaveSpeed = std::atof(waveSpd);
                    demoLink.MaxVehicle = std::atoi(maxVeh);
                    demoLink.SetFromNode(
                        ((std::size_t)atoll(from_node)));
                    demoLink.SetToNode(
                        ((std::size_t)atoll(to_node)));
                    demoLink.MaxSpeed = std::atof(maxSpd);
                    demoLink.MinSpeed = std::atof(minSpd);

                    // save lane infos for each link
                    // int lane_num = 0;
                    for (TiXmlElement* ele = e->FirstChildElement();
                         ele != nullptr; ele = ele->NextSiblingElement())
                    {
                        std::string elemName3 = ele->Value();
                        if (elemName3 == "lane")
                        {
                            const char *left_lane_id = ele->Attribute("left_lane_id");
                            const char *right_lane_id = ele->Attribute("right_lane_id");
                            const char *laneId = ele->Attribute("id");
                            const char *num_cell = ele->Attribute("num_cell");
                            
                            if (!left_lane_id)   throw std::runtime_error ("Element should have 'left_lane_id' attribute");
                            if (!right_lane_id)   throw std::runtime_error ("Element should have 'right_lane_id' attribute");
                            if (!laneId)   throw std::runtime_error ("Element should have 'id' attribute");
                            if (!num_cell)   throw std::runtime_error ("Element should have 'num_cell' attribute");

                            InputLane demoLane(
                                (std::size_t)atoll(laneId),
                                (std::size_t)atoll(left_lane_id),
                                (std::size_t)atoll(right_lane_id),
                                atoi(num_cell));

                            for (TiXmlElement* e_lane =
                                     ele->FirstChildElement();
                                 e_lane != nullptr;
                                 e_lane = e_lane->NextSiblingElement())
                            {
                                std::string elementName = e_lane->Value();
                                if (elementName == "cell")
                                {
                                    const char *cellId = e_lane->Attribute("id");
                                    const char *offset = e_lane->Attribute("offset");
                                    const char *cellLength = e_lane->Attribute("length");
                                    
                                    if (!cellId)   throw std::runtime_error ("Element should have 'id' attribute");
                                    if (!offset)   throw std::runtime_error ("Element should have 'offset' attribute");
                                    if (!cellLength)   throw std::runtime_error ("Element should have 'length' attribute");

                                    InputCell demoCell(
                                        (std::size_t)atoll(cellId),
                                        atof(offset),
                                        atof(cellLength));
                                    SetCellAttrs(demoLink, demoCell);
                                    demoLane.pushCell(demoCell);
                                }

                                else if (elementName == "segment")
                                {
                                    const char *segmentId = e_lane->Attribute("id");
                                    const char *init_point = e_lane->Attribute("init_point");
                                    const char *end_point = e_lane->Attribute("end_point");
                                    const char *block = e_lane->Attribute("block");
                                    const char *left_lc = e_lane->Attribute("left_lc");
                                    const char *right_lc = e_lane->Attribute("right_lc");
                                    
                                    if (!segmentId)   throw std::runtime_error ("Element should have 'id' attribute");
                                    if (!init_point)   throw std::runtime_error ("Element should have 'init_point' attribute");
                                    if (!end_point)   throw std::runtime_error ("Element should have 'end_point' attribute");
                                    if (!block)   throw std::runtime_error ("Element should have 'block' attribute");
                                    if (!left_lc)   throw std::runtime_error ("Element should have 'left_lc' attribute");
                                    if (!right_lc)   throw std::runtime_error ("Element should have 'right_lc' attribute");

                                    bool blocked = a_to_bool(block);
                                    bool left_lc_bool = a_to_bool(left_lc);
                                    bool right_lc_bool = a_to_bool(right_lc);

                                    InputSegment demoSegment(
                                        (std::size_t)atoll(segmentId),
                                        blocked,
                                        left_lc_bool,
                                        right_lc_bool,
                                        atof(init_point),
                                        atof(end_point));
                                    demoLane.pushSegment(demoSegment);
                                }
                            }

                            demoLink.pushLaneId(demoLane);
                        }
                    }

                    Links.push_back(demoLink);
                    // perhaps need to free pointers here
                }
            }
        }
    }
    doc.Clear();
};

bool a_to_bool(const char* val)
{
    bool temp = false;
    if (strcmp(val, "True") == 0)
    {
        temp = true;
    }
    else if (strcmp(val, "False") == 0)
    {
        temp = false;
    }
    // else
    // {
    //     assert(false);
    // }
    return temp;
}

void SetCellAttrs(const InputLink& parentLink, InputCell& cell)
{
    cell.FreeFlowSpeed = parentLink.FreeFlowSpeed;
    cell.MaxSpeed = parentLink.MaxSpeed;
    cell.MinSpeed = parentLink.MinSpeed;
    cell.MaxVehicle = parentLink.MaxVehicle;
    cell.Qmax = parentLink.Qmax;
    cell.WaveSpeed = parentLink.WaveSpeed;
    cell.Width = -1;
}
