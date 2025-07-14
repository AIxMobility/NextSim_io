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
        std::cout << "Loading failed (SignalControlArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();
    // int planId = atoi(root->Attribute("id"));

    std::vector<InputSignalControl> signalControlList;

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
        signalControlList.push_back(singleSignalControl);
    }
    SetSignalControls(signalControlList);

    doc.Clear();
};
} // namespace NextSimIO