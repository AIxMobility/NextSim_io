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
        std::cout << "Error description: " << doc.ErrorDesc() << std::endl;
        std::cout << "Error ID: " << doc.ErrorId() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();
    // int planId = atoi(root->Attribute("id"));

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        int id = std::stoi(e->Attribute("id"));
        
        InputSignal singleSignal(id);

        TiXmlElement *tTurnList = e->FirstChildElement("turn_list");
        for (TiXmlElement *tTurn = tTurnList->FirstChildElement(); tTurn != NULL;
             tTurn = tTurn->NextSiblingElement())
        {
            const char *turnId = tTurn->Attribute("id");
            const char *turning = tTurn->Attribute("turning");
            const char *type = tTurn->Attribute("type");
            const char *connList = tTurn->Attribute("conn_list");
            
            if (!turnId)   throw std::runtime_error ("Element should have 'id' attribute");
            if (!turning)   throw std::runtime_error ("Element should have 'turning' attribute");
            if (!type)   throw std::runtime_error ("Element should have 'type' attribute");
            if (!connList)   throw std::runtime_error ("Element should have 'conn_list' attribute");

            turn singleTurn(std::atoi(turnId), std::atoi(turning), type);
            singleTurn.SetConnList(connList);

            singleSignal.PushTurn(singleTurn);
        }

        TiXmlElement *tPlanList = e->FirstChildElement("plan_list");
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
                const char *duration = tPhase->Attribute("duration");
                const char *turnList = tPhase->Attribute("turn_list");

                
                if (!phaseId)   throw std::runtime_error ("Element should have 'id' attribute");
                if (!duration)   throw std::runtime_error ("Element should have 'duration' attribute");
                if (!turnList)   throw std::runtime_error ("Element should have 'turn_list' attribute");

                phase singlePhase(std::atoi(phaseId), std::atoi(duration));
                singlePhase.SetTurnList(turnList);

                phaseSeq.push_back(singlePhase);
            }

            plan singlePlan(std::atoi(planId), std::atoi(cycle), std::atoi(offset), phaseSeq);

            singleSignal.PushPlan(singlePlan);
        }

        m_signals.push_back(singleSignal);
    }
    doc.Clear();
};
} // namespace NextSimIO