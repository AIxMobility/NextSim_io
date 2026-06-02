/**
 * NextSim Captain
 * @file : LinkArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <utility>

#include <NextSim_io/parser/LinkArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
// tool functions
void SetCellAttrs(const InputLink& parentLink, InputCell& cell);
bool a_to_bool(const char* val);
std::vector<std::pair<double, double>> ParseShapePoints(const char* val);

// Note: All IDs of all objects should be more than 0, if ID is 0 the object is
// not valid

// LinkArr Constructor
LinkArr::LinkArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::NetworkXMLPath.string().c_str());

    if (!loadSuccess)
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
                    const char *linkShape = e->Attribute("shape");

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

                    demoLink.SetShapePoints(ParseShapePoints(linkShape));

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
                    const char *type = e->Attribute("type");

                    if (!ffspeed)   throw std::runtime_error ("Element should have 'ffspeed' attribute");
                    if (!qmax)   throw std::runtime_error ("Element should have 'qmax' attribute");
                    if (!waveSpd)   throw std::runtime_error ("Element should have 'waveSpd' attribute");
                    if (!maxVeh)   throw std::runtime_error ("Element should have 'maxVeh' attribute");
                    if (!from_node)   throw std::runtime_error ("Element should have 'from_node' attribute");
                    if (!to_node)   throw std::runtime_error ("Element should have 'to_node' attribute");
                    if (!maxSpd)   throw std::runtime_error ("Element should have 'max_spd' attribute");
                    if (!minSpd)   throw std::runtime_error ("Element should have 'min_spd' attribute");
                    if (!type)   throw std::runtime_error ("Element should have 'type' attribute");

                    demoLink.freeFlowSpeed = std::atof(ffspeed);
                    demoLink.qMax = std::atof(qmax);
                    demoLink.waveSpeed = std::atof(waveSpd);
                    demoLink.maxVehicle = std::atoi(maxVeh);
                    demoLink.SetFromNode(
                        ((std::size_t)atoll(from_node)));
                    demoLink.SetToNode(
                        ((std::size_t)atoll(to_node)));
                    demoLink.maxSpeed = std::atof(maxSpd);
                    demoLink.minSpeed = std::atof(minSpd);
                    demoLink.SetType(type);

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
                            const char *laneAccessType = ele->Attribute("laneAccessType");
                            const char *laneShape = ele->Attribute("shape");
                            
                            if (!left_lane_id)   throw std::runtime_error ("Element should have 'left_lane_id' attribute");
                            if (!right_lane_id)   throw std::runtime_error ("Element should have 'right_lane_id' attribute");
                            if (!laneId)   throw std::runtime_error ("Element should have 'id' attribute");
                            if (!num_cell)   throw std::runtime_error ("Element should have 'num_cell' attribute");
                            if (!laneAccessType)   laneAccessType = "All";  // default value
                            
                            auto shapePoints = ParseShapePoints(laneShape);

                            InputLane demoLane(
                                (std::size_t)atoll(laneId),
                                (std::size_t)atoll(left_lane_id),
                                (std::size_t)atoll(right_lane_id),
                                laneAccessType,
                                atoi(num_cell),
                                shapePoints);

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
                                    demoLane.PushCell(demoCell);
                                }

                                else if (elementName == "segment")
                                {
                                    const char *segmentId = e_lane->Attribute("id");
                                    const char *init_point = e_lane->Attribute("init_point");
                                    const char *end_point = e_lane->Attribute("end_point");
                                    const char *block = e_lane->Attribute("block");
                                    
                                    if (!segmentId)   throw std::runtime_error ("Element should have 'id' attribute");
                                    if (!init_point)   throw std::runtime_error ("Element should have 'init_point' attribute");
                                    if (!end_point)   throw std::runtime_error ("Element should have 'end_point' attribute");
                                    if (!block)   throw std::runtime_error ("Element should have 'block' attribute");

                                    bool blocked = a_to_bool(block);

                                    InputSegment demoSegment(
                                        (std::size_t)atoll(segmentId),
                                        blocked,
                                        atof(init_point),
                                        atof(end_point));
                                    demoLane.PushSegment(demoSegment);
                                }
                            }

                            demoLane.MergeShortResidualCell();
                            demoLink.PushLaneId(demoLane);
                        }
                    }

                    if (demoLink.GetType() == "return")
                        m_returnLinks.push_back(demoLink);

                    m_links.push_back(demoLink);
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

std::vector<std::pair<double, double>> ParseShapePoints(const char* val)
{
    std::vector<std::pair<double, double>> shapePoints;
    if (val == nullptr)
        return shapePoints;

    std::stringstream ss(val);
    std::string token;
    while (ss >> token)
    {
        const auto commaPos = token.find(',');
        if (commaPos == std::string::npos)
            continue;

        const std::string xStr = token.substr(0, commaPos);
        const std::string yStr = token.substr(commaPos + 1);
        if (xStr.empty() || yStr.empty())
            continue;

        shapePoints.emplace_back(std::stod(xStr), std::stod(yStr));
    }

    return shapePoints;
}

void SetCellAttrs(const InputLink& parentLink, InputCell& cell)
{
    cell.freeFlowSpeed = parentLink.freeFlowSpeed;
    cell.maxSpeed = parentLink.maxSpeed;
    cell.minSpeed = parentLink.minSpeed;
    cell.maxVehicle = parentLink.maxVehicle;
    cell.qMax = parentLink.qMax;
    cell.waveSpeed = parentLink.waveSpeed;
    cell.width = -1;
}
}  // namespace NextSimIO
