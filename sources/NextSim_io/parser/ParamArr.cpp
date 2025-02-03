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
    : m_microVehLen(3),
      m_jamgap(3),
      m_ffSpeed(3),
      m_reactionTime(3),
      m_maxAcc(3),
      m_maxDec(3)
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::ParamXMLPath.string().c_str());

    if (!loadSuccess)
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
        m_microVehLen[0] = val;
    }
    else if (param == "jam_gap")
    {
        m_jamgap[0] = val;
    }
    else if (param == "ff_speed")
    {
        m_ffSpeed[0] = val;
    }
    else if (param == "reaction_time")
    {
        m_reactionTime[0] = val;
    }
    else if (param == "max_acc")
    {
        m_maxAcc[0] = val;
    }
    else if (param == "max_dec")
    {
        m_maxDec[0] = val;
    }
};

void ParamArr::SetSd(double val, std::string param)
{
    if (param == "veh_len")
    {
        m_microVehLen[1] = val;
    }
    else if (param == "jam_gap")
    {
        m_jamgap[1] = val;
    }
    else if (param == "ff_speed")
    {
        m_ffSpeed[1] = val;
    }
    else if (param == "reaction_time")
    {
        m_reactionTime[1] = val;
    }
    else if (param == "max_acc")
    {
        m_maxAcc[1] = val;
    }
    else if (param == "max_dec")
    {
        m_maxDec[1] = val;
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
        m_microVehLen[2] = val;
    }
    else if (param == "jam_gap")
    {
        m_jamgap[2] = val;
    }
    else if (param == "ff_speed")
    {
        m_ffSpeed[2] = val;
    }
    else if (param == "reaction_time")
    {
        m_reactionTime[2] = val;
    }
    else if (param == "max_acc")
    {
        m_maxAcc[2] = val;
    }
    else if (param == "max_dec")
    {
        m_maxDec[2] = val;
    }
};
} // namespace NextSimIO