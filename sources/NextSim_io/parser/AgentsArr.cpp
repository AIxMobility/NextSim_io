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

    // A <veh> missing an attribute or its <link>/<node> line used to dereference null.
    // Missing sequences stay empty and NetInitializer skips that agent with a warning.
    auto parseVeh = [](TiXmlElement* e) {
        const char* idAttr = e->Attribute("id");
        const char* typeAttr = e->Attribute("type");
        const char* dptAttr = e->Attribute("dptTime");
        if (!idAttr || !typeAttr || !dptAttr)
            throw std::runtime_error(std::string("agents.xml: <veh") + (idAttr ? std::string(" id=") + idAttr : "")
                                     + "> needs id, type and dptTime attributes");
        InputAgents veh(std::stoi(idAttr), std::stoi(typeAttr), std::stod(dptAttr));
        auto attr = [&](const char* child, const char* name) {
            TiXmlElement* c = e->FirstChildElement(child);
            const char* value = c ? c->Attribute(name) : nullptr;
            return std::string(value ? value : "");
        };
        veh.SetLinkSeq(attr("link", "seq"));
        veh.SetNodeSeq(attr("node", "seq"));
        if (e->FirstChildElement("station"))
        {
            veh.SetStationSeq(attr("station", "seq"));
            veh.SetStationDistanceSeq(attr("station", "distance"));
        }
        return veh;
    };

    for (TiXmlElement *elem = root ? root->FirstChildElement() : NULL; elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();
        if (elemName == "agentSet")
        {
            const char *id = elem->Attribute("id");
            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");

            for (TiXmlElement *child = elem->FirstChildElement(); child != NULL;
                 child = child->NextSiblingElement())
            {
                std::string childName = child->Value();
                if (childName == "normalVeh")
                {
                    for (TiXmlElement *e = child->FirstChildElement(); e != NULL;
                        e = e->NextSiblingElement())
                    {
                        std::string elemName2 = e->Value();

                        if (elemName2 == "veh")
                        {
                            m_agents.push_back(parseVeh(e));
                        }
                    }
                }

                if (childName == "publicVeh")
                {
                    for (TiXmlElement *e = child->FirstChildElement(); e != NULL;
                        e = e->NextSiblingElement())
                    {
                        std::string elemName2 = e->Value();

                        if (elemName2 == "veh")
                        {
                            m_agents.push_back(parseVeh(e));
                        }
                    }
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