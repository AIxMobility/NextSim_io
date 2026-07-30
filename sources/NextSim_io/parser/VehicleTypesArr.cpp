/**
 * NextSim Captain
 * @file : VehicleTypesArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include <NextSim_io/parser/VehicleTypesArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
VehicleTypesArr::VehicleTypesArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::VehicleTypeXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (VehicleTypesArr)" << std::endl;
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
            InputDistribution veh_widthDist(std::string("Normal"), 1.9, 1.8, 2.1, 0.2);
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

                    veh_lenDist.SetDist(dist);
                    veh_lenDist.SetMax(atof(max));
                    veh_lenDist.SetMean(atof(mean));
                    veh_lenDist.SetMin(atof(min));
                    veh_lenDist.SetSD(atof(sd));
                }

                else if (elemName2 == "veh_width")
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

                    veh_widthDist.SetDist(dist);
                    veh_widthDist.SetMax(atof(max));
                    veh_widthDist.SetMean(atof(mean));
                    veh_widthDist.SetMin(atof(min));
                    veh_widthDist.SetSD(atof(sd));
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

                    jamgapDist.SetDist(dist);
                    jamgapDist.SetMax(atof(max));
                    jamgapDist.SetMean(atof(mean));
                    jamgapDist.SetMin(atof(min));
                    jamgapDist.SetSD(atof(sd));
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

                    vfDist.SetDist(dist);
                    vfDist.SetMax(atof(max));
                    vfDist.SetMean(atof(mean));
                    vfDist.SetMin(atof(min));
                    vfDist.SetSD(atof(sd));
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

                    reaction_timeDist.SetDist(dist);
                    reaction_timeDist.SetMax(atof(max));
                    reaction_timeDist.SetMean(atof(mean));
                    reaction_timeDist.SetMin(atof(min));
                    reaction_timeDist.SetSD(atof(sd));
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

                    max_accDist.SetDist(dist);
                    max_accDist.SetMax(atof(max));
                    max_accDist.SetMean(atof(mean));
                    max_accDist.SetMin(atof(min));
                    max_accDist.SetSD(atof(sd));
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

                    max_decDist.SetDist(dist);
                    max_decDist.SetMax(atof(max));
                    max_decDist.SetMean(atof(mean));
                    max_decDist.SetMin(atof(min));
                    max_decDist.SetSD(atof(sd));
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

                    lc_param1Dist.SetDist(dist);
                    lc_param1Dist.SetMax(atof(max));
                    lc_param1Dist.SetMean(atof(mean));
                    lc_param1Dist.SetMin(atof(min));
                    lc_param1Dist.SetSD(atof(sd));
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

                    lc_param2Dist.SetDist(dist);
                    lc_param2Dist.SetMax(atof(max));
                    lc_param2Dist.SetMean(atof(mean));
                    lc_param2Dist.SetMin(atof(min));
                    lc_param2Dist.SetSD(atof(sd));
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

                    lc_senseDist.SetDist(dist);
                    lc_senseDist.SetMax(atof(max));
                    lc_senseDist.SetMean(atof(mean));
                    lc_senseDist.SetMin(atof(min));
                    lc_senseDist.SetSD(atof(sd));
                }
            }

            const char* id = elem->Attribute("id");
            const char* name = elem->Attribute("name");
            const char* max_pax = elem->Attribute("max_pax");

            if (!id)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!name)   throw std::runtime_error ("Element should have 'name' attribute");
            if (!max_pax)   max_pax = "1";

            InputVehicleTypes demoVehicleTypes(
                name, std::atoi(max_pax),
                veh_lenDist, veh_widthDist, jamgapDist, vfDist, reaction_timeDist, 
                max_accDist, max_decDist, lc_param1Dist, lc_param2Dist, lc_senseDist);

            m_vehTypes.insert({ std::atoi(id), demoVehicleTypes });
        }
    }
    doc.Clear();
};
} // namespace NextSimIO
