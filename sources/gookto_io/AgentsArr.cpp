#include <iostream>
#include <sstream>
#include <string>

#include <gookto_io/AgentsArr.hpp>
#include <gookto_io/InputAgents.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>

AgentsArr::AgentsArr()
{
    TiXmlDocument doc;

    doc.LoadFile("./network_xml/agents.xml");
    std::cout << "Loading AgentsArr" << std::endl;

    if (!doc.LoadFile("./network_xml/agents.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        // const char *attr;
        if (elemName == "small_av")
        {
            std::cout << "Got Small AV" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh")
                {
                    // std::cout << "Got Veh" << std::endl;

                    int type = atoi(e->Attribute("type"));

                    float dpt_time = atof(e->Attribute("dpt_time"));

                    // Intialize single Vehicle
                    InputAgents single_veh(atol(e->Attribute("id")), type,
                                           dpt_time);

                    // parse the Link Seq of each vehicles:
                    // String Stream --> Extract Integer
                    std::stringstream links;
                    std::stringstream nodes;
                    std::stringstream origins;
                    std::stringstream destinations;
                    std::stringstream pax;

                    links << e->Attribute("link_seq");
                    nodes << e->Attribute("node_seq");
                    pax << e->Attribute("pax_list");
                    origins << e->Attribute("pax_origin");
                    destinations << e->Attribute("pax_dest");

                    std::string temp_links;
                    std::string temp_nodes;
                    std::string temp_pax;
                    std::string temp_origins;
                    std::string temp_dests;

                    int found;

                    // add Links
                    while (!links.eof())
                    {
                        links >> temp_links;
                        if (std::stringstream(temp_links) >> found)
                        {
                            single_veh.addLink(found);
                        }
                        temp_links = "";
                    }

                    // add Nodes
                    while (!nodes.eof())
                    {
                        nodes >> temp_nodes;
                        if (std::stringstream(temp_nodes) >> found)
                        {
                            single_veh.addNode(found);
                        }
                        temp_nodes = "";
                    }

                    // add Pax
                    while (!pax.eof())
                    {
                        pax >> temp_pax;
                        if (std::stringstream(temp_pax) >> found)
                        {
                            single_veh.addPaxList(found);
                        }
                        temp_pax = "";
                    }

                    // add Pax Origin
                    while (!origins.eof())
                    {
                        origins >> temp_origins;
                        if (std::stringstream(temp_origins) >> found)
                        {
                            single_veh.addPaxOrigin(found);
                        }
                        temp_origins = "";
                    }

                    // add Pax Dest
                    while (!destinations.eof())
                    {
                        destinations >> temp_dests;
                        if (std::stringstream(temp_dests) >> found)
                        {
                            single_veh.addPaxDest(found);
                        }
                        temp_dests = "";
                    }

                    Agents.push_back(single_veh);
                }
            }
        }

        if (elemName == "bus_av")
        {
            std::cout << "Got BUS AV" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh")
                {
                    // std::cout << "Got Veh" << std::endl;
                    // dpt_time, type, id, link_seq, node_seq

                    int type = atoi(e->Attribute("type"));

                    float dpt_time = atof(e->Attribute("dpt_time"));

                    // Intialize single Vehicle
                    InputAgents single_veh(atol(e->Attribute("id")), type,
                                           dpt_time);

                    // parse the Link Seq of each vehicles:
                    // String Stream --> Extract Integer
                    std::stringstream links;
                    std::stringstream nodes;
                    std::stringstream stations;

                    links << e->Attribute("link_seq");
                    nodes << e->Attribute("node_seq");
                    stations << e->Attribute("station_seq");

                    std::string temp_links;
                    std::string temp_nodes;
                    std::string temp_stations;

                    int found;

                    // add Links
                    while (!links.eof())
                    {
                        links >> temp_links;
                        if (std::stringstream(temp_links) >> found)
                        {
                            single_veh.addLink(found);
                        }
                        temp_links = "";
                    }

                    // add Nodes
                    while (!nodes.eof())
                    {
                        nodes >> temp_nodes;
                        if (std::stringstream(temp_nodes) >> found)
                        {
                            single_veh.addNode(found);
                        }
                        temp_nodes = "";
                    }

                    // add Stations
                    while (!stations.eof())
                    {
                        stations >> temp_stations;
                        if (std::stringstream(temp_stations) >> found)
                        {
                            single_veh.addStation(found);
                        }
                        temp_stations = "";
                    }

                    Agents.push_back(single_veh);
                }
            }
        }
    }
    doc.Clear();
};

void AgentsArr::showArr()
{
    for (size_t i = 0; i < Agents.size(); i++)
    {
        for (size_t j = 0; j < Agents[i].getLinkSeq().size(); j++)
        {
            std::cout << Agents[i].getLinkSeq()[j] << " ";
        }
        std::cout << std::endl;
    }
};