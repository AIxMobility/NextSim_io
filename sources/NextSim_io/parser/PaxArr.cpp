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
            // 승객 매트릭스 id: <od_pax id="N">. id 가 없는 블록(예전 파일)은 매트릭스 0 이다.
            // 시나리오는 시간 구간마다 이 id 로 매트릭스를 고른다 (passengerDemandSchedule).
            const char* idAttr = elem->Attribute("id");
            const int matrixId = idAttr ? atoi(idAttr) : 0;
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "demand")
                {
                    const char* origin = e->Attribute("origin");
                    const char* dest = e->Attribute("dest");
                    const char* flow = e->Attribute("flow");
                    const char* dist = e->Attribute("dist");
                    if (!origin || !dest || !flow)
                    {
                        std::cout << "Warning: passenger.xml demand without origin, dest or flow; skipped" << std::endl;
                        continue;
                    }
                    InputODPax demoPax(atol(origin),
                                  atol(dest),
                                  atol(flow),
                                  dist ? dist : "Uniform",
                                  matrixId);

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
                     InputAgentPax demoPax(atol(e->Attribute("id")),
                                        atol(e->Attribute("originLink")),
                                        atol(e->Attribute("originOffset")),
                                        atol(e->Attribute("destLink")),
                                        atol(e->Attribute("destOffset")),
                                        atof(e->Attribute("time")));
 
                     for (TiXmlElement* tripElem = e->FirstChildElement("trip"); tripElem != NULL;
                     tripElem = tripElem->NextSiblingElement("trip"))
                     {
                         const char* lineID = tripElem->Attribute("lineID");
                         const char* tripTime = tripElem->Attribute("time");
                         demoPax.AddTrip(atol(tripElem->Attribute("origin")),
                                     atol(tripElem->Attribute("dest")),
                                     tripElem->Attribute("mode"),
                                     lineID == nullptr ? "" : lineID,
                                     tripTime == nullptr ? 0.0 : atof(tripTime));
                     }
 
                     m_agentPax.push_back(demoPax);
                 }
             }
         }
     }
     doc.Clear();
 };
 } // namespace NextSimIO
