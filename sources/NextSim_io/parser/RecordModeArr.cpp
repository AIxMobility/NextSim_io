/**
 * NextSim Captain
 * @file : RecordModeArr.cpp
 * @version : 1.0
 * @author : Chaemin Na
 */

#include <iostream>
#include <NextSim_io/RunErrors.hpp>
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
        NextSimIO::ReportRunError("Loading failed (RecordModes)");
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    // Older recordMode.xml files lack some elements (e.g. SignalControlEvent); a missing
    // element or active attribute means that output is off instead of a null dereference.
    auto isActive = [](TiXmlElement* parent, const char* name) {
        TiXmlElement* e = parent ? parent->FirstChildElement(name) : nullptr;
        const char* active = e ? e->Attribute("active") : nullptr;
        return active != nullptr && std::string(active) == "t";
    };

    // VehicleEvent (Debugging, Visualizer, Statistics)
    TiXmlElement *eVehicleEvent = root ? root->FirstChildElement("VehicleEvent") : nullptr;
    m_recordModes.emplace_back(InputRecordMode(0, isActive(eVehicleEvent, "Debugging")));
    m_recordModes.emplace_back(InputRecordMode(1, isActive(eVehicleEvent, "Visualizer")));
    m_recordModes.emplace_back(InputRecordMode(2, isActive(eVehicleEvent, "Statistics")));

    m_recordModes.emplace_back(InputRecordMode(3, isActive(root, "PassengerEvent")));
    m_recordModes.emplace_back(InputRecordMode(4, isActive(root, "UniformEvent")));
    m_recordModes.emplace_back(InputRecordMode(5, isActive(root, "StationEvent")));
    m_recordModes.emplace_back(InputRecordMode(6, isActive(root, "SinkEvent")));
    // SignalEvent (when visualizer is activated)
    m_recordModes.emplace_back(InputRecordMode(7, isActive(root, "SignalEvent")));
    // SignalControlEvent (when signalControl is activated)
    m_recordModes.emplace_back(InputRecordMode(9, isActive(root, "SignalControlEvent")));

    // DetectorEvent (optional)
    TiXmlElement *eDetectorEvent = root ? root->FirstChildElement("DetectorEvent") : nullptr;
    // An absent element keeps the historical behaviour (detector output on);
    // only an explicit active="f" turns detector recording off.
    bool activatedDetectorEvent = true;
    if (eDetectorEvent != nullptr && eDetectorEvent->Attribute("active") != nullptr)
        activatedDetectorEvent = std::string(eDetectorEvent->Attribute("active")) == "t";
    m_recordModes.emplace_back(InputRecordMode(10, activatedDetectorEvent));
    
    doc.Clear();
};
} // namespace NextSimIO