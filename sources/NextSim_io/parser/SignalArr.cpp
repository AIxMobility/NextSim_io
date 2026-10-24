/**
 * NextSim Captain
 * @file : SignalArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <NextSim_io/parser/SignalArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
SignalArr::SignalArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::SignalXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (SignalArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();
    // int planId = atoi(root->Attribute("id"));

    for (TiXmlElement *e = root ? root->FirstChildElement() : NULL; e != NULL;
         e = e->NextSiblingElement())
    {
        const char *signalId = e->Attribute("id");
        if (!signalId)
            throw std::runtime_error("signal.xml: a <" + std::string(e->Value()) + "> has no id attribute");
        int id = std::stoi(signalId);
        const std::string where = "signal.xml: signal " + std::string(signalId) + ": ";
        
        InputSignal singleSignal(id);

        TiXmlElement *tTurnList = e->FirstChildElement("turnList");
        if (!tTurnList)
            throw std::runtime_error(where + "has no <turnList>");
        for (TiXmlElement *tTurn = tTurnList->FirstChildElement(); tTurn != NULL;
             tTurn = tTurn->NextSiblingElement())
        {
            const char *turnId = tTurn->Attribute("id");
            const char *turning = tTurn->Attribute("turning");
            const char *type = tTurn->Attribute("type");
            const char *connList = tTurn->Attribute("connList");
            
            if (!turnId)   throw std::runtime_error (where + "a <turn> has no 'id' attribute");
            if (!turning)   throw std::runtime_error (where + "a <turn> has no 'turning' attribute");
            if (!type)   throw std::runtime_error (where + "a <turn> has no 'type' attribute");
            if (!connList)   throw std::runtime_error (where + "a <turn> has no 'connList' attribute");

            turn singleTurn(std::atoi(turnId), std::atoi(turning), type);
            singleTurn.SetConnList(connList);

            singleSignal.PushTurn(singleTurn);
        }

        TiXmlElement *tPlanList = e->FirstChildElement("planList");
        if (!tPlanList)
            throw std::runtime_error(where + "has no <planList>");
        for (TiXmlElement *tPlan = tPlanList->FirstChildElement(); tPlan != NULL;
             tPlan = tPlan->NextSiblingElement())
        {
            const char *planId = tPlan->Attribute("id");
            const char *cycle = tPlan->Attribute("cycle");
            const char *offset = tPlan->Attribute("offset");
            
            if (!planId)   throw std::runtime_error (where + "a <plan> has no 'id' attribute");
            if (!cycle)   throw std::runtime_error (where + "a <plan> has no 'cycle' attribute");
            if (!offset)   throw std::runtime_error (where + "a <plan> has no 'offset' attribute");

            std::vector<phase> phaseSeq;
            for(TiXmlElement *tPhase = tPlan->FirstChildElement(); tPhase != NULL;
                tPhase = tPhase->NextSiblingElement())
            {
                const char *phaseId = tPhase->Attribute("id");
                const char *duration = tPhase->Attribute("duration");
                const char *turnList = tPhase->Attribute("turnList");
                const char *kind = tPhase->Attribute("kind");
                const char *phaseType = tPhase->Attribute("phaseType");

                
                if (!phaseId)   throw std::runtime_error (where + "a <phase> has no 'id' attribute");
                if (!duration)   throw std::runtime_error (where + "a <phase> has no 'duration' attribute");
                if (!turnList)   throw std::runtime_error (where + "a <phase> has no 'turnList' attribute");

                phase singlePhase(std::atoi(phaseId),
                                  std::atoi(duration),
                                  kind == nullptr ? "UNSPECIFIED" : kind,
                                  phaseType == nullptr ? "VEHICLE" : phaseType);
                singlePhase.SetTurnList(turnList);

                phaseSeq.push_back(singlePhase);
            }

            plan singlePlan(std::atoi(planId), std::atoi(cycle), std::atoi(offset), phaseSeq);

            singleSignal.PushPlan(singlePlan);
        }

        m_signals.push_back(singleSignal);
    }
    doc.Clear();

    TiXmlDocument doc_signal;
    loadSuccess = doc_signal.LoadFile(NextSimIO::SignalTODXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (SignalTOD)" << std::endl;
        return;
    }

    TiXmlElement *root_signal = doc_signal.FirstChildElement();

    for (TiXmlElement *elem = root_signal ? root_signal->FirstChildElement() : NULL; elem != NULL;
         elem = elem->NextSiblingElement())
    {
        const char *todNodeId = elem->Attribute("id");
        if (!todNodeId)
            throw std::runtime_error("signalTOD.xml: a <node> has no id attribute");
        int nodeId = atoi(todNodeId);

        std::vector<table> todTable;
        for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
             e = e->NextSiblingElement())
        {
            const char *planId = e->Attribute("id");
            const char *startTime = e->Attribute("startTime");
            const char *endTime = e->Attribute("endTime");

            if (!planId)
                throw std::runtime_error("signalTOD.xml: node " + std::string(todNodeId) + ": a <plan> has no 'id' attribute");
            if (!startTime)
                throw std::runtime_error("signalTOD.xml: node " + std::string(todNodeId) + ": a <plan> has no 'startTime' attribute");
            if (!endTime)
                throw std::runtime_error("signalTOD.xml: node " + std::string(todNodeId) + ": a <plan> has no 'endTime' attribute");

            table singleTable(atoi(planId), startTime, endTime);

            todTable.push_back(singleTable);
        }

        InputTOD singleTOD(nodeId, todTable);

        m_signalTODs.push_back(singleTOD);
    }

    doc_signal.Clear();
};
} // namespace NextSimIO