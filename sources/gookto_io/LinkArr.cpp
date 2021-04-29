#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/LinkArr.hpp>
#include <gookto_io/includes/gookto_io/FilePath.hpp>

// tool functions
void SetCellAttrs(const InputLink& parentLink, InputCell& cell);
bool a_to_bool(const char* val);

// Note: All IDs of all objects should be more than 0, if ID is 0 the object is
// not valid

// LinkArr Constructor
LinkArr::LinkArr()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << cwd << std::endl;

    for (const auto& entry : std::filesystem::directory_iterator(cwd))
        std::cout << entry.path() << std::endl;

    std::filesystem::path netDir("network_xml");
    for (const auto& entry : std::filesystem::directory_iterator(cwd / netDir))
        std::cout << entry.path() << std::endl;

    TiXmlDocument doc("");
    bool loadOkay = doc.LoadFile(STSIO::NetworkXMLPath.string().c_str());

    std::cout << loadOkay << std::endl;

    std::cout << "Loading LinkArr" << std::endl;

    if (!loadOkay)
    {
        std::cout << "loading failed" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
        exit(0);
    }

    TiXmlElement* root = doc.FirstChildElement();

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        // const char *attr;
        if (elemName == "links")
        {
            std::cout << "Got links" << std::endl;
            for (TiXmlElement* e = elem->FirstChildElement(); e != nullptr;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "link")
                {
                    // std::cout << "Got A link" << std::endl;

                    InputLink demoLink(
                        static_cast<std::size_t>(atoll(e->Attribute("id"))),
                        atoi(e->Attribute("num_lane")),
                        atof(e->Attribute("length")),
                        atof(e->Attribute("width")));

                    // set the Link 2d, 1d values here.
                    // TODO: add set min max speed

                    demoLink.FreeFlowSpeed = std::atof(e->Attribute("ffspeed"));
                    demoLink.Qmax = std::atof(e->Attribute("qmax"));
                    demoLink.WaveSpeed = std::atof(e->Attribute("waveSpd"));
                    demoLink.MaxVehicle = std::atoi(e->Attribute("maxVeh"));
                    demoLink.SetFromNode(
                        static_cast<std::size_t>(std::atoll(
                            e->Attribute("from_node"))));
                    demoLink.SetToNode(
                        ((std::size_t)atoll(e->Attribute("to_node"))));
                    // save lane infos for each link
                    // int lane_num = 0;
                    for (TiXmlElement* ele = e->FirstChildElement();
                         ele != nullptr; ele = ele->NextSiblingElement())
                    {
                        std::string elemName3 = ele->Value();
                        if (elemName3 == "lane")
                        {
                            // demoLink.pushLaneId(atol(ele->Attribute("id")));

                            const char* leftLaneID =
                                (ele->Attribute("left_lane_id"));
                            const char* rightLaneID =
                                (ele->Attribute("right_lane_id"));
                            bool r_empty = false, l_empty = false;
                            if (strcmp(leftLaneID, "") == 0)
                            {
                                l_empty = true;
                            }
                            if (strcmp(rightLaneID, "") == 0)
                            {
                                r_empty = true;
                            }

                            InputLane demoLane(
                                (std::size_t)atoll(ele->Attribute("id")),
                                (std::size_t)atoll(leftLaneID),
                                (std::size_t)atoll(rightLaneID),
                                atoi(ele->Attribute("num_cell")), r_empty,
                                l_empty);

                            for (TiXmlElement* e_lane =
                                     ele->FirstChildElement();
                                 e_lane != nullptr;
                                 e_lane = e_lane->NextSiblingElement())
                            {
                                // parse the lane
                                std::string elementName = e_lane->Value();
                                if (elementName == "cell")
                                {
                                    InputCell demoCell(
                                        (std::size_t)atoll(
                                            e_lane->Attribute("id")),
                                        atof(e_lane->Attribute("offset")),
                                        atof(e_lane->Attribute("length")));
                                    SetCellAttrs(demoLink, demoCell);
                                    demoLane.pushCell(demoCell);
                                }
                                else if (elementName == "segment")
                                {
                                    const char* block =
                                        e_lane->Attribute("block");
                                    bool blocked = a_to_bool(block);
                                    bool left_lc =
                                        a_to_bool(e_lane->Attribute("left_lc"));
                                    bool right_lc = a_to_bool(
                                        e_lane->Attribute("right_lc"));

                                    InputSegment demoSegment(
                                        (std::size_t)atoll(
                                            e_lane->Attribute("id")),
                                        blocked, left_lc, right_lc,
                                        atof(e_lane->Attribute("init_point")),
                                        atof(e_lane->Attribute("end_point")));
                                    demoLane.pushSegment(demoSegment);
                                }
                                else
                                {
                                    assert(false);
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
    if (strcmp(val, "true") == 0)
    {
        temp = true;
    }
    else if (strcmp(val, "false") == 0)
    {
        temp = false;
    }
    else
    {
        assert(false);
    }
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
