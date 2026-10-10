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
#include <algorithm>
#include <stdexcept>

#include <NextSim_io/parser/PTlineArr.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
namespace
{
// 빈 값이나 숫자가 아닌 값이면 std::stoi/stod 가 이유 없이 "stoi" 예외만 던졌다 — 어느 노선의 어느 값인지 알린다.
template <typename Parse>
auto ParseLineNumber(const char* raw, const std::string& lineId, const char* field, Parse parse)
{
    try
    {
        return parse(std::string(raw));
    }
    catch (const std::exception&)
    {
        throw std::runtime_error("roadPTline.xml: line " + lineId + " has an invalid " + field + " '" +
                                 std::string(raw) + "'");
    }
}
}  // namespace

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
                fee = ParseLineNumber(lineElem->Attribute("fee"), id, "fee",
                                      [](const std::string& value) { return std::stod(value); });
            if (lineElem->Attribute("interval"))
                interval = ParseLineNumber(lineElem->Attribute("interval"), id, "interval",
                                           [](const std::string& value) { return std::stoi(value); });

            // 노선 종류: 라인의 type 속성(웹 에디터가 쓴다)이 있으면 그것을, 없으면 <Lines mode> 를 따른다
            const char* typeAttr = lineElem->Attribute("type");
            const std::string lineMode = (typeAttr && *typeAttr) ? typeAttr : mode;

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

            if (lineMode == "Bus")
                m_busLines.push_back(tPTline);
            else if (lineMode == "TRT")
                m_trtLines.push_back(tPTline);
            else if (lineMode == "Tram")
                m_tramLines.push_back(tPTline);
            else
                std::cerr << "Unknown mode: " << lineMode << " for line id: " << id << std::endl;
        }
    }
}
} // namespace NextSimIO
 