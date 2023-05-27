#include <iostream>
#include <sstream>
#include <string>

#include <gookto_io/Demand.hpp>
#include <gookto_io/DemandInfo.hpp>
#include <gookto_io/ODMatrix.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

ODMatrix::ODMatrix()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::OdMatrixXMLPath.string().c_str());
    // std::cout << "Loading ODMatrix" << std::endl;

    if (!doc.LoadFile(STSIO::OdMatrixXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (ODMatrix)" << std::endl;
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "od_matrix")
        {
            const char *id = elem->Attribute("id");
            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");

            std::string type;
            std::vector<Demand> Demands;

            for (TiXmlElement *child = elem->FirstChildElement(); child != NULL;
                 child = child->NextSiblingElement())
            {
                std::string childName = child->Value();

                if (childName == "nv_od_matrix")
                {
                    type = "nv";
                    for (TiXmlElement *demand = child->FirstChildElement();
                         demand != NULL; demand = demand->NextSiblingElement())
                    {
                        std::string demandName = demand->Value();

                        if (demandName == "demand")
                        {
                            const char *flow = demand->Attribute("flow");
                            const char *sink = demand->Attribute("sink");
                            const char *source = demand->Attribute("source");
                            const char *dist = demand->Attribute("dist");

                            if (!flow)
                                throw std::runtime_error(
                                    "Element should have 'flow' attribute");
                            if (!sink)
                                throw std::runtime_error(
                                    "Element should have 'sink' attribute");
                            if (!source)
                                throw std::runtime_error(
                                    "Element should have 'source' attribute");
                            if (!dist)
                                dist = "Exponential";

                            if (!strcmp(dist, "Normal")) dist = "0";
                            else if (!strcmp(dist, "Exponential")) dist = "1";
                            else dist = "2"; 

                            Demand single_demand(
                                atoi(flow), 
                                atoi(sink),
                                atoi(source), 
                                atoi(dist));

                            Demands.push_back(single_demand);
                        }
                    }
                }
            }

            DemandInfo demandInfo(
                atoi(id), 
                type, 
                Demands);

            ODmatrix.push_back(demandInfo);
        }
    };
    doc.Clear();
}