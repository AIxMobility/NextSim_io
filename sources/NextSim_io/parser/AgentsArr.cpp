/**
 * NextSim Captain
 * @file : AgentsArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <NextSim_io/parser/AgentsArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{

AgentsArr::AgentsArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::AgentXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (AgentsArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }
    
    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "NormalVeh")
        {
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh")
                {
                    int id = std::stoi(e->Attribute("id"));
                    int type = std::stoi(e->Attribute("type"));
                    double dpt_time = std::stod(e->Attribute("dpt_time"));

                    InputAgents single_veh(
                        id, type, dpt_time);

                    TiXmlElement *ee = e->FirstChildElement();

                    std::string eName = ee->Value();
                    if (eName == "link")
                    {
                        std::string linkSeq = ee->Attribute("seq");
                        single_veh.SetLinkSeq(linkSeq);
                    }
                    
                    ee = ee->NextSiblingElement();
                    eName = ee->Value();
                    if (eName == "node")
                    {
                        std::string nodeSeq = ee->Attribute("seq");
                        single_veh.SetNodeSeq(nodeSeq);
                    }
                    
                    m_agents.push_back(single_veh);
                }
            }
        }

        if (elemName == "PublicVeh")
        {
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh")
                {
                    int id = std::stoi(e->Attribute("id"));
                    int type = std::stoi(e->Attribute("type"));
                    double dpt_time = std::stod(e->Attribute("dpt_time"));

                    InputAgents single_veh(
                        id, type, dpt_time);
                    
                    TiXmlElement *ee = e->FirstChildElement();

                    std::string eName = ee->Value();
                    if (eName == "link")
                    {
                        std::string linkSeq = ee->Attribute("seq");
                        single_veh.SetLinkSeq(linkSeq);
                    }
                    
                    ee = ee->NextSiblingElement();
                    eName = ee->Value();
                    if (eName == "node")
                    {
                        std::string nodeSeq = ee->Attribute("seq");
                        single_veh.SetNodeSeq(nodeSeq);
                    }
                    
                    ee = ee->NextSiblingElement();
                    eName = ee->Value();
                    if (eName == "station")
                    {
                        std::string stationSeq = ee->Attribute("seq");
                        single_veh.SetStationSeq(stationSeq);

                        std::string stationDistanceSeq = ee->Attribute("distance");
                        single_veh.SetStationDistanceSeq(stationDistanceSeq);
                    }

                    m_agents.push_back(single_veh);
                }
            }
        }
    }
    doc.Clear();
}

void AgentsArr::ShowArr()
{
    for (size_t i = 0; i < m_agents.size(); i++)
    {
        for (size_t j = 0; j < m_agents[i].GetLinkSeq().size(); j++)
        {
            std::cout << m_agents[i].GetLinkSeq()[j] << " ";
        }
        std::cout << std::endl;
    }
};

}  // namespace NextSimIO