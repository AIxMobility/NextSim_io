#include <string>
#include <iostream>
#include <sstream>

#include <NextSim_io/PaxArr.hpp>

#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/tinyapi/tinystr.h>

#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
PaxArr::PaxArr()
{
    TiXmlDocument doc(NextSimIO::PassengerXMLPath.string().c_str());
    
    bool loadOkay = doc.LoadFile();
    if (!loadOkay)
    {
        std::cout << "Loading failed (PaxArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();

    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "od_pax")
        {
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "demand")
                {
                    InputODPax demoPax(atol(e->Attribute("origin")),
                                  atol(e->Attribute("dest")),
                                  atol(e->Attribute("flow")),
                                  e->Attribute("dist"));

                    ODPaxVec.push_back(demoPax);
                }
            }
        }

        else if (elemName == "agent_pax")
        {
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "agent")
                {
                    InputAgentPax demoPax(atol(e->Attribute("id")),
                                     atol(e->Attribute("origin_station")),
                                     atol(e->Attribute("dest_station")),
                                     atof(e->Attribute("dpt_time")),
                                     e->Attribute("type"));

                    AgentPaxVec.push_back(demoPax);
                }
            }
        }
    }
    doc.Clear();
};
} // namespace NextSimIO