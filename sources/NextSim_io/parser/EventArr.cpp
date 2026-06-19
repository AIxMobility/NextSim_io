/**
 * NextSim Captain
 * @file : EventArr.cpp
 * @version : 1.1
 * @author : Jeyun Kim
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <cctype>

#include <NextSim_io/parser/EventArr.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
namespace
{
std::string TrimString(std::string value)
{
    const auto begin = value.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) return "";
    const auto end = value.find_last_not_of(" \t\r\n");
    return value.substr(begin, end - begin + 1);
}

bool HasText(const char* text)
{
    return text != nullptr && !TrimString(text).empty();
}

std::vector<int> ParseLaneVector(const char* laneText)
{
    std::vector<int> laneVector;
    const std::string text = TrimString(laneText ? laneText : "");
    if (text.empty())
    {
        laneVector.push_back(-1);
        return laneVector;
    }

    std::string normalized = text;
    for (char& ch : normalized)
    {
        if (ch == ',') ch = ' ';
    }

    std::stringstream laneStream(normalized);
    int laneID = -1;
    while (laneStream >> laneID)
    {
        laneVector.push_back(laneID);
    }

    if (laneVector.empty())
    {
        throw std::runtime_error("Element should have valid laneIds attribute");
    }

    return laneVector;
}

bool ParsePositionRange(const char* startPosText, const char* endPosText,
                        double& startPos, double& endPos)
{
    const bool hasStartPos = HasText(startPosText);
    const bool hasEndPos = HasText(endPosText);
    if (!hasStartPos && !hasEndPos)
    {
        startPos = 0.0;
        endPos = 0.0;
        return false;
    }
    if (hasStartPos != hasEndPos)
    {
        throw std::runtime_error("startPos and endPos should both be empty or both be specified");
    }

    startPos = std::atof(startPosText);
    endPos = std::atof(endPosText);
    return true;
}

double ParseHMSTimeToSeconds(const char* timeText)
{
    const std::string text = TrimString(timeText ? timeText : "");
    if (text.empty()) return 0.0;

    std::stringstream ss(text);
    std::string token;
    std::vector<int> parts;
    while (std::getline(ss, token, ':'))
    {
        const std::string trimmed = TrimString(token);
        if (trimmed.empty()) throw std::runtime_error("stime should be HH:MM:SS");
        for (char ch : trimmed)
        {
            if (!std::isdigit(static_cast<unsigned char>(ch)))
                throw std::runtime_error("stime should be HH:MM:SS");
        }
        parts.push_back(std::stoi(trimmed));
    }

    if (parts.size() != 3)
        throw std::runtime_error("stime should be HH:MM:SS");
    if (parts[0] < 0 || parts[0] > 23 || parts[1] < 0 || parts[1] > 59 || parts[2] < 0 || parts[2] > 59)
        throw std::runtime_error("stime should be HH:MM:SS");

    return static_cast<double>(parts[0] * 3600 + parts[1] * 60 + parts[2]);
}

double ParseDuration(const char* durationText)
{
    if (!HasText(durationText)) return -1.0;
    return std::atof(durationText);
}

InputEvent ParseEventElement(TiXmlElement* elem, int msgType)
{
    const char* id = elem->Attribute("id");
    const char* linkId = elem->Attribute("linkId");
    const char* laneIds = elem->Attribute("laneIds");
    const char* startPosText = elem->Attribute("startPos");
    const char* endPosText = elem->Attribute("endPos");
    const char* stime = elem->Attribute("stime");
    const char* duration = elem->Attribute("duration");
    const char* type = elem->Attribute("type");
    const char* sern = elem->Attribute("sern");
    const char* speedLimit = elem->Attribute("speedLimit");
    const char* detail = elem->Attribute("detail");

    if (!id) throw std::runtime_error("Element should have 'id' attribute");
    if (!linkId) throw std::runtime_error("Element should have 'linkId' attribute");

    double startPos = 0.0;
    double endPos = 0.0;
    const bool hasPosRange = ParsePositionRange(startPosText, endPosText, startPos, endPos);
    const bool hasStartTime = HasText(stime);
    const double startTime = hasStartTime ? ParseHMSTimeToSeconds(stime) : 0.0;
    const double durationSec = ParseDuration(duration);
    const auto laneVector = ParseLaneVector(laneIds);

    int eventType = 0;
    int severity = 1;
    double speedLimitValue = 0.0;
    if (msgType == ToInt(InputEventMsgType::RoadEvent))
    {
        if (!type) type = "1";
        if (!sern) sern = "1";
        eventType = std::atoi(type);
        severity = std::atoi(sern);
    }
    else if (msgType == ToInt(InputEventMsgType::SpeedLimit))
    {
        if (!speedLimit) throw std::runtime_error("SpeedLimit event should have 'speedLimit' attribute");
        speedLimitValue = std::atof(speedLimit);
    }

    return InputEvent(
        static_cast<int>(std::atoll(id)),
        static_cast<std::size_t>(std::atoll(linkId)),
        hasPosRange,
        startPos,
        endPos,
        laneVector,
        hasStartTime,
        startTime,
        durationSec,
        msgType,
        eventType,
        severity,
        speedLimitValue,
        detail ? detail : "");
}
} // namespace

EventArr::EventArr()
{
    TiXmlDocument doc;
    const bool loadSuccess = doc.LoadFile(NextSimIO::EventXMLPath.string().c_str());
    if (!loadSuccess)
    {
        std::cout << "Loading failed (EventArr)" << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (!root)
    {
        return;
    }

    for (TiXmlElement* category = root->FirstChildElement(); category != nullptr;
         category = category->NextSiblingElement())
    {
        const std::string categoryName = category->Value();
        int msgType = 0;
        if (categoryName == "RoadEvents")
        {
            msgType = ToInt(InputEventMsgType::RoadEvent);
        }
        else if (categoryName == "SpeedLimitEvents")
        {
            msgType = ToInt(InputEventMsgType::SpeedLimit);
        }
        else
        {
            throw std::runtime_error("events.xml should contain only RoadEvents or SpeedLimitEvents categories");
        }

        for (TiXmlElement* elem = category->FirstChildElement(); elem != nullptr;
             elem = elem->NextSiblingElement())
        {
            if (std::string(elem->Value()) != "event")
            {
                throw std::runtime_error("events.xml category should contain only event elements");
            }
            m_events.push_back(ParseEventElement(elem, msgType));
        }
    }

    doc.Clear();
}
} // namespace NextSimIO
