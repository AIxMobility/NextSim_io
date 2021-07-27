#include <iostream>
#include <sstream>
#include <string>

#include <gookto_io/ODMatrix.hpp>
#include <gookto_io/Demand.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

ODMatrix::ODMatrix()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::OdMatrixXMLPath.string().c_str());
    std::cout << "Loading ODMatrix" << std::endl;

    if (!doc.LoadFile("./network_xml/odmatrix.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "Demand")
        {
            const char *flow = elem->Attribute("flow");
            const char *sink = elem->Attribute("sink");
            const char *source = elem->Attribute("source");
            const char *dist = elem->Attribute("dist");

            if (!flow)   throw std::runtime_error ("Element should have 'flow' attribute");
            if (!sink)   throw std::runtime_error ("Element should have 'sink' attribute");
            if (!source)   throw std::runtime_error ("Element should have 'source' attribute");
            if (!dist)   dist = "Exponential";

            if (!strcmp (dist, "Normal"))   dist = "0";
            else if (!strcmp (dist, "Exponential")) dist = "1";
            else dist = "2";

            Demand single_demand(
                atoi(flow),
                atoi(sink),
                atoi(source),
                atoi(dist));

            Demands.push_back(single_demand);
        }
        
    };
    doc.Clear();
}