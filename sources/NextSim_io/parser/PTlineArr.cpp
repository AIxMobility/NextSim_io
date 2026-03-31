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
#include <algorithm>

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
            double fee = 0;
            int interval = 0;

            if (lineElem->Attribute("id"))
                id = lineElem->Attribute("id");
            if (lineElem->Attribute("fee"))
                fee = std::stod(lineElem->Attribute("fee"));
            if (lineElem->Attribute("interval"))
                interval = std::stoi(lineElem->Attribute("interval"));

            InputPTline tPTline(id, fee, interval);

            TiXmlElement* linksElem = lineElem->FirstChildElement("links");
            if (linksElem)
            {
                for (TiXmlElement* linkElem = linksElem->FirstChildElement("link");
                    linkElem != nullptr;
                    linkElem = linkElem->NextSiblingElement("link"))
                {
                    int link_id = 0;
                    int seq = 0;
                    bool use_ptlane = false;

                    const char* attr = nullptr;

                    if ((attr = linkElem->Attribute("id")))
                        link_id = std::stoi(attr);
                    if ((attr = linkElem->Attribute("seq")))
                        seq = std::stoi(attr);
                    if ((attr = linkElem->Attribute("use_ptlane")))
                        use_ptlane = (std::string(attr) == "True");
                    if ((attr = linkElem->Attribute("station")))
                    {
                        tPTline.PushStationSeq(std::stoi(attr));
                    }
                    if ((attr = linkElem->Attribute("garage")))
                    {
                        tPTline.PushGarageSeq(std::stoi(attr));
                    }

                    InputPTlink ptlink(link_id, seq, use_ptlane);
                    tPTline.PushPTlink(ptlink);
                }
            }

            if (mode == "Bus")
                m_busLines.push_back(tPTline);
            else if (mode == "TRT")
                m_trtLines.push_back(tPTline);
            else if (mode == "Tram")
                m_tramLines.push_back(tPTline);
            else
                std::cerr << "Unknown mode: " << mode << " for line id: " << id << std::endl;
        }
    }
}

} // namespace NextSimIO
 