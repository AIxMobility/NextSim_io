/**
 * NextSim Captain
 * @file : ODMatrixArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <iostream>
#include <sstream>
#include <string>

#include <NextSim_io/parser/ODMatrixArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
ODMatrixArr::ODMatrixArr()
    : ODMatrixArr(NextSimIO::OdMatrixXMLPath)
{
}

ODMatrixArr::ODMatrixArr(const std::filesystem::path& odMatrixPath)
{
    parseODMatrix(odMatrixPath);
}

void ODMatrixArr::parseODMatrix(const std::filesystem::path& odMatrixPath)
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(odMatrixPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (ODMatrix)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "odMatrix")
        {
            const char *id = elem->Attribute("id");
            if (!id)
                throw std::runtime_error("Element should have 'id' attribute");

            std::vector<InputFlow> odmatrix;

            auto distToInt = [](const char* dist) {
                if (!dist) return 1;
                const std::string distStr = dist;
                if (distStr == "Normal") return 0;
                if (distStr == "Exponential") return 1;
                return 2;
            };

            auto isV2XActive = [](const char* v2x) {
                if (!v2x) return false;
                const std::string v2xStr = v2x;
                return v2xStr == "on" || v2xStr == "true" || v2xStr == "1";
            };

            auto readDemandBlock = [&](TiXmlElement* child, int type, bool defaultV2XActive) {
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
                        const char *v2x = demand->Attribute("v2x");

                        if (!flow)
                            throw std::runtime_error(
                                "Element should have 'flow' attribute");
                        if (!sink)
                            throw std::runtime_error(
                                "Element should have 'sink' attribute");
                        if (!source)
                            throw std::runtime_error(
                                "Element should have 'source' attribute");

                        InputFlow single_flow(
                            type,
                            atoi(flow),
                            atoi(sink),
                            atoi(source),
                            distToInt(dist),
                            v2x ? isV2XActive(v2x) : defaultV2XActive);

                        odmatrix.push_back(single_flow);
                    }
                }
            };

            for (TiXmlElement *child = elem->FirstChildElement(); child != NULL;
                 child = child->NextSiblingElement())
            {
                std::string childName = child->Value();

                if (childName == "nvodMatrix")
                {
                    readDemandBlock(child, 0, false);
                }
                else if (childName == "avodMatrix")
                {
                    readDemandBlock(child, 1, false);
                }
                else if (childName == "trodMatrix")
                {
                    readDemandBlock(child, 2, false);
                }
            }

            InputODMatrix InputODMatrix(
                atoi(id), 
                odmatrix);

            m_odMatrix.push_back(InputODMatrix);
        }
    };
    doc.Clear();
}
} // namespace NextSimIO
