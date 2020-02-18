#include <iostream>
#include <string>
#include <sstream>

#include <gookto_io/ParamArr.hpp>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

// intialize with the meso params
ParamArr::ParamArr() : micro_veh_len(3), jam_gap(3), ff_speed(3), reaction_time(3), max_acc(3), max_dec(3)
{
    TiXmlDocument doc;

    doc.LoadFile("./network_xml/param.xml");
    std::cout << "Loading ParamArr" << std::endl;

    if (!doc.LoadFile("./network_xml/param.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "meso")
        {
            std::cout << "Got Meso Params" << std::endl;
            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();
                if ( elemName2 == "max_flow")
                {
                    setMaxFlow(atof(e->Attribute("value")));
                }

                if ( elemName2 == "veh_len")
                {
                    setMesoVehLen(atof(e->Attribute("value")));
                }

                if ( elemName2 == "wave_speed")
                {
                    setWaveSpeed(atof(e->Attribute("value")));
                }
            }
        }


        if (elemName == "micro")
        {
            std::cout << "Got Micro Params" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();
                const char* conv_str = elemName2.c_str();


                std::string dist = e->Attribute("dist");
                const char* model = dist.c_str();

                setMean(atof(e->Attribute("mean")), conv_str);
                setSd(atof(e->Attribute("sd")), conv_str);
                setModel(model, conv_str);
            }
        }
    }
    doc.Clear();
};


void ParamArr::setMean(float val, const char *str)
{
    if (strncmp(str, "veh_len", 5) == 0)
    {
        micro_veh_len[0] = val;
    }

    if (strncmp(str, "jam_gap", 5) == 0)
    {
        jam_gap[0] = val;
    }

    if (strncmp(str, "ff_speed", 5) == 0)
    {
        ff_speed[0] = val;
    }

    if (strncmp(str, "reaction_time", 5) == 0)
    {
        reaction_time[0] = val;
    }

    if (strncmp(str, "max_acc", 5) == 0)
    {
        max_acc[0] = val;
    }

    if (strncmp(str, "max_dec", 5) == 0)
    {
        max_dec[0] = val;
    }
};

void ParamArr::setSd(float val, const char *str)
{
    if (strncmp(str, "veh_len", 5) == 0)
    {
        micro_veh_len[1] = val;
    }

    if (strncmp(str, "jam_gap", 5) == 0)
    {
        jam_gap[1] = val;
    }

    if (strncmp(str, "ff_speed", 5) == 0)
    {
        ff_speed[1] = val;
    }

    if (strncmp(str, "reaction_time", 5) == 0)
    {
        reaction_time[1] = val;
    }

    if (strncmp(str, "max_acc", 5) == 0)
    {
        max_acc[1] = val;
    }

    if (strncmp(str, "max_dec", 5) == 0)
    {
        max_dec[1] = val;
    }
};

void ParamArr::setModel(const char *model, const char *str)
{
    float val;
    //first determine the model representation
    if (strncmp(model, "normal", 3) == 0)
    {
        val = 1.0;
    }

    if (strncmp(model, "lognormal", 3) == 0)
    {
        val = 2.0;
    }

    if (strncmp(model, "poisson", 3) == 0)
    {
        val = 3.0;
    }

    if (strncmp(str, "veh_len", 5) == 0)
    {
        micro_veh_len[2] = val;
    }

    if (strncmp(str, "jam_gap", 5) == 0)
    {
        jam_gap[2] = val;
    }

    if (strncmp(str, "ff_speed", 5) == 0)
    {
        ff_speed[2] = val;
    }

    if (strncmp(str, "reaction_time", 5) == 0)
    {
        reaction_time[2] = val;
    }

    if (strncmp(str, "max_acc", 5) == 0)
    {
        max_acc[2] = val;
    }

    if (strncmp(str, "max_dec", 5) == 0)
    {
        max_dec[2] = val;
    }
};