/**
 * NextSim Captain
 * @file : PaxArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <string>
#include <iostream>
#include <sstream>

#include <NextSim_io/parser/PaxArr.hpp>

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

                    m_odPax.push_back(demoPax);
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
                     InputAgentPax demoPax(atol(e->Attribute("originLink")),
                                      atol(e->Attribute("originOffset")),
                                      atol(e->Attribute("destLink")),
                                      atol(e->Attribute("destOffset")),
                                      atof(e->Attribute("time")),
                                      e->Attribute("type"));
 
                     for (TiXmlElement* tripElem = e->FirstChildElement("trip"); tripElem != NULL;
                     tripElem = tripElem->NextSiblingElement("trip"))
                     {
                         demoPax.AddTrip(atol(tripElem->Attribute("origin")),
                                     atol(tripElem->Attribute("dest")),
                                     tripElem->Attribute("mode"));
                     }
 
                     m_agentPax.push_back(demoPax);
                 }
             }
         }
     }
     doc.Clear();
 };
 } // namespace NextSimIO