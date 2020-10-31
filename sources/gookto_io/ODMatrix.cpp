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
         elem = elem->NextSiblingElement("Demand"))
    {
        std::string elemName = elem->Value();

        // const char *attr;
        if (elemName == "Demand")
        {
            Demand single_demand(atoi(elem->Attribute("flow")), atoi(elem->Attribute("sink")), atoi(elem->Attribute("source")), 1);

            Demands.push_back(single_demand);
        }
        
    };
    std::cout << "Got Demand" << std::endl;
    doc.Clear();
}