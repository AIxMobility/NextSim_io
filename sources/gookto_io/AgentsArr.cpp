#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/AgentsArr.hpp>
#include <gookto_io/InputAgents.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

AgentsArr::AgentsArr()
{
    parseAgent("Agents");
    parseAgent("Agents_opt");
};

void AgentsArr::parseAgent(std::string AgentType){
    TiXmlDocument doc;

    if(AgentType == "Agents"){
        doc.LoadFile(STSIO::AgentXMLPath.string().c_str());
        // std::cout << "Loading AgentsArr" << std::endl;

        if (!doc.LoadFile(STSIO::AgentXMLPath.string().c_str()))
        {
            std::cout << "Loading failed (AgentsArr)" << std::endl;
            std::cerr << doc.ErrorDesc() << std::endl;
        }
    }
    else if(AgentType == "Agents_opt"){
        if (!std::filesystem::exists(STSIO::AgentOptXMLPath.string().c_str()))   return;

        doc.LoadFile(STSIO::AgentOptXMLPath.string().c_str());
        // std::cout << "Loading Optional AgentsArr" << std::endl;

        if (!doc.LoadFile(STSIO::AgentOptXMLPath.string().c_str()))
        {
            std::cout << "Loading failed (AgentsOptArr)" << std::endl;
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
                        single_veh.setLinkSeq(linkSeq);
                    }
                    
                    ee = ee->NextSiblingElement();
                    eName = ee->Value();
                    if (eName == "node")
                    {
                        std::string nodeSeq = ee->Attribute("seq");
                        single_veh.setNodeSeq(nodeSeq);
                    }
                    
                    if(AgentType == "Agents")    Agents.push_back(single_veh);
                    else if(AgentType == "Agents_opt") Agents_opt.push_back(single_veh);
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
                        single_veh.setLinkSeq(linkSeq);
                    }
                    
                    ee = ee->NextSiblingElement();
                    eName = ee->Value();
                    if (eName == "node")
                    {
                        std::string nodeSeq = ee->Attribute("seq");
                        single_veh.setNodeSeq(nodeSeq);
                    }
                    
                    ee = ee->NextSiblingElement();
                    eName = ee->Value();
                    if (eName == "station")
                    {
                        std::string stationSeq = ee->Attribute("seq");
                        single_veh.setStationSeq(stationSeq);
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
