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
    bool loadSuccess = doc.LoadFile(NextSimIO::SignalNewXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (SignalArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();
    // int planId = atoi(root->Attribute("id"));

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        int id = std::stoi(e->Attribute("id"));
        
        InputSignal singleSignal(id);

        TiXmlElement *tTurnList = e->FirstChildElement("turnList");
        for (TiXmlElement *tTurn = tTurnList->FirstChildElement(); tTurn != NULL;
             tTurn = tTurn->NextSiblingElement())
        {
            const char *turnId = tTurn->Attribute("id");
            const char *turning = tTurn->Attribute("turning");
            const char *type = tTurn->Attribute("type");
            const char *connList = tTurn->Attribute("connList");
            
            if (!turnId)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!turning)   throw std::runtime_error ("Element should have 'turning' attribute");
            if (!type)   throw std::runtime_error ("Element should have 'type' attribute");
            if (!connList)   throw std::runtime_error ("Element should have 'connList' attribute");

            turn singleTurn(std::atoi(turnId), std::atoi(turning), type);
            singleTurn.SetConnList(connList);

            singleSignal.PushTurn(singleTurn);
        }

        TiXmlElement *tPlanList = e->FirstChildElement("planList");
        for (TiXmlElement *tPlan = tPlanList->FirstChildElement(); tPlan != NULL;
             tPlan = tPlan->NextSiblingElement())
        {
            const char *planId = tPlan->Attribute("id");
            const char *cycle = tPlan->Attribute("cycle");
            const char *offset = tPlan->Attribute("offset");
            
            if (!planId)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!cycle)   throw std::runtime_error ("Element should have 'cycle' attribute");
            if (!offset)   throw std::runtime_error ("Element should have 'offset' attribute");

            std::vector<phase> phaseSeq;
            for(TiXmlElement *tPhase = tPlan->FirstChildElement(); tPhase != NULL;
                tPhase = tPhase->NextSiblingElement())
            {
                const char *phaseId = tPhase->Attribute("id");
                const char *greenTime = tPhase->Attribute("greenTime");
                const char *yellowTime = tPhase->Attribute("yellowTime");
                const char *turnList = tPhase->Attribute("turnList");

                
                if (!phaseId)   throw std::runtime_error ("Element should have 'id' attribute");
                if (!greenTime)   throw std::runtime_error ("Element should have 'greenTime' attribute");
                if (!yellowTime)   throw std::runtime_error ("Element should have 'yellowTime' attribute");
                if (!turnList)   throw std::runtime_error ("Element should have 'turnList' attribute");

                phase singlePhase(std::atoi(phaseId), std::atoi(greenTime), std::atoi(yellowTime));
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

    for (TiXmlElement *elem = root_signal->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        int nodeId = atoi(elem->Attribute("id"));

        std::vector<table> todTable;
        for (TiXmlElement *e = elem->FirstChildElement(); e != NULL;
             e = e->NextSiblingElement())
        {
            const char *planId = e->Attribute("planId");
            const char *startTime = e->Attribute("startTime");
            const char *endTime = e->Attribute("endTime");

            if (!planId)
                throw std::runtime_error("Element should have 'planId' attribute");
            if (!startTime)
                throw std::runtime_error("Element should have 'startTime' attribute");
            if (!endTime)
                throw std::runtime_error("Element should have 'endTime' attribute");

            table singleTable(atoi(planId), atoi(startTime), atoi(endTime));

            todTable.push_back(singleTable);
        }

        InputTOD singleTOD(nodeId, todTable);

        m_signalTODs.push_back(singleTOD);
    }

    doc_signal.Clear();
};
} // namespace NextSimIO