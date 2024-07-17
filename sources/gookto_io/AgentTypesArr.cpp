/**
 * NextSim Captain
 * @file : AgentTypesArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include <gookto_io/AgentTypesArr.hpp>
#include <gookto_io/InputAgentTypes.hpp>
#include <gookto_io/InputDistribution.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

AgentTypesArr::AgentTypesArr()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::AgentTypeXMLPath.string().c_str());
    // std::cout << "Loading AgentTypesArr" << std::endl;

    if (!doc.LoadFile(STSIO::AgentTypeXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (AgentTypesArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "vehtype")
        {
            InputDistribution veh_lenDist(std::string("Normal"), 4.5, 5.0, 5.5, 0.4);
            InputDistribution jamgapDist(std::string("LogNormal"), 1.0, 2.0, 3.5, 0.2);
            InputDistribution vfDist(std::string("Normal"), 50.0, 60.0, 70.0, 10.0);
            InputDistribution reaction_timeDist(std::string("LogNormal"), 1.0, 1.5, 3.5, 0.2);
            InputDistribution max_accDist(std::string("Normal"), 4.5, 4.8, 6.0, 1.1);
            InputDistribution max_decDist(std::string("Normal"), 4.5, 5.6, 7.0, 1.2);
            InputDistribution lc_param1Dist(std::string("Normal"), 0.08, 0.055, 0.04, 0.02);
            InputDistribution lc_param2Dist(std::string("Normal"), 0.04, 0.025, 0.01, 0.02);
            InputDistribution lc_senseDist(std::string("LogNormal"), 0.1, 0.0033, 0.001, 2.5);

            for (TiXmlElement *e = elem->FirstChildElement(); e != nullptr;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "veh_len")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    veh_lenDist.setdist(dist);
                    veh_lenDist.setmax(atof(max));
                    veh_lenDist.setmean(atof(mean));
                    veh_lenDist.setmin(atof(min));
                    veh_lenDist.setsd(atof(sd));
                }

                else if (elemName2 == "jamgap")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    jamgapDist.setdist(dist);
                    jamgapDist.setmax(atof(max));
                    jamgapDist.setmean(atof(mean));
                    jamgapDist.setmin(atof(min));
                    jamgapDist.setsd(atof(sd));
                }

                else if (elemName2 == "vf")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    vfDist.setdist(dist);
                    vfDist.setmax(atof(max));
                    vfDist.setmean(atof(mean));
                    vfDist.setmin(atof(min));
                    vfDist.setsd(atof(sd));
                }

                else if (elemName2 == "reaction_time")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    reaction_timeDist.setdist(dist);
                    reaction_timeDist.setmax(atof(max));
                    reaction_timeDist.setmean(atof(mean));
                    reaction_timeDist.setmin(atof(min));
                    reaction_timeDist.setsd(atof(sd));
                }

                else if (elemName2 == "max_acc")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    max_accDist.setdist(dist);
                    max_accDist.setmax(atof(max));
                    max_accDist.setmean(atof(mean));
                    max_accDist.setmin(atof(min));
                    max_accDist.setsd(atof(sd));
                }

                else if (elemName2 == "max_dec")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    max_decDist.setdist(dist);
                    max_decDist.setmax(atof(max));
                    max_decDist.setmean(atof(mean));
                    max_decDist.setmin(atof(min));
                    max_decDist.setsd(atof(sd));
                }

                else if (elemName2 == "lc_param1")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    lc_param1Dist.setdist(dist);
                    lc_param1Dist.setmax(atof(max));
                    lc_param1Dist.setmean(atof(mean));
                    lc_param1Dist.setmin(atof(min));
                    lc_param1Dist.setsd(atof(sd));
                }

                else if (elemName2 == "lc_param2")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    lc_param2Dist.setdist(dist);
                    lc_param2Dist.setmax(atof(max));
                    lc_param2Dist.setmean(atof(mean));
                    lc_param2Dist.setmin(atof(min));
                    lc_param2Dist.setsd(atof(sd));
                }

                else if (elemName2 == "lc_sensitivity")
                {
                    const char* dist = e->Attribute("dist");
                    const char* max = e->Attribute("max");
                    const char* mean = e->Attribute("mean");
                    const char* min = e->Attribute("min");
                    const char* sd = e->Attribute("sd");

                    if (!dist)   throw std::runtime_error ("Element should have 'dist' attribute");
                    if (!max)   throw std::runtime_error ("Element should have 'max' attribute");
                    if (!mean)   throw std::runtime_error ("Element should have 'mean' attribute");
                    if (!min)   throw std::runtime_error ("Element should have 'min' attribute");
                    if (!sd)   throw std::runtime_error ("Element should have 'sd' attribute");

                    lc_senseDist.setdist(dist);
                    lc_senseDist.setmax(atof(max));
                    lc_senseDist.setmean(atof(mean));
                    lc_senseDist.setmin(atof(min));
                    lc_senseDist.setsd(atof(sd));
                }
            }

            const char* id = elem->Attribute("id");
            const char* name = elem->Attribute("name");
            const char* v2x = elem->Attribute("v2x");
            const char* max_pax = elem->Attribute("max_pax");

            if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!name)   throw std::runtime_error ("Element should have 'name' attribute");
            if (!v2x)   v2x = "off";
            if (!max_pax)   max_pax = "1";

            // TODO: implement v2x on/off
            InputAgentTypes demoAgentTypes(
                name, std::atoi(max_pax), strcmp(v2x, "on") == 0 ? true : false,
                veh_lenDist, jamgapDist, vfDist, reaction_timeDist, max_accDist,
                max_decDist, lc_param1Dist, lc_param2Dist, lc_senseDist);

            vehTypes.insert({ std::atoi(id), demoAgentTypes });
        }
    }
    doc.Clear();
};