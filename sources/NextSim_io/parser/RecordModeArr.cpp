/**
 * NextSim Captain
 * @file : RecordModeArr.cpp
 * @version : 1.0
 * @author : Chaemin Na
 */

#include <iostream>
#include <sstream>
#include <string>

#include <NextSim_io/parser/RecordModeArr.hpp>
#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
RecordModeArr::RecordModeArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::RecordModeXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (RecordModes)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();
    
    // VehicleEvent (Debugging, Visualizer, Statistics)
    TiXmlElement *eVehicleEvent = root->FirstChildElement("VehicleEvent");

    TiXmlElement *eDebugging = eVehicleEvent->FirstChildElement("Debugging");
    bool activatedDebugging = std::string(eDebugging->Attribute("active")) == "t";
    InputRecordMode recordModeDebugging(0, activatedDebugging);
    m_recordModes.emplace_back(recordModeDebugging);

    TiXmlElement *eVisualizer = eVehicleEvent->FirstChildElement("Visualizer");
    bool activatedVisualizer = std::string(eVisualizer->Attribute("active")) == "t";
    InputRecordMode recordModeVisualizer(1, activatedVisualizer);
    m_recordModes.emplace_back(recordModeVisualizer);

    TiXmlElement *eStatistics = eVehicleEvent->FirstChildElement("Statistics");
    bool activatedStatistics = std::string(eStatistics->Attribute("active")) == "t";
    InputRecordMode recordModeStatistics(2, activatedStatistics);
    m_recordModes.emplace_back(recordModeStatistics);


    // PassengerEvent
    TiXmlElement *ePassengerEvent = root->FirstChildElement("PassengerEvent");

    bool activatedPassengerEvent = std::string(ePassengerEvent->Attribute("active")) == "t";
    InputRecordMode recordModePassengerEvent(3, activatedPassengerEvent);
    m_recordModes.emplace_back(recordModePassengerEvent);


    // UniformEvent
    TiXmlElement *eUniformEvent = root->FirstChildElement("UniformEvent");

    bool activatedUniformEvent = std::string(eUniformEvent->Attribute("active")) == "t";
    InputRecordMode recordModeUniformEvent(4, activatedUniformEvent);
    m_recordModes.emplace_back(recordModeUniformEvent);


    // StationEvent
    TiXmlElement *eStationEvent = root->FirstChildElement("StationEvent");

    bool activatedStationEvent = std::string(eStationEvent->Attribute("active")) == "t";
    InputRecordMode recordModeStationEvent(5, activatedStationEvent);
    m_recordModes.emplace_back(recordModeStationEvent);


    // SinkEvent
    TiXmlElement *eSinkEvent = root->FirstChildElement("SinkEvent");

    bool activatedSinkEvent = std::string(eSinkEvent->Attribute("active")) == "t";
    InputRecordMode recordModeSinkEvent(6, activatedSinkEvent);
    m_recordModes.emplace_back(recordModeSinkEvent);
    
    doc.Clear();
};
} // namespace NextSimIO