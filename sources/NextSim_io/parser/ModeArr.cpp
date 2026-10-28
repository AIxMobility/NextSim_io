/**
 * NextSim Captain
 * @file : ModeArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <filesystem>

#include <NextSim_io/parser/ModeArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ModeArr::ModeArr()
{    
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::ModeXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (ModeArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for(TiXmlElement *elem = root ? root->FirstChildElement() : NULL ; elem != NULL ; elem = elem->NextSiblingElement())
    {
        const char* idAttr = elem->Attribute("id");
        const char* stimeAttr = elem->Attribute("stime");
        if (!idAttr || !stimeAttr)
            throw std::runtime_error("mode.xml: every <period> needs id and stime attributes");
        int id = std::stoi(idAttr);
        int stime = std::stoi(stimeAttr);

        InputMode tMode = InputMode(id, stime);

        // A period may leave out <micro> or <meso>; the engine runs links it does not list as micro.
        for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
            std::string eName = e->Value();
            const char* linkIds = e->Attribute("linkid");
            if (eName == "micro")
                tMode.SetMicroLinkVector(linkIds ? linkIds : "");
            else if (eName == "meso")
                tMode.SetMesoLinkVector(linkIds ? linkIds : "");
        }

        m_modes.push_back(tMode);
    }
}
} // namespace NextSimIO