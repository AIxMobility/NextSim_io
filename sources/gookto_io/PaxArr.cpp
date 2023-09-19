#include <string>
#include <iostream>
#include <sstream>

#include <gookto_io/PaxArr.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

#include <gookto_io/FilePath.hpp>

PaxArr::PaxArr()
{
    TiXmlDocument doc(STSIO::PassengerXMLPath.string().c_str());
    bool loadOkay = doc.LoadFile();

    if (!loadOkay)
    {
        std::cout << "Loading failed (PaxArr)" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
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
                    ODPax demoPax(atol(e->Attribute("origin")),
                                  atol(e->Attribute("dest")),
                                  atof(e->Attribute("flow")),
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
                    AgentPax demoPax(atol(e->Attribute("origin_link")),
                                     atof(e->Attribute("origin_pos")),
                                     atol(e->Attribute("dest_link")),
                                     atof(e->Attribute("dest_pos")),
                                     atol(e->Attribute("num_pax")),
                                     atof(e->Attribute("time")),
                                     e->Attribute("type"));

                    AgentPaxVec.push_back(demoPax);
                }
            }
        }
    }
    doc.Clear();
};
