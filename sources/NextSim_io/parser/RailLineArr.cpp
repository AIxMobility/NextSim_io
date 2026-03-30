/**
 * NextSim Captain
 * @file : RailLineArr.cpp
 * @version : 2.0
 * @author : Yuseock Hwang, Dongheon Lee
 */
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include <NextSim_io/parser/RailLineArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
RailLineArr::RailLineArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::RailPTlineXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (RailLineArr)" << std::endl;
        return;
    }

    TiXmlElement *modeElem = doc.FirstChildElement("Mode");
    if (modeElem == nullptr)
    {
        std::cout << "Missing Mode element (RailLineArr)" << std::endl;
        return;
    }

    TiXmlElement *linesElem = modeElem->FirstChildElement("Lines");
    if (linesElem == nullptr)
    {
        std::cout << "Missing Lines element (RailLineArr)" << std::endl;
        return;
    }

    for (TiXmlElement *lineElem = linesElem->FirstChildElement("Line");
         lineElem != nullptr;
         lineElem = lineElem->NextSiblingElement("Line"))
    {
        const char *idAttr = lineElem->Attribute("id");
        if (idAttr == nullptr)
        {
            continue;
        }

        const char *feeAttr = lineElem->Attribute("fee");
        const double fee = (feeAttr != nullptr) ? std::stod(feeAttr) : 0.0;

        std::vector<std::string> departureTimes;
        const char *departureAttr = lineElem->Attribute("departureTime");
        if (departureAttr != nullptr)
        {
            std::stringstream departureStream(departureAttr);
            std::string departure;
            while (departureStream >> departure)
            {
                departureTimes.push_back(departure);
            }
        }

        std::vector<stationSeq> stationSeqList;
        std::vector<std::pair<int, stationSeq>> orderedStations;
        for (TiXmlElement *seqElem = lineElem->FirstChildElement("stationSeq");
             seqElem != nullptr;
             seqElem = seqElem->NextSiblingElement("stationSeq"))
        {
            const char *stationIdAttr = seqElem->Attribute("id");
            const char *seqAttr = seqElem->Attribute("seq");
            if (stationIdAttr == nullptr || seqAttr == nullptr)
            {
                continue;
            }

            const int stationId = std::stoi(stationIdAttr);
            const int seq = std::stoi(seqAttr);
            const char *timeOffsetAttr = seqElem->Attribute("timeOffset");
            const int timeOffset = (timeOffsetAttr != nullptr) ? std::stoi(timeOffsetAttr) : 0;

            orderedStations.emplace_back(seq, stationSeq(stationId, seq, timeOffset));
        }

        std::sort(orderedStations.begin(), orderedStations.end(),
                  [](const std::pair<int, stationSeq> &lhs, const std::pair<int, stationSeq> &rhs)
                  {
                      return lhs.first < rhs.first;
                  });
        stationSeqList.reserve(orderedStations.size());
        for (const auto &entry : orderedStations)
        {
            stationSeqList.push_back(entry.second);
        }

        InputRailLine line(idAttr, fee, departureTimes, stationSeqList);
        m_railline.push_back(line);
    }
    doc.Clear();
}
} // namespace NextSimIO