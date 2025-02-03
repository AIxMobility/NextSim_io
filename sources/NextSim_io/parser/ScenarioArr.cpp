/**
 * NextSim Captain
 * @file : ScenarioArr.cpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

#include <iostream>
#include <sstream>
#include <string>

#include <NextSim_io/parser/ScenarioArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ScenarioArr::ScenarioArr()
{
    TiXmlDocument doc_OD;
    bool loadSuccess = doc_OD.LoadFile(NextSimIO::OdScenarioXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (ODScenario)" << std::endl;
        return;
    }

    TiXmlElement *root_OD = doc_OD.FirstChildElement();

    for (TiXmlElement *elem = root_OD->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "Scenario")
        {
            const char *id = elem->Attribute("id");
            const char *od_id = elem->Attribute("od_matrix_id");

            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");
            if (!od_id)
                throw std::runtime_error("Element should have 'od_matrix_id' attribute");
            

            m_odScenarios.emplace_back(std::make_pair(atoi(id), atoi(od_id)));
        }
    }
    doc_OD.Clear();


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
}
} // namespace NextSimIO