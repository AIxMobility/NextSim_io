/**
 * NextSim Captain
 * @file : PTLineArr.cpp
 * @version : 1.1
 * @author : Sujae Jeon, Yeonwoo Yu
 */

#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>

#include <NextSim_io/parser/PTlineArr.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
PTlineArr::PTlineArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::RoadPTlineXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cerr << "Loading failed (PTLineArr)" << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement(); 
    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())
    {
        std::string id;
        double fee = 0;
        int interval = 0;

        if (elem->Attribute("id"))
            id = elem->Attribute("id");
        if (elem->Attribute("fee"))
            fee = std::stod(elem->Attribute("fee"));
        if (elem->Attribute("interval"))
            interval = std::stoi(elem->Attribute("interval"));

        InputPTline PTline(id, fee, interval);

        TiXmlElement* e = elem->FirstChildElement("link");
        if (e && e->Attribute("seq"))
        {
            PTline.SetLinkSeq(e->Attribute("seq"));
        }

        e = elem->FirstChildElement("node");
        if (e && e->Attribute("seq"))
        {
            PTline.SetNodeSeq(e->Attribute("seq"));
        }

        e = elem->FirstChildElement("station");
        if (e && e->Attribute("seq"))
        {
            PTline.SetStationSeq(e->Attribute("seq"));
        }

        e = elem->FirstChildElement("garage");
        if (e)
        {
            if (e->Attribute("id"))
            {
                PTline.SetGarageSeq(e->Attribute("id"));
            }
            else if (e->Attribute("seq"))
            {
                PTline.SetGarageSeq(e->Attribute("seq"));
            }
        }

        m_ptLines.push_back(PTline);
    }
}

} // namespace NextSimIO
 