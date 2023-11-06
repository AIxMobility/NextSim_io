#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/AgentsArr.hpp>
#include <gookto_io/InputAgents.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

AgentsArr::AgentsArr(const std::string& userName)
{
    parseAgent("Agents", userName);
    parseAgent("Agents_opt", userName);
};

void AgentsArr::parseAgent(std::string AgentType, const std::string& userName){
    TiXmlDocument doc;

    if(AgentType == "Agents"){
        doc.LoadFile(STSIO::AgentXML(userName).c_str());
        // std::cout << "Loading AgentsArr" << std::endl;

        if (!doc.LoadFile(STSIO::AgentXML(userName).c_str()))
        {
            std::cout << "Loading failed (AgentsArr)" << std::endl;
            std::cerr << doc.ErrorDesc() << std::endl;
        }
    }
    else if(AgentType == "Agents_opt"){
        if (!std::filesystem::exists(STSIO::AgentOptXML(userName).c_str()))   return;

        doc.LoadFile(STSIO::AgentOptXML(userName).c_str());
        // std::cout << "Loading Optional AgentsArr" << std::endl;

        if (!doc.LoadFile(STSIO::AgentOptXML(userName).c_str()))
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
                    const char *id = e->Attribute("id");
                    const char *typeId = e->Attribute("type_id");
                    const char *dpt_time = e->Attribute("dpt_time");

                    if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!typeId)   throw std::runtime_error ("Element should have 'type_id' attribute");
                    if (!dpt_time)   throw std::runtime_error ("Element should have 'dpt_time' attribute");

                    InputAgents single_veh(
                        atol(id),
                        atoi(typeId),
                        atof(dpt_time));

                    std::string link_seq = e->Attribute("link_seq");
                    std::string node_seq = e->Attribute("node_seq");

                    single_veh.setLinkSeq(link_seq);
                    single_veh.setNodeSeq(node_seq);
                    
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
                    const char *id = e->Attribute("id");
                    const char *typeId = e->Attribute("type_id");
                    const char *dpt_time = e->Attribute("dpt_time");

                    if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!typeId)   throw std::runtime_error ("Element should have 'type_id' attribute");
                    if (!dpt_time)   throw std::runtime_error ("Element should have 'dpt_time' attribute");

                    InputAgents single_veh(
                        atol(id),
                        atoi(typeId),
                        atof(dpt_time));
                        
                    std::string link_seq = e->Attribute("link_seq");
                    std::string node_seq = e->Attribute("node_seq");
                    std::string station_seq = e->Attribute("station_seq");

                    single_veh.setLinkSeq(link_seq);
                    single_veh.setNodeSeq(node_seq);
                    single_veh.setStationSeq(station_seq);

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
