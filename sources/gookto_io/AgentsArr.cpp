#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/AgentsArr.hpp>
#include <gookto_io/InputAgents.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>

AgentsArr::AgentsArr()
{
    parseAgent("Agents");
    parseAgent("Agents_opt");
};

void AgentsArr::parseAgent(std::string AgentType){
    TiXmlDocument doc;

    if(AgentType == "Agents"){
        doc.LoadFile("./network_xml/agents.xml");
        std::cout << "Loading AgentsArr" << std::endl;

        if (!doc.LoadFile("./network_xml/agents.xml"))
        {
            std::cerr << doc.ErrorDesc() << std::endl;
        }
    }
    else if(AgentType == "Agents_opt"){
        if (!std::filesystem::exists("./network_xml/agents_opt.xml"))   return;

        doc.LoadFile("./network_xml/agents_opt.xml");
        std::cout << "Loading Optional AgentsArr" << std::endl;

        if (!doc.LoadFile("./network_xml/agents_opt.xml"))
        {
            std::cerr << doc.ErrorDesc() << std::endl;
        }
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "NormalVeh")
        {
            std::cout << "Got Normal Veh" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh")
                {
                    const char *id = e->Attribute("id");
                    const char *type = e->Attribute("type");
                    const char *dpt_time = e->Attribute("dpt_time");

                    if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!type)   throw std::runtime_error ("Element should have 'type' attribute");
                    if (!dpt_time)   throw std::runtime_error ("Element should have 'dpt_time' attribute");

                    InputAgents single_veh(
                        atol(id),
                        atoi(type),
                        atof(dpt_time));

                    // parse the Link Seq of each vehicles:
                    // String Stream --> Extract Integer
                    const char *link_seq = e->Attribute("link_seq");
                    const char *node_seq = e->Attribute("node_seq");

                    if (!link_seq)   throw std::runtime_error ("Element should have 'link_seq' attribute");
                    if (!node_seq)   throw std::runtime_error ("Element should have 'node_seq' attribute");

                    std::stringstream links;
                    std::stringstream nodes;

                    links << link_seq;
                    nodes << node_seq;

                    std::string temp_links;
                    std::string temp_nodes;

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

                    if(AgentType == "Agents")    Agents.push_back(single_veh);
                    else if(AgentType == "Agents_opt") Agents_opt.push_back(single_veh);
                }
            }
        }

        if (elemName == "PublicVeh")
        {
            std::cout << "Got Public Veh" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh")
                {
                    const char *id = e->Attribute("id");
                    const char *type = e->Attribute("type");
                    const char *dpt_time = e->Attribute("dpt_time");

                    if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!type)   throw std::runtime_error ("Element should have 'type' attribute");
                    if (!dpt_time)   throw std::runtime_error ("Element should have 'dpt_time' attribute");

                    InputAgents single_veh(
                        atol(id),
                        atoi(type),
                        atof(dpt_time));

                    // parse the Link Seq of each vehicles:
                    // String Stream --> Extract Integer

                    const char *link_seq = e->Attribute("link_seq");
                    const char *node_seq = e->Attribute("node_seq");

                    if (!link_seq)   throw std::runtime_error ("Element should have 'link_seq' attribute");
                    if (!node_seq)   throw std::runtime_error ("Element should have 'node_seq' attribute");

                    std::stringstream links;
                    std::stringstream nodes;
                    std::stringstream stations;
                    std::stringstream station_dwell_times;
                    std::stringstream station_in;
                    std::stringstream station_out;

                    // station related attributes are optional

                    //Station Sequence
                    if (e->Attribute("station_seq"))
                    {
                        stations << e->Attribute("station_seq");

                        int found;

                        std::string temp_stations;
                        while (!stations.eof())
                        {
                            stations >> temp_stations;
                            if (std::stringstream(temp_stations) >> found)
                            {
                                single_veh.addStation(found);
                            }
                            temp_stations = "";
                        }
                    }

                    //Station Dwell Time
                    if (e->Attribute("station_dwell_time"))
                    {
                        station_dwell_times << e->Attribute("station_dwell_time");

                        double found_double;

                        std::string temp_station_dwell_times;
                        while (!station_dwell_times.eof())
                        {
                            station_dwell_times >> temp_station_dwell_times;
                            if (std::stringstream(temp_station_dwell_times) >> found_double)
                            {
                                single_veh.addStationDwellTime(found_double);
                            }
                            temp_station_dwell_times = "";
                        }
                    }

                    // Station In
                    if (e->Attribute("station_in"))
                    {
                        station_in << e->Attribute("station_in");

                        int found;

                        std::string temp_station_in;
                        while (!station_in.eof())
                        {
                            station_in >> temp_station_in;
                            if (std::stringstream(temp_station_in) >> found)
                            {
                                single_veh.addStationIn(found);
                            }
                            temp_station_in = "";
                        }
                    }

                    // Station Out
                    if (e->Attribute("station_out"))
                    {
                        station_out << e->Attribute("station_out");

                        int found;

                        std::string temp_station_out;
                        while (!station_out.eof())
                        {
                            station_out >> temp_station_out;
                            if (std::stringstream(temp_station_out) >> found)
                            {
                                single_veh.addStationOut(found);
                            }
                            temp_station_out = "";
                        }
                    }

                    links << link_seq;
                    nodes << node_seq;

                    std::string temp_links;
                    std::string temp_nodes;

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

                    if(AgentType == "Agents")    Agents.push_back(single_veh);
                    else if(AgentType == "Agents_opt") Agents_opt.push_back(single_veh);
                }
            }
        }
    }
    doc.Clear();
}

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
