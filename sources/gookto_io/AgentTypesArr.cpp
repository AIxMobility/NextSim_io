#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include <gookto_io/AgentTypesArr.hpp>
#include <gookto_io/InputAgentTypes.hpp>
#include <gookto_io/InputDistribution.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>

AgentTypesArr::AgentTypesArr()
{
    TiXmlDocument doc;

    doc.LoadFile("./network_xml/agenttypes.xml");
    std::cout << "Loading AgentTypesArr" << std::endl;

    if (!doc.LoadFile("./network_xml/agenttypes.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement()->FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "vehtype")
        {
            std::cout << "Got vehtype" << std::endl;

            InputDistribution veh_lenDist(std::string("Normal"), -1.0, 0.0, 1.0,
                                          1.0);
            InputDistribution jamgapDist(std::string("Normal"), -1.0, 0.0, 1.0,
                                         1.0);
            InputDistribution vfDist(std::string("Normal"), -1.0, 0.0, 1.0,
                                     1.0);
            InputDistribution reaction_timeDist(std::string("Normal"), -1.0,
                                                0.0, 1.0, 1.0);
            InputDistribution max_accDist(std::string("Normal"), -1.0, 0.0, 1.0,
                                          1.0);
            InputDistribution max_decDist(std::string("Normal"), -1.0, 0.0, 1.0,
                                          1.0);

            for (TiXmlElement *e = elem->FirstChildElement(); e != nullptr;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh_len")
                {
                    veh_lenDist.setdist(e->Attribute("dist"));
                    veh_lenDist.setmax(atof(e->Attribute("max")));
                    veh_lenDist.setmean(atof(e->Attribute("mean")));
                    veh_lenDist.setmin(atof(e->Attribute("min")));
                    veh_lenDist.setsd(atof(e->Attribute("sd")));
                }
                else if (elemName2 == "jamgap")
                {
                    jamgapDist.setdist(e->Attribute("dist"));
                    jamgapDist.setmax(atof(e->Attribute("max")));
                    jamgapDist.setmean(atof(e->Attribute("mean")));
                    jamgapDist.setmin(atof(e->Attribute("min")));
                    jamgapDist.setsd(atof(e->Attribute("sd")));
                }
                else if (elemName2 == "vf")
                {
                    vfDist.setdist(e->Attribute("dist"));
                    vfDist.setmax(atof(e->Attribute("max")));
                    vfDist.setmean(atof(e->Attribute("mean")));
                    vfDist.setmin(atof(e->Attribute("min")));
                    vfDist.setsd(atof(e->Attribute("sd")));
                }
                else if (elemName2 == "reaction_time")
                {
                    reaction_timeDist.setdist(e->Attribute("dist"));
                    reaction_timeDist.setmax(atof(e->Attribute("max")));
                    reaction_timeDist.setmean(atof(e->Attribute("mean")));
                    reaction_timeDist.setmin(atof(e->Attribute("min")));
                    reaction_timeDist.setsd(atof(e->Attribute("sd")));
                }
                else if (elemName2 == "max_acc")
                {
                    max_accDist.setdist(e->Attribute("dist"));
                    max_accDist.setmax(atof(e->Attribute("max")));
                    max_accDist.setmean(atof(e->Attribute("mean")));
                    max_accDist.setmin(atof(e->Attribute("min")));
                    max_accDist.setsd(atof(e->Attribute("sd")));
                }
                else if (elemName2 == "max_dec")
                {
                    max_decDist.setdist(e->Attribute("dist"));
                    max_decDist.setmax(atof(e->Attribute("max")));
                    max_decDist.setmean(atof(e->Attribute("mean")));
                    max_decDist.setmin(atof(e->Attribute("min")));
                    max_decDist.setsd(atof(e->Attribute("sd")));
                }
            }

            InputAgentTypes demoAgentTypes(
                elem->Attribute("name"),
                // std::atoi(elem->Attribute("max_pax")),
                0,  // TODO: something is making error here
                veh_lenDist, jamgapDist, vfDist, reaction_timeDist, max_accDist,
                max_decDist);

            vehTypes.insert({ std::atoi(elem->Attribute("id")), demoAgentTypes });
        }
    }
    doc.Clear();
};