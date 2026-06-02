/**
 * NextSim Captain
 * @file : RailLineArr.cpp
 * @version : 2.0
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon, Dongheon Lee
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

    TiXmlElement* modeElem = doc.FirstChildElement("Mode");

    TiXmlElement* linesElem = modeElem->FirstChildElement("Lines");

    for (TiXmlElement* lineElem = linesElem->FirstChildElement("Line");
        lineElem != nullptr;
        lineElem = lineElem->NextSiblingElement("Line"))
    {
        const char* idAttr = lineElem->Attribute("id");
        if (!idAttr) {
            std::cerr << "[WARN] Skipping Line: missing 'id'\n";
            continue;
        }
        std::string id = idAttr;

        const char* feeAttr = lineElem->Attribute("fee");
        double fee = (feeAttr != nullptr) ? std::stod(feeAttr) : 0.0;

        // parse departureTime attribute (space-separated times)
        std::vector<std::string> departureTimes;
        const char* depAttr = lineElem->Attribute("departureTime");
        if (depAttr) {
            std::istringstream ds(depAttr);
            std::string t;
            while (ds >> t) departureTimes.push_back(t);
        }

        // parse stationSeq child elements with id, seq, timeOffset
        std::vector<stationSeq> stationSeqs;
        for (TiXmlElement* sElem = lineElem->FirstChildElement("stationSeq"); sElem != nullptr; sElem = sElem->NextSiblingElement("stationSeq")) {
            const char* sid = sElem->Attribute("id");
            const char* seq = sElem->Attribute("seq");
            const char* toff = sElem->Attribute("timeOffset");
            if (!sid || !seq || !toff) {
                std::cerr << "[WARN] Skipping stationSeq in line " << id << ": missing attributes\n";
                continue;
            }
            int stationId = std::stoi(sid);
            int seqInt = std::stoi(seq);
            int timeOffset = std::stoi(toff);
            stationSeqs.emplace_back(stationId, seqInt, timeOffset);
        }

        m_railLines.emplace_back(id, fee, departureTimes, stationSeqs);
    }
    doc.Clear();
}
} // namespace NextSimIO