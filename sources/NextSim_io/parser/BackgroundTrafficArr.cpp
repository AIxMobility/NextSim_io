/**
 * NextSim Captain
 * @file : BackgroundTrafficArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <iostream>
#include <sstream>
#include <string>

#include <NextSim_io/parser/BackgroundTrafficArr.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
BackgroundTrafficArr::BackgroundTrafficArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::BackgroundTrafficXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (BackgroundTraffics)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();
    
    for (TiXmlElement *state = root->FirstChildElement();
            state != NULL; state = state->NextSiblingElement())
    {
        const char *link = state->Attribute("id");
        const char *avgSpd = state->Attribute("avgSpd");
        const char *density = state->Attribute("density");

        if (!link)
            throw std::runtime_error(
                "Element should have 'link' attribute");
        if (!avgSpd)
            throw std::runtime_error(
                "Element should have 'avgSpd' attribute");
        if (!density)
            throw std::runtime_error(
                "Element should have 'density' attribute");

        InputBackgroundTraffic singleState(
            atoi(link), 
            atof(avgSpd), 
            atof(density));

        m_BackgroundTraffics.push_back(singleState);
    }
    doc.Clear();
};
} // namespace NextSimIO