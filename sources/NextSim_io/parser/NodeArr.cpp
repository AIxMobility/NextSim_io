/**
 * NextSim Captain
 * @file : NodeArr.cpp
 * @version : 1.0
 * @author : Jeyun Kim
 */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <NextSim_io/parser/NodeArr.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
NodeArr::NodeArr()
{
    TiXmlDocument doc;
    bool loadSuccess = doc.LoadFile(NextSimIO::NetworkXMLPath.string().c_str());

    if (!loadSuccess)
    {
        std::cout << "Loading failed (NodeArr-Network.xml)" << std::endl;
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
                const char *nodeId = e2->Attribute("id");
                const char *nodeType = e2->Attribute("type");
                const char *numConnection = e2->Attribute("num_connection");
                const char *numPort = e2->Attribute("num_port");
                const char *v2x = e2->Attribute("v2x");

                if (!nodeId)   throw std::runtime_error ("Element should have 'id' attribute");
                if (!nodeType)   throw std::runtime_error ("Element should have 'type' attribute");
                if (!numConnection)   throw std::runtime_error ("Element should have 'num_connection' attribute");
                if (!numPort)   throw std::runtime_error ("Element should have 'num_port' attribute");
                if (!v2x)   v2x = "off";

                const bool v2xEnabled = (strcmp(v2x, "on") == 0);

                auto parsePort = [](TiXmlElement *element, InputNode& targetNode) {
                    int temp = -1;

                    const char *link_id = element->Attribute("link_id");
                    const char *direction = element->Attribute("direction");
                    const char *portType = element->Attribute("type");

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

                    targetNode.pushLink(single_link);
                };

                auto parseConnection = [](TiXmlElement *element, InputNode& targetNode) {
                    const char *connectionId = element->Attribute("id");
                    const char *from_link = element->Attribute("from_link");
                    const char *from_lane = element->Attribute("from_lane");
                    const char *to_link = element->Attribute("to_link");
                    const char *to_lane = element->Attribute("to_lane");
                    const char *priority = element->Attribute("priority");
                    const char *turning = element->Attribute("turning");
                    const char *length = element->Attribute("length");
                    const char *width = element->Attribute("width");
                    const char *ffspeed = element->Attribute("ff_spd");

                    if (!connectionId)   throw std::runtime_error ("Element should have 'id' attribute");
                    if (!from_link)   throw std::runtime_error ("Element should have 'from_link' attribute");
                    if (!from_lane)   throw std::runtime_error ("Element should have 'from_lane' attribute");
                    if (!to_link)   throw std::runtime_error ("Element should have 'to_link' attribute");
                    if (!to_lane)   throw std::runtime_error ("Element should have 'to_lane' attribute");
                    if (!turning)   throw std::runtime_error ("Element should have 'turning' attribute");
                    if (!priority)   priority = "1";
                    if (!length)   throw std::runtime_error ("Element should have 'length' attribute");
                    if (!width)   width = "3.5";
                    if (!ffspeed)   throw std::runtime_error ("Element should have 'ff_spd' attribute");

                    connection single_connection(
                        atol(connectionId),
                        atol(from_link),
                        atol(from_lane),
                        atol(to_link),
                        atol(to_lane),
                        turning,
                        atof(priority),
                        atof(length),
                        atof(width),
                        atof(ffspeed));

                    targetNode.pushConnection(single_connection);
                };

                auto parseNodeChildren = [&](TiXmlElement *nodeElement, InputNode& targetNode, bool includeConnections) {
                    for (TiXmlElement *e3 = nodeElement->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        if (val1 == "port")
                        {
                            parsePort(e3, targetNode);
                        }
                        else if (includeConnections && val1 == "connection")
                        {
                            parseConnection(e3, targetNode);
                        }
                    }
                };

                if (!strcmp (nodeType, "normal"))
                {
                    InputNode single_node(
                        0,
                        atol(nodeId),
                        atoi(numConnection),
                        atoi(numPort),
                        v2xEnabled);

                    parseNodeChildren(e2, single_node, true);
                    m_nodes.push_back(single_node);
                    m_normalNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                    single_node.FreePhaseTable();
                }

                else if (!strcmp (nodeType, "intersection"))
                {
                    InputNode single_node(
                        1,
                        atol(nodeId),
                        atoi(numConnection),
                        atoi(numPort),
                        v2xEnabled);

                    parseNodeChildren(e2, single_node, true);
                    m_nodes.push_back(single_node);
                    m_intersectionNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                    single_node.FreePhaseTable();
                }
                
                else if (!strcmp (nodeType, "merging"))
                {
                    InputNode single_node(
                        2, 
                        atol(nodeId),
                        atoi(numConnection),
                        atoi(numPort),
                        v2xEnabled);

                    parseNodeChildren(e2, single_node, true);
                    m_nodes.push_back(single_node);
                    m_intersectionNodes.push_back(single_node);
                    m_mergingNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                }

                else if (!strcmp (nodeType, "diverging"))
                {
                    InputNode single_node(
                        3,
                        atol(nodeId),
                        atoi(numConnection),
                        atoi(numPort),
                        v2xEnabled);

                    parseNodeChildren(e2, single_node, true);
                    m_nodes.push_back(single_node);
                    m_intersectionNodes.push_back(single_node);
                    m_divergingNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                }

                else if (!strcmp (nodeType, "terminal"))
                {
                    InputNode single_node(
                        4, 
                        atol(nodeId), 
                        -1,
                        atoi(numPort),
                        v2xEnabled);

                    parseNodeChildren(e2, single_node, false);
                    m_nodes.push_back(single_node);
                    m_terminalNodes.push_back(single_node);
                    
                    single_node.FreeConnectedLinks();
                }

                else if (!strcmp (nodeType, "garage"))
                {
                    InputNode single_node(
                        5, 
                        atol(nodeId), 
                        -1,
                        atoi(numPort),
                        v2xEnabled);

                    parseNodeChildren(e2, single_node, true);
                    m_nodes.push_back(single_node);
                    m_garageNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                }
            }
        }
    }
    doc.Clear();
};

void NodeArr::ShowArr()
{
    if (m_nodes.size() == 0)
    {
        std::cout << "ITS EMPTY" << std::endl;
    }

    for (size_t i = 0; i < m_nodes.size(); i++)
    {
        std::cout << m_nodes[i].GetId() << " " << m_nodes[i].GetNumConn() << " "
                  << m_nodes[i].GetNumLink() << std::endl;

        // Example:: Getting the first connection ID of each intersection
        std::cout << "connID :" << m_nodes[i].GetConnections()[0].GetConnId()
                  << std::endl;
    }
}
} // namespace NextSimIO