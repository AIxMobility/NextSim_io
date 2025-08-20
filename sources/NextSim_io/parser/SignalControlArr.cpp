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

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        int id = std::stoi(e->Attribute("id"));
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

            
            if (!phaseId)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!duration)   throw std::runtime_error ("Element should have 'duration' attribute");
            if (!turnList)   throw std::runtime_error ("Element should have 'turnList' attribute");

            phase singlePhase(std::atoi(phaseId), std::atoi(duration));
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

    const fs::path originalPath = fs::weakly_canonical(fs::path(xmlPath));
    const fs::path bakPath      = originalPath.string() + ".bak";

    // 1) save tmp file
    const fs::path tmpPath = originalPath.string() + ".tmp";
    if (!doc.SaveFile(tmpPath.string().c_str())) {
        std::cerr << "[UpdateSignalControlXML] Save to temp failed: " << tmpPath << std::endl;
        return false;
    }

    // 2) remove original file
    std::error_code ec;
    fs::remove(originalPath, ec);

    // 3) save backup file for safety
    fs::rename(tmpPath, bakPath, ec);
    if (ec) {
        // std::cerr << "[UpdateSignalControlXML] Rename tmp->bak failed: " << ec.message() << std::endl;
        return false;
    }

    // 4) rename backup file to original
    fs::rename(bakPath, originalPath, ec);
    if (ec) {
        // std::cerr << "[UpdateSignalControlXML] Rename bak->original failed: " << ec.message() << std::endl;
        return false;
    }

    // 5) re-open and verify the changes (debugging)
    // set as annotation because of increased computation time

    // TiXmlDocument verifyDoc;
    // if (!verifyDoc.LoadFile(originalPath.string().c_str())) {
    //     // std::cerr << "[UpdateSignalControlXML] Re-open failed after save." << std::endl;
    //     return false;
    // }

    // TiXmlElement* verifyRoot = verifyDoc.FirstChildElement();
    // TiXmlElement* verifyElem = nullptr;
    // for (TiXmlElement* e = verifyRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
    //     const char* idAttr = e->Attribute("id");
    //     if (!idAttr) continue;
    //     int idValue = 0; try { idValue = std::stoi(idAttr); } catch (...) { continue; }
    //     if (idValue == nodeId) { verifyElem = e; break; }
    // }
    // if (!verifyElem) return false;

    // const char* changedAttr = verifyElem->Attribute("changed");
    // if (!changedAttr) return false;

    // std::string changedStr(changedAttr);
    // std::transform(changedStr.begin(), changedStr.end(), changedStr.begin(),
    //                [](unsigned char c){ return std::tolower(c); });

    // if (changedStr != "false") {
    //     // std::cerr << "[UpdateSignalControlXML] Verify failed: changed=" << changedAttr << std::endl;//
    //     return false;
    // }

    return true;
}
} // namespace NextSimIO