#include <iostream>
#include <string>
#include <filesystem>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/LinkArr.hpp>

// tool functions
void SetCellAttrs(InputLink *parent_link, InputCell *cell);
bool a_to_bool(const char *val);

// Note: All IDs of all objects should be more than 0, if id is 0 the object is
// not valid

// LinkArr Constructor
LinkArr::LinkArr()
{
    std::filesystem::path cwd = std::filesystem::current_path() ;
    std::cout << cwd << std::endl;

    TiXmlDocument doc("./network_xml/network.xml");
    bool loadOkay = doc.LoadFile();

    std::cout << loadOkay << std::endl;

    std::cout << "Loading LinkArr" << std::endl;

    if (!loadOkay)
    {
        std::cout << "loading failed" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
        exit(0);
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        //const char *attr;
        if (elemName == "links")
        {
            std::cout << "Got links" << std::endl;
            std::cout << (elem->FirstChildElement())->Value() << std::endl;
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "link")
                {
                    // std::cout << "Got A link" << std::endl;

                    InputLink demoLink((u_ll)atoll(e->Attribute("id")),
                                       atoi(e->Attribute("num_lane")),
                                       atof(e->Attribute("length")),
                                       atof(e->Attribute("width")));

                    // set the Link 2d, 1d values here.
                    // TODO: add set min max speed

                    demoLink.setFreeFlowSpeed(atof(e->Attribute("ffspeed")));
                    demoLink.setQmax(atof(e->Attribute("qmax")));
                    demoLink.setWaveSpeed(atof(e->Attribute("waveSpd")));
                    demoLink.setMaxVehicle(atoi(e->Attribute("maxVeh")));
                    demoLink.setFromNode(
                        (u_ll)atoll(e->Attribute("from_node")));
                    demoLink.setToNode(((u_ll)atoll(e->Attribute("to_node"))));
                    // save lane infos for each link
                    // int lane_num = 0;
                    for (TiXmlElement *ele = e->FirstChildElement();
                         ele != NULL; ele = ele->NextSiblingElement())
                    {
                        std::string elemName3 = ele->Value();
                        if (elemName3 == "lane")
                        {
                            // demoLink.pushLaneId(atol(ele->Attribute("id")));

                            const char *leftLaneID =
                                (ele->Attribute("left_lane_id"));
                            const char *rightLaneID =
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
                                (u_ll)atoll(ele->Attribute("id"))  ,
                                (u_ll)atoll(leftLaneID)  ,
                                (u_ll)atoll(rightLaneID) ,
                                atoi(ele->Attribute("num_cell")), r_empty,
                                l_empty);

                            for (TiXmlElement *e_lane =
                                     ele->FirstChildElement();
                                 e_lane != NULL;
                                 e_lane = e_lane->NextSiblingElement())
                            {
                                // parse the lane
                                std::string elemName = e_lane->Value();
                                if (elemName == "cell")
                                {
                                    InputCell demoCell(
                                        (u_ll)atoll(e_lane->Attribute("id")),
                                        atof(e_lane->Attribute("offset")),
                                        atof(e_lane->Attribute("length")));
                                    SetCellAttrs(&demoLink, &demoCell);
                                    demoLane.pushCell(demoCell);
                                }
                                else if (elemName == "segment")
                                {
                                    const char *block =
                                        e_lane->Attribute("block");
                                    bool blocked = a_to_bool(block);
                                    bool left_lc =
                                        a_to_bool(e_lane->Attribute("left_lc"));
                                    bool right_lc = a_to_bool(
                                        e_lane->Attribute("right_lc"));

                                    InputSegment demoSegment(
                                        (u_ll)atoll(e_lane->Attribute("id")),
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

bool a_to_bool(const char *val)
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

void SetCellAttrs(InputLink *parent_link, InputCell *cell)
{
    cell->setFreeFlowSpeed(parent_link->getFreeFlowSpeed());
    cell->setMaxSpeed(parent_link->getMaxSpeed());
    cell->setMinSpeed(parent_link->getMinSpeed());
    cell->setMaxVehicle(parent_link->getMaxVehicle());
    cell->setQmax(parent_link->getQmax());
    cell->setWaveSpeed(parent_link->getWaveSpeed());
    cell->setWidth(-1);
}