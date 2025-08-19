/**
 * NextSim Captain
 * @file : RailLineArr.cpp
 * @version : 1.2
 * @author : Yuseock Hwang, Yeonwoo Yu, Sujae Jeon
 */
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

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
        const char* seqAttr = lineElem->Attribute("railStationSeq");

        if (!idAttr || !seqAttr) {
            std::cerr << "[WARN] Skipping Line: missing 'id' or 'railStationSeq'\n";
            continue;
        }

        std::string id = idAttr;
        std::string stationSeqStr = seqAttr;

        const char* feeAttr = lineElem->Attribute("fee");
        double fee = (feeAttr != nullptr) ? std::stod(feeAttr) : 0;

        std::vector<int> stationSeq;
        std::istringstream stationStream(stationSeqStr);
        int station;
        while (stationStream >> station)
        {
            stationSeq.push_back(station);
        }

        m_railLines.emplace_back(id, fee, stationSeq);
    }
    doc.Clear();
    
};
} // namespace NextSimIO