/**
 * NextSim Captain
 * @file : SignalControlArr.cpp
 * @version : 1.0
 * @author : Chaemin Na
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cctype>

#include <NextSim_io/parser/SignalControlArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
SignalControlArr::SignalControlArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::SignalControlXMLPath.string().c_str());

    if (!loadSuccess)
    {
        // std::cout << "Loading failed (SignalControlArr)" << std::endl;
        // set as annotation because print error while changing in the middle of signal control
        return;
    }

    // A declaration-only file (e.g. read mid-write) has no root: treat it like
    // a missing file.
    TiXmlElement *root = doc.FirstChildElement();
    if (!root)
        return;

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        const char *idStr = e->Attribute("id");
        if (!idStr)   throw std::runtime_error ("Element should have 'id' attribute");
        int id = std::stoi(idStr);
        InputSignalControl singleSignalControl(id);

        const char *cycle = e->Attribute("cycle");
        const char *changedStr = e->Attribute("changed");

        if (!cycle)   throw std::runtime_error ("Element should have 'cycle' attribute");
        if (!changedStr)   throw std::runtime_error ("Element should have 'changed' attribute");

        singleSignalControl.SetCycle(std::atoi(cycle));
        bool changed = (std::strcmp(changedStr, "1") == 0 ||
                            strcasecmp(changedStr, "true") == 0);

        singleSignalControl.SetChanged(changed);

        std::vector<phase> phaseSeq;

        for (TiXmlElement *tPhase = e->FirstChildElement(); tPhase != NULL;
             tPhase = tPhase->NextSiblingElement())
        {
            const char *phaseId = tPhase->Attribute("id");
            const char *duration = tPhase->Attribute("duration");
            const char *turnList = tPhase->Attribute("turnList");
            const char *kind = tPhase->Attribute("kind");
            const char *phaseType = tPhase->Attribute("phaseType");

            
            if (!phaseId)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!duration)   throw std::runtime_error ("Element should have 'duration' attribute");
            if (!turnList)   throw std::runtime_error ("Element should have 'turnList' attribute");

            phase singlePhase(std::atoi(phaseId),
                              std::atoi(duration),
                              kind == nullptr ? "UNSPECIFIED" : kind,
                              phaseType == nullptr ? "VEHICLE" : phaseType);
            singlePhase.SetTurnList(turnList);

            phaseSeq.push_back(singlePhase);
        }
        singleSignalControl.SetPhaseList(phaseSeq);

        Captain::UnitIdentifier nodeIdentifier(id, Captain::UnitType::Node);
        SetSignalControlMap(nodeIdentifier, singleSignalControl);
    }

    doc.Clear();
};

bool SignalControlArr::UpdateSignalControlXML(int nodeId) const
{
    namespace fs = std::filesystem;

    const std::string xmlPath = NextSimIO::SignalControlXMLPath.string();

    TiXmlDocument doc;
    if (!doc.LoadFile(xmlPath.c_str())) {
        std::cerr << "[UpdateSignalControlXML] Failed to load XML: " << xmlPath << std::endl;
        return false;
    }

    TiXmlElement* rootElement = doc.FirstChildElement();
    if (!rootElement) {
        std::cerr << "[UpdateSignalControlXML] Root element not found." << std::endl;
        return false;
    }

    TiXmlElement* targetElement = nullptr;
    for (TiXmlElement* e = rootElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        const char* idAttr = e->Attribute("id");
        if (!idAttr) continue;

        int idValue = 0;
        try { idValue = std::stoi(idAttr); } catch (...) { continue; }

        if (idValue == nodeId) {
            targetElement = e;
            break;
        }
    }

    if (!targetElement) {
        std::cerr << "[UpdateSignalControlXML] Node id=" << nodeId << " not found in XML." << std::endl;
        return false;
    }

    // 0) set changed as false
    targetElement->SetAttribute("changed", "False");

    // Write a sibling temp file, then rename it over the original. The rename
    // replaces the original in one step, so a reader (or a failure here) never
    // sees the input file missing.
    const fs::path originalPath = fs::weakly_canonical(fs::path(xmlPath));
    const fs::path tmpPath = originalPath.string() + ".tmp";
    if (!doc.SaveFile(tmpPath.string().c_str())) {
        std::cerr << "[UpdateSignalControlXML] Save to temp failed: " << tmpPath << std::endl;
        return false;
    }

    std::error_code ec;
    fs::rename(tmpPath, originalPath, ec);
    if (ec) {
        std::cerr << "[UpdateSignalControlXML] Replace failed: " << ec.message() << std::endl;
        fs::remove(tmpPath, ec);
        return false;
    }

    return true;
}
} // namespace NextSimIO