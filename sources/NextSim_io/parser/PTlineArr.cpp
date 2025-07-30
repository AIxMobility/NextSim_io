/**
 * NextSim Captain
 * @file : PTLineArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
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

    for (TiXmlElement* linesElem = root; linesElem != nullptr; linesElem = linesElem->NextSiblingElement("Lines"))
    {
        const char* modeAttr = linesElem->Attribute("mode");
        std::string mode = modeAttr ? modeAttr : "";
        for (TiXmlElement* lineElem = linesElem->FirstChildElement("Line"); lineElem != nullptr; lineElem = lineElem->NextSiblingElement("Line"))
        {
            // Get required attributes: id & interval
            std::string id;
            int interval = 0;

            if (lineElem->Attribute("id"))
                id = lineElem->Attribute("id");
            if (lineElem->Attribute("interval"))
                interval = std::stoi(lineElem->Attribute("interval"));

            InputPTline tPTline(id, interval);

            // link
            TiXmlElement* e = lineElem->FirstChildElement("link");
            if (e && e->Attribute("seq"))
                tPTline.SetLinkSeq(e->Attribute("seq"));

            // node
            e = lineElem->FirstChildElement("node");
            if (e && e->Attribute("seq"))
                tPTline.SetNodeSeq(e->Attribute("seq"));

            // station
            e = lineElem->FirstChildElement("station");
            if (e && e->Attribute("seq"))
                tPTline.SetStationSeq(e->Attribute("seq"));

            // garage (있을 수도 없을 수도 있음)
            e = lineElem->FirstChildElement("garage");
            if (e)
            {
                if (e->Attribute("id"))
                    tPTline.SetGarageSeq(e->Attribute("id"));
                else if (e->Attribute("seq"))
                    tPTline.SetGarageSeq(e->Attribute("seq"));
            }

            if (mode == "Bus")
                m_busLines.push_back(tPTline);
            else if (mode == "TRT")
                m_trtLines.push_back(tPTline);
            else
                std::cerr << "Unknown mode: " << mode << " for line id: " << id << std::endl;
        }
    }
}

} // namespace NextSimIO
 