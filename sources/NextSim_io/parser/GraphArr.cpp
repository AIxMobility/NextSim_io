/**
 * NextSim Captain
 * @file GraphArr.cpp
 * @version 1.0
 * @author Dongheon Lee
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <NextSim_io/parser/GraphArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
VertexArr::VertexArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::NetworkXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (VertexArr)" << std::endl;
        return;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        std::string elemName2 = e->Value();

        if (elemName2 == "nodes")
        {
            for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL;
            e2 = e2->NextSiblingElement())
            {
                const char *vertexid = e2->Attribute("id");

                InputGraphVertex single_vertex(
                    atol(vertexid),
                    0.0,
                    0);

                for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                    e3 = e3->NextSiblingElement())
                {
                    std::string val1 = e3->Value();
                    if (val1 == "port")
                    {
                        int temp = -1;

                        const char *link_id = e3->Attribute("link_id");
                        const char *direction = e3->Attribute("direction");
                        const char *portType = e3->Attribute("type");

                        if (!link_id)   throw std::runtime_error ("Element should have 'link_id' attribute");
                        if (!direction)   throw std::runtime_error ("Element should have 'direction' attribute");
                        if (!portType)   throw std::runtime_error ("Element should have 'type' attribute");

                        if (!strcmp (portType, "in"))
                        {
                            temp = 1;
                        }

                        port single_link(
                            atol(link_id),
                            atoi(direction),
                            temp);

                        single_vertex.pushLink(single_link);
                    }
                }
                m_vertices.push_back(single_vertex);

                single_vertex.FreeLinks();
            }
        }
    }
    doc.Clear();
}; // VertexArr::VertexArr

ArcArr::ArcArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::NetworkXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (ArcArr)" << std::endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr;
         elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        if (elemName == "links"){
            for (TiXmlElement* e = elem->FirstChildElement(); e != nullptr;
                 e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "link")
                {
                    const char *vertexId = e->Attribute("id");
                    const char *fromNode = e->Attribute("from_node");
                    const char *toNode = e->Attribute("to_node");
                    const char *arc_length = e->Attribute("length");

                    if (!vertexId)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!fromNode)   throw std::runtime_error ("Element should have 'from_node' attribute");
                    if (!toNode)   throw std::runtime_error ("Element should have 'to_node' attribute");
                    if (!arc_length)   throw std::runtime_error ("Element should have 'length' attribute");

                    InputGraphArc demoArc(
                        static_cast<std::size_t>(atoll(vertexId)),
                        static_cast<std::size_t>(atoll(fromNode)),
                        static_cast<std::size_t>(atoll(toNode)));
                    
                    demoArc.PushArcCost(ArcCost(0, atof(arc_length), 0, 0));

                    m_arcs.push_back(demoArc);
                }
            }
        }
    }
    doc.Clear();
}; // ArcArr::ArcArr

} // namespace NextSimIO