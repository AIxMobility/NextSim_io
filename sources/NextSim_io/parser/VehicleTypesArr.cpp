/**
 * NextSim Captain
 * @file : VehicleTypesArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <array>
#include <NextSim_io/RunErrors.hpp>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

#include <NextSim_io/parser/VehicleTypesArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
VehicleTypesArr::VehicleTypesArr() : VehicleTypesArr(NextSimIO::VehicleTypeXMLPath) {}

VehicleTypesArr::VehicleTypesArr(const std::filesystem::path& path)
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(path.string().c_str());

    if (!loadSuccess)
    {
        NextSimIO::ReportRunError("Loading failed (VehicleTypesArr)");
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
            std::optional<InputTramParameters> tramParameters;
            std::array<double, 3> powertrainRatios {1.0, 0.0, 0.0};

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
                else if (elemName2 == "tram_config")
                {
                    const char* segmentCount = e->Attribute("segment_count");
                    const char* segmentGap = e->Attribute("segment_gap");
                    const char* signalStopBuffer =
                        e->Attribute("signal_stop_buffer");
                    const char* stationStopTolerance =
                        e->Attribute("station_stop_tolerance");

                    if (!segmentCount)
                        throw std::runtime_error(
                            "tram_config requires 'segment_count'");
                    if (!segmentGap)
                        throw std::runtime_error(
                            "tram_config requires 'segment_gap'");
                    if (!signalStopBuffer)
                        throw std::runtime_error(
                            "tram_config requires 'signal_stop_buffer'");
                    if (!stationStopTolerance)
                        throw std::runtime_error(
                            "tram_config requires 'station_stop_tolerance'");

                    InputTramParameters parameters;
                    parameters.SegmentCount = std::atoi(segmentCount);
                    parameters.SegmentGapM = std::atof(segmentGap);
                    parameters.SignalStopBufferM = std::atof(signalStopBuffer);
                    parameters.StationStopToleranceM =
                        std::atof(stationStopTolerance);
                    if (parameters.SegmentCount <= 0
                        || parameters.SegmentGapM < 0.0
                        || parameters.SignalStopBufferM < 0.0
                        || parameters.StationStopToleranceM < 0.0)
                        throw std::runtime_error(
                            "tram_config values must be non-negative and segment_count must be positive");
                    if (const char* lengths = e->Attribute("segment_lengths"))
                    {
                        std::istringstream stream(lengths);
                        std::string token;
                        while (stream >> token)
                        {
                            std::size_t parsed = 0;
                            const double length = std::stod(token, &parsed);
                            if (parsed != token.size() || !std::isfinite(length) || length <= 0.0)
                                throw std::runtime_error("tram_config segment_lengths must contain positive finite lengths in meters");
                            parameters.SegmentLengthsM.push_back(length);
                        }
                        if (parameters.SegmentLengthsM.size() != static_cast<std::size_t>(parameters.SegmentCount))
                            throw std::runtime_error("tram_config segment_lengths must match segment_count");
                    }
                    tramParameters = parameters;
                }
                else if (elemName2 == "powertrain")
                {
                    constexpr std::array<const char*, 3> ratioAttributeNames {
                        "ice_ratio", "phev_ratio", "bev_ratio"
                    };

                    for (std::size_t i = 0; i < ratioAttributeNames.size(); ++i)
                    {
                        if (e->QueryDoubleAttribute(
                                ratioAttributeNames.at(i),
                                &powertrainRatios.at(i)) != TIXML_SUCCESS)
                        {
                            throw std::runtime_error(
                                std::string("Element 'powertrain' should have numeric '") +
                                ratioAttributeNames.at(i) + "' attribute");
                        }
                    }
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
            if (strcmp(name, "Tram") == 0
                && !tramParameters.has_value())
                throw std::runtime_error(
                    "Tram vehicle type requires a tram_config element");

            for (const double ratio : powertrainRatios)
            {
                if (!std::isfinite(ratio) || ratio < 0.0 || ratio > 1.0)
                {
                    throw std::runtime_error(
                        std::string("Powertrain ratios for vehicle type '") +
                        name + "' must be between 0 and 1");
                }
            }

            const double powertrainRatioSum = std::accumulate(
                powertrainRatios.begin(), powertrainRatios.end(), 0.0);
            if (std::fabs(powertrainRatioSum - 1.0) > 1e-9)
            {
                throw std::runtime_error(
                    std::string("Powertrain ratios for vehicle type '") + name +
                    "' must sum to 1.0");
            }

            // TODO: implement v2x on/off
            InputVehicleTypes demoVehicleTypes(
                name, std::atoi(max_pax), strcmp(v2x, "on") == 0 ? true : false,
                veh_lenDist, veh_widthDist, jamgapDist, vfDist, reaction_timeDist, 
                max_accDist, max_decDist, lc_param1Dist, lc_param2Dist, lc_senseDist,
                powertrainRatios, tramParameters);

            m_vehTypes.insert({ std::atoi(id), demoVehicleTypes });
        }
    }
    doc.Clear();
};
} // namespace NextSimIO
