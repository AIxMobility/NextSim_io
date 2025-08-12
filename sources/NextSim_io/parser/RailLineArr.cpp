/**
 * NextSim Captain
 * @file : RailLineArr.cpp
 * @version : 1.0
 * @author : Yuseock Hwang
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
        std::cout << "Loading failed (RailStationArr)" << std::endl;
        return;
    }

    TiXmlElement *modeElem = doc.FirstChildElement("Mode");

    TiXmlElement *linesElem = modeElem->FirstChildElement("Lines");

    for (TiXmlElement *lineElem = linesElem->FirstChildElement("Line");
             lineElem != nullptr;
             lineElem = lineElem->NextSiblingElement("Line"))
    {
        std::string id = lineElem->Attribute("id");
        double fee = std::stod(lineElem->Attribute("fee"));
        std::string stationSeqStr = lineElem->Attribute("railStationSeq");

        std::vector<int> stationSeq;
        std::istringstream stationStream(stationSeqStr);
        int station;
        while (stationStream >> station)
        {
            stationSeq.push_back(station);
        }

        InputRailLine line(id, fee, stationSeq);
        m_railline.push_back(line);
    }
    doc.Clear();


};
} // namespace NextSimIO