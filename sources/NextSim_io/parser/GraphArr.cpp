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
                const char *type = e2->Attribute("type");
                const char *center = e2->Attribute("center");

                int nodeType;
                if (!strcmp(type, "normal")){
                    nodeType = 0;
                }
                else if (!strcmp(type, "intersection")){
                    nodeType = 1;
                }
                else if (!strcmp(type, "merging")){
                    nodeType = 2;
                }
                else if (!strcmp(type, "diverging")){
                    nodeType = 3;
                }
                else if (!strcmp(type, "terminal")){
                    nodeType = 4;
                }
                else if (!strcmp(type, "garage")){
                    nodeType = 5;
                }
                else{
                    throw std::runtime_error ("Invalid node type");
                }

                InputGraphVertex single_vertex(
                    atol(vertexid),
                    nodeType,
                    0.0,
                    0);
                
                double xcoord = 0.0;
                double ycoord = 0.0;
                if (center)
                {
                    std::istringstream iss(center);
                    std::string x, y;
                    if (std::getline(iss, x, ' ') && std::getline(iss, y))
                    {
                        xcoord = atof(x.c_str());
                        ycoord = atof(y.c_str());
                    }
                    else
                    {
                        throw std::runtime_error ("Invalid center format");
                    }
                }
                else
                {
                    const char *xcoordAttr = e2->Attribute("x_coord");
                    const char *ycoordAttr = e2->Attribute("y_coord");

                    if (!xcoordAttr || !ycoordAttr)
                        throw std::runtime_error ("Element should have 'x_coord' and 'y_coord' attributes");

                    xcoord = atof(xcoordAttr);
                    ycoord = atof(ycoordAttr);
                }

                VertexCoord single_coord(xcoord, ycoord);

                single_vertex.SetCoordinates({single_coord});

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

                    else if (val1 == "connection")
                    {
                        const char *fromLink = e3->Attribute("from_link");
                        const char *toLink = e3->Attribute("to_link");
                        const char *fromLane = e3->Attribute("from_lane");
                        const char *toLane = e3->Attribute("to_lane");
                        const char *arc_length = e3->Attribute("length");

                        if (!fromLink)   throw std::runtime_error ("Element should have 'from_link' attribute");
                        if (!toLink)   throw std::runtime_error ("Element should have 'to_link' attribute");
                        if (!fromLane)   throw std::runtime_error ("Element should have 'from_lane' attribute");
                        if (!toLane)   throw std::runtime_error ("Element should have 'to_lane' attribute");
                        if (!arc_length)   throw std::runtime_error ("Element should have 'length' attribute");

                        ConnectionInfo NewconnectionInfo(
                            atol(fromLink),
                            atol(toLink),
                            atol(fromLane),
                            atol(toLane),
                            atof(arc_length));
                        
                        single_vertex.pushConnectionInfo(NewconnectionInfo);
                    }
                }
                m_vertices.push_back(single_vertex);

                single_vertex.FreeLinks();
            }
        }
    }

    for (auto &vertex : m_vertices)
    {
        m_vertexInfo[vertex.GetId()] = vertex;

        if (vertex.GetType() == 4)
        {
            if (vertex.GetLinks()[0].GetType() == -1)
            {
                m_sourceTerminals.emplace_back(vertex.GetId());
            }
            else if (vertex.GetLinks()[0].GetType() == 1)
            {
                m_sinkTerminals.emplace_back(vertex.GetId());
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
                    const char *ArcId = e->Attribute("id");
                    const char *fromNode = e->Attribute("from_node");
                    const char *toNode = e->Attribute("to_node");
                    const char *numLane = e->Attribute("num_lane");
                    const char *arc_length = e->Attribute("length");

                    if (!ArcId)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!fromNode)   throw std::runtime_error ("Element should have 'from_node' attribute");
                    if (!toNode)   throw std::runtime_error ("Element should have 'to_node' attribute");
                    if (!numLane)   throw std::runtime_error ("Element should have 'num_lane' attribute");
                    if (!arc_length)   throw std::runtime_error ("Element should have 'length' attribute");

                    InputGraphArc demoArc(
                        static_cast<std::size_t>(atoll(ArcId)),
                        static_cast<std::size_t>(atoll(fromNode)),
                        static_cast<std::size_t>(atoll(toNode)),
                        static_cast<std::size_t>(atoll(numLane)),
                        static_cast<double>(atof(arc_length))
                    );
                    
                    demoArc.SetArcCost(ArcCost(0, atof(arc_length), 0, 0));

                    std::vector<int> availableLanes = {};
                    for (TiXmlElement* laneElem = e->FirstChildElement(); laneElem != nullptr;
                         laneElem = laneElem->NextSiblingElement())
                    {
                        bool isBlock = false;
                        for (TiXmlElement* segElem = laneElem->FirstChildElement(); segElem != nullptr;
                             segElem = segElem->NextSiblingElement())
                        {
                            std::string name = segElem->Value();
                            if (name == "segment")
                            {
                                const char *end_point = segElem->Attribute("end_point");
                                const char *block = segElem->Attribute("block");

                                if (strcmp(block, "True") == 0 && std::abs(atof(end_point) - atof(arc_length)) < 3)
                                    isBlock = true;
                            }
                            else continue;
                        }

                        if (!isBlock)
                        {
                            const char *laneId = laneElem->Attribute("id");
                            const char *laneAccessType = laneElem->Attribute("laneAccessType");

                            if (laneAccessType == nullptr) {
                                availableLanes.push_back(static_cast<int>(atol(laneId)));
                            }
                            else {
                                demoArc.PushPTLaneList(static_cast<int>(atol(laneId)));
                            }
                        }
                    }

                    demoArc.SetAvailableLanes(availableLanes);

                    m_arcs.push_back(demoArc);
                }
            }
        }
    }

    for (auto &arc : m_arcs)
    {
        m_arcInfo[arc.GetID()] = arc;
    }

    doc.Clear();
}; // ArcArr::ArcArr

Graph::Graph(ArcArr arcArr, VertexArr vertexArr)
{
    std::vector<InputGraphVertex> vertices = vertexArr.GetVertices();
    std::unordered_map<int, InputGraphArc> arcInfo = arcArr.GetArcInfo();

    m_arcToArc.clear();

    for (auto &vertex : vertices)
    {
        std::vector<ConnectionInfo> linkConnections = vertex.GetConnectionInfo();
        for (auto &conn : linkConnections)
        {
            int fromLink = conn.GetFromLink();
            int fromLane = conn.GetFromLane();
            int toLink = conn.GetToLink();
            int toLane = conn.GetToLane();

            InputGraphArc &fromLinkInfo = arcInfo.at(fromLink);
            InputGraphArc &toLinkInfo = arcInfo.at(toLink);
            std::vector<int> fromLinkAvailableLanes = fromLinkInfo.GetAvailableLanes();
            std::vector<int> toLinkAvailableLanes = toLinkInfo.GetAvailableLanes();

            if ((std::find(fromLinkAvailableLanes.begin(), fromLinkAvailableLanes.end(), fromLane) == fromLinkAvailableLanes.end())
                || (std::find(toLinkAvailableLanes.begin(), toLinkAvailableLanes.end(), toLane) == toLinkAvailableLanes.end()))
            {
                continue;
            }

            if(std::find(m_arcToArc[fromLink].begin(), m_arcToArc[fromLink].end(), toLink) == m_arcToArc[fromLink].end())
            {
                m_arcToArc[fromLink].emplace_back(toLink);
            }
        }
    }
}; // Graph::Graph

} // namespace NextSimIO