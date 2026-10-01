/**
 * NextSim Captain
 * @file : DetectorArr.cpp
 * @version : 1.0
 * @author : Keunhee Cho
 */

#include <NextSim_io/parser/DetectorArr.hpp>

#include <iostream>
#include <optional>
#include <string>
#include <cstdlib>

#include <NextSim_io/FilePath.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>

namespace NextSimIO
{
namespace
{
double ParseDouble(const TiXmlElement* elem, const char* name, double defaultValue)
{
    const char* raw = elem->Attribute(name);
    if (raw == nullptr)
        return defaultValue;
    return atof(raw);
}

int ParseInt(const TiXmlElement* elem, const char* name, int defaultValue)
{
    const char* raw = elem->Attribute(name);
    if (raw == nullptr)
        return defaultValue;
    return atoi(raw);
}

std::string ParseString(const TiXmlElement* elem, const char* name, const std::string& defaultValue)
{
    const char* raw = elem->Attribute(name);
    if (raw == nullptr)
        return defaultValue;
    return std::string(raw);
}

bool ParseBool(const TiXmlElement* elem, const char* name, bool defaultValue)
{
    const char* raw = elem->Attribute(name);
    if (raw == nullptr)
        return defaultValue;

    const std::string text(raw);
    return (text == "true" || text == "t" || text == "1" ||
            text == "TRUE" || text == "T");
}

std::optional<InputDetectorPoint> ParsePoint(const TiXmlElement* pointElem)
{
    if (pointElem == nullptr)
        return std::nullopt;

    const char* linkId = pointElem->Attribute("linkId");
    const char* laneIndex = pointElem->Attribute("laneIndex");
    const char* pos = pointElem->Attribute("pos");
    if (linkId == nullptr || laneIndex == nullptr || pos == nullptr)
        return std::nullopt;

    InputDetectorPoint point;
    point.LinkId = atoi(linkId);
    point.LaneIndex = atoi(laneIndex);
    point.Pos = atof(pos);
    return point;
}
} // namespace

DetectorArr::DetectorArr()
{
    TiXmlDocument doc;
    const bool loadSuccess = doc.LoadFile(NextSimIO::DetectorXMLPath.string().c_str());
    if (!loadSuccess)
    {
        std::cout << "Loading failed (DetectorArr): "
                  << NextSimIO::DetectorXMLPath.string() << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement("detectors");
    if (root == nullptr)
        root = doc.FirstChildElement();
    if (root == nullptr)
        return;

    if (TiXmlElement* e1Root = root->FirstChildElement("e1Detectors"))
    {
        for (TiXmlElement* elem = e1Root->FirstChildElement("e1Detector");
             elem != nullptr;
             elem = elem->NextSiblingElement("e1Detector"))
        {
            const std::string id = ParseString(elem, "id", "");
            const int linkId = ParseInt(elem, "linkId", -1);
            const int laneIndex = ParseInt(elem, "laneIndex", -1);
            const double pos = ParseDouble(elem, "pos", 0.0);
            const double begin = ParseDouble(elem, "begin", 0.0);
            const double end = ParseDouble(elem, "end", -1.0);
            const double freq = ParseDouble(elem, "freq", 60.0);
            const bool friendlyPos = ParseBool(elem, "friendlyPos", true);
            const std::string vTypes = ParseString(elem, "vTypes", "");

            if (id.empty() || linkId < 0 || laneIndex < 0)
                continue;

            m_e1Detectors.emplace_back(
                id, linkId, laneIndex, pos, begin, end, freq, friendlyPos, vTypes);
        }
    }

    if (TiXmlElement* e2Root = root->FirstChildElement("e2Detectors"))
    {
        for (TiXmlElement* elem = e2Root->FirstChildElement("e2Detector");
             elem != nullptr;
             elem = elem->NextSiblingElement("e2Detector"))
        {
            const std::string id = ParseString(elem, "id", "");
            const int linkId = ParseInt(elem, "linkId", -1);
            const int laneIndex = ParseInt(elem, "laneIndex", -1);
            const double pos = ParseDouble(elem, "pos", 0.0);
            const double endPos = ParseDouble(elem, "endPos", pos);
            const double begin = ParseDouble(elem, "begin", 0.0);
            const double end = ParseDouble(elem, "end", -1.0);
            const double freq = ParseDouble(elem, "freq", 60.0);
            const bool friendlyPos = ParseBool(elem, "friendlyPos", true);
            const std::string vTypes = ParseString(elem, "vTypes", "");

            if (id.empty() || linkId < 0 || laneIndex < 0)
                continue;

            m_e2Detectors.emplace_back(id, linkId, laneIndex, pos, endPos, begin,
                                       end, freq, friendlyPos, vTypes);
        }
    }

    if (TiXmlElement* e3Root = root->FirstChildElement("e3Detectors"))
    {
        for (TiXmlElement* elem = e3Root->FirstChildElement("e3Detector");
             elem != nullptr;
             elem = elem->NextSiblingElement("e3Detector"))
        {
            const std::string id = ParseString(elem, "id", "");
            const double begin = ParseDouble(elem, "begin", 0.0);
            const double end = ParseDouble(elem, "end", -1.0);
            const double freq = ParseDouble(elem, "freq", 60.0);
            const bool friendlyPos = ParseBool(elem, "friendlyPos", true);
            const bool openEntry = ParseBool(elem, "openEntry", false);
            const std::string vTypes = ParseString(elem, "vTypes", "");

            std::vector<InputDetectorPoint> entryPoints;
            std::vector<InputDetectorPoint> exitPoints;

            if (TiXmlElement* entryRoot = elem->FirstChildElement("entryPoints"))
            {
                for (TiXmlElement* pointElem = entryRoot->FirstChildElement("point");
                     pointElem != nullptr;
                     pointElem = pointElem->NextSiblingElement("point"))
                {
                    const auto point = ParsePoint(pointElem);
                    if (point.has_value())
                        entryPoints.emplace_back(point.value());
                }
            }

            if (TiXmlElement* exitRoot = elem->FirstChildElement("exitPoints"))
            {
                for (TiXmlElement* pointElem = exitRoot->FirstChildElement("point");
                     pointElem != nullptr;
                     pointElem = pointElem->NextSiblingElement("point"))
                {
                    const auto point = ParsePoint(pointElem);
                    if (point.has_value())
                        exitPoints.emplace_back(point.value());
                }
            }

            if (id.empty() || entryPoints.empty() || exitPoints.empty())
                continue;

            m_e3Detectors.emplace_back(id, begin, end, freq, friendlyPos, openEntry,
                                       vTypes, std::move(entryPoints),
                                       std::move(exitPoints));
        }
    }

    doc.Clear();
}
} // namespace NextSimIO
