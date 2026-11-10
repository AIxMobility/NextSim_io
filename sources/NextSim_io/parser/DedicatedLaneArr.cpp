/**
 * NextSim Captain
 * @file : DedicatedLaneArr.cpp
 */

#include <NextSim_io/parser/DedicatedLaneArr.hpp>

#include <NextSim_io/FilePath.hpp>
#include <NextSim_io/tinyapi/tinyxml.h>

#include <cstdlib>
#include <set>
#include <stdexcept>
#include <string>

namespace NextSimIO
{
namespace
{
const std::set<std::string> kTypes = { "BusOnly", "TramOnly", "HOVOnly", "BikeOnly" };

[[noreturn]] void Fail(const std::string& where, const std::string& message)
{
    throw std::runtime_error("dedicatedLane.xml: " + where + ": " + message);
}

int ParseClock(const char* text, const std::string& where)
{
    // HH:MM or HH:MM:SS, 24:00 allowed as the end of the day
    int h = 0, m = 0, s = 0;
    char extra = 0;
    const int read = text ? std::sscanf(text, "%d:%d:%d%c", &h, &m, &s, &extra) : 0;
    if ((read != 2 && read != 3) || h < 0 || h > 24 || m < 0 || m > 59 || s < 0 || s > 59
        || (h == 24 && (m != 0 || s != 0)))
        Fail(where, std::string("bad time '") + (text ? text : "") + "', expected HH:MM");
    return h * 3600 + m * 60 + s;
}

double ParseLength(const char* text, const std::string& where, const char* name)
{
    if (!text)
        return DefaultDedicatedEntryLength;
    char* end = nullptr;
    const double value = std::strtod(text, &end);
    if (end == text || *end != '\0' || !(value >= 0.0))
        Fail(where, std::string(name) + " must be a length in metres, got '" + text + "'");
    return value;
}
}  // namespace

DedicatedLaneArr::DedicatedLaneArr() : DedicatedLaneArr(DedicatedLaneXMLPath) {}

DedicatedLaneArr::DedicatedLaneArr(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
        return;
    TiXmlDocument doc;
    if (!doc.LoadFile(path.string().c_str()))
        Fail("file", std::string("cannot be read: ") + doc.ErrorDesc());
    m_hasFile = true;

    const TiXmlElement* root = doc.RootElement();
    if (root == nullptr || std::string(root->Value()) != "DedicatedLanes")
        Fail("file", "root element should be <DedicatedLanes>");

    for (const TiXmlElement* e = root->FirstChildElement("lane"); e; e = e->NextSiblingElement("lane"))
    {
        const char* link = e->Attribute("link");
        const char* lane = e->Attribute("lane");
        if (!link || !lane)
            Fail("lane", "every <lane> needs link and lane attributes");
        const std::string where = std::string("link ") + link + " lane " + lane;

        InputDedicatedLane info;
        const char* type = e->Attribute("type");
        if (!type || !kTypes.count(type))
            Fail(where, std::string("type should be BusOnly, TramOnly, HOVOnly or BikeOnly, got '") + (type ? type : "") + "'");
        info.Type = type;

        const char* strict = e->Attribute("strict");
        if (strict && std::string(strict) != "true" && std::string(strict) != "false")
            Fail(where, std::string("strict should be true or false, got '") + strict + "'");
        info.Strict = strict && std::string(strict) == "true";
        info.EntryEnd = ParseLength(e->Attribute("entry_end"), where, "entry_end");

        for (const TiXmlElement* h = e->FirstChildElement("hours"); h; h = h->NextSiblingElement("hours"))
        {
            const int start = ParseClock(h->Attribute("start"), where);
            const int end = ParseClock(h->Attribute("end"), where);
            if (end <= start)
                Fail(where, "hours end must be after start");
            info.Hours.emplace_back(start, end);
        }

        const auto key = std::make_pair(static_cast<std::size_t>(std::atoll(link)),
                                        static_cast<std::size_t>(std::atoll(lane)));
        if (!m_lanes.emplace(key, info).second)
            Fail(where, "listed twice");
    }
}

const InputDedicatedLane* DedicatedLaneArr::Find(std::size_t linkId, std::size_t laneId) const
{
    const auto it = m_lanes.find({ linkId, laneId });
    return it == m_lanes.end() ? nullptr : &it->second;
}

std::string DedicatedLaneArr::AccessType(std::size_t linkId, std::size_t laneId, const char* networkXmlType) const
{
    if (!m_hasFile)
        return networkXmlType ? networkXmlType : "All";
    const auto* lane = Find(linkId, laneId);
    return lane ? lane->Type : "All";
}

bool DedicatedLaneArr::IsStrict(std::size_t linkId, std::size_t laneId, const char* networkXmlType) const
{
    if (!m_hasFile)
        return networkXmlType && std::string(networkXmlType) == "TramOnly";
    const auto* lane = Find(linkId, laneId);
    return lane && lane->Strict;
}
}  // namespace NextSimIO
