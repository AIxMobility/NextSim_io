/**
 * NextSim Captain
 * @file : ParamArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <iostream>
#include <string>
#include <sstream>

#include <NextSim_io/parser/ParamArr.hpp>

#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ParamArr::ParamArr()
    : micro_veh_len(3),
      jam_gap(3),
      ff_speed(3),
      reaction_time(3),
      max_acc(3),
      max_dec(3)
{
    TiXmlDocument doc;

    doc.LoadFile(NextSimIO::ParamXMLPath.string().c_str());
    // std::cout << "Loading ParamArr" << std::endl;

    if (!doc.LoadFile(NextSimIO::ParamXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (ParamArr)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();

    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "meso")
        {
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();
                if (elemName2 == "max_flow")
                {
                    const char *value = e->Attribute("value");

                    if (!value) throw std::runtime_error ("Element should have 'value' attribute");

                    SetMaxFlow(atof(value));
                }

                if (elemName2 == "veh_len")
                {
                    const char *value = e->Attribute("value");

                    if (!value) throw std::runtime_error ("Element should have 'value' attribute");

                    SetMesoVehLen(atof(value));
                }

                if (elemName2 == "wave_speed")
                {
                    const char *value = e->Attribute("value");

                    if (!value) throw std::runtime_error ("Element should have 'value' attribute");

                    SetWaveSpeed(atof(value));
                }
            }
        }

        if (elemName == "micro")
        {
            for (TiXmlElement* e = elem->FirstChildElement(); e != NULL;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();
                const char* conv_str = elemName2.c_str();

                std::string dist = e->Attribute("dist");
                const char* model = dist.c_str();

                SetMean(atof(e->Attribute("mean")), conv_str);
                SetSd(atof(e->Attribute("sd")), conv_str);
                SetModel(model, conv_str);
            }
        }
    }
    doc.Clear();
};


void ParamArr::SetMean(double val, std::string param)
{
    if (param == "veh_len")
    {
        micro_veh_len[0] = val;
    }
    else if (param == "jam_gap")
    {
        jam_gap[0] = val;
    }
    else if (param == "ff_speed")
    {
        ff_speed[0] = val;
    }
    else if (param == "reaction_time")
    {
        reaction_time[0] = val;
    }
    else if (param == "max_acc")
    {
        max_acc[0] = val;
    }
    else if (param == "max_dec")
    {
        max_dec[0] = val;
    }
};

void ParamArr::SetSd(double val, std::string param)
{
    if (param == "veh_len")
    {
        micro_veh_len[1] = val;
    }
    else if (param == "jam_gap")
    {
        jam_gap[1] = val;
    }
    else if (param == "ff_speed")
    {
        ff_speed[1] = val;
    }
    else if (param == "reaction_time")
    {
        reaction_time[1] = val;
    }
    else if (param == "max_acc")
    {
        max_acc[1] = val;
    }
    else if (param == "max_dec")
    {
        max_dec[1] = val;
    }
};

void ParamArr::SetModel(std::string model, std::string param)
{
    double val = 0;
    
    if (model == "normal")
    {
        val = 1.0;
    }
    else if (model == "lognormal")
    {
        val = 2.0;
    }
    else if (model == "poisson")
    {
        val = 3.0;
    }

    if (param == "veh_len")
    {
        micro_veh_len[2] = val;
    }
    else if (param == "jam_gap")
    {
        jam_gap[2] = val;
    }
    else if (param == "ff_speed")
    {
        ff_speed[2] = val;
    }
    else if (param == "reaction_time")
    {
        reaction_time[2] = val;
    }
    else if (param == "max_acc")
    {
        max_acc[2] = val;
    }
    else if (param == "max_dec")
    {
        max_dec[2] = val;
    }
};
} // namespace NextSimIO