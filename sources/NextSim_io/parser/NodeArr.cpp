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

                if (!strcmp (nodeType, "normal"))
                {

                    // create single InputNode instance here
                    InputNode single_node(
                        0, 
                        atol(nodeId), 
                        atoi(numConnection),
                        atoi(numPort),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // InputNode
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

                            single_node.pushLink(single_link);
                        }
                        else if (val1 == "connection")
                        {
                            const char *connectionId = e3->Attribute("id");
                            const char *from_link = e3->Attribute("from_link");
                            const char *from_lane = e3->Attribute("from_lane");
                            const char *to_link = e3->Attribute("to_link");
                            const char *to_lane = e3->Attribute("to_lane");
                            const char *priority = e3->Attribute("priority");
                            const char *turning = e3->Attribute("turning");
                            const char *length = e3->Attribute("length");
                            const char *width = e3->Attribute("width");
                            const char *ffspeed = e3->Attribute("ff_spd");

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

                            single_node.pushConnection(single_connection);
                        }
                    }
                    m_nodes.push_back(single_node);
                    m_normalNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                    single_node.FreePhaseTable();
                }

                else if (!strcmp (nodeType, "intersection"))
                {
                    // create single InputNode instance here
                    InputNode single_node(
                        1,
                        atol(nodeId),
                        atoi(numConnection),
                        atoi(numPort),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // InputNode
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
                            single_node.pushLink(single_link);
                        }
                        else if (val1 == "connection")
                        {
                            const char *connectionId = e3->Attribute("id");
                            const char *from_link = e3->Attribute("from_link");
                            const char *from_lane = e3->Attribute("from_lane");
                            const char *to_link = e3->Attribute("to_link");
                            const char *to_lane = e3->Attribute("to_lane");
                            const char *priority = e3->Attribute("priority");
                            const char *turning = e3->Attribute("turning");
                            const char *length = e3->Attribute("length");
                            const char *width = e3->Attribute("width");
                            const char *ffspeed = e3->Attribute("ff_spd");

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
                                
                            single_node.pushConnection(single_connection);
                        }
                    }
                    m_nodes.push_back(single_node);
                    m_intersectionNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                    single_node.FreePhaseTable();
                }
                
                else if (!strcmp (nodeType, "merging"))
                {
                    // create single InputNode instance here
                    InputNode single_node(
                        2, 
                        atol(nodeId),
                        atoi(numConnection),
                        atoi(numPort),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // InputNode
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
                            single_node.pushLink(single_link);
                        }
                        else if (val1 == "connection")
                        {
                            const char *connectionId = e3->Attribute("id");
                            const char *from_link = e3->Attribute("from_link");
                            const char *from_lane = e3->Attribute("from_lane");
                            const char *to_link = e3->Attribute("to_link");
                            const char *to_lane = e3->Attribute("to_lane");
                            const char *priority = e3->Attribute("priority");
                            const char *turning = e3->Attribute("turning");
                            const char *length = e3->Attribute("length");
                            const char *width = e3->Attribute("width");
                            const char *ffspeed = e3->Attribute("ff_spd");

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
                                
                            single_node.pushConnection(single_connection);
                        }
                    }
                    m_nodes.push_back(single_node);
                    m_intersectionNodes.push_back(single_node);
                    m_mergingNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                    single_node.FreePhaseTable();
                }

                else if (!strcmp (nodeType, "diverging"))
                {
                    // create single InputNode instance here
                    InputNode single_node(
                        3,
                        atol(nodeId),
                        atoi(numConnection),
                        atoi(numPort),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // InputNode
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
                            single_node.pushLink(single_link);
                        }
                        else if (val1 == "connection")
                        {
                            const char *connectionId = e3->Attribute("id");
                            const char *from_link = e3->Attribute("from_link");
                            const char *from_lane = e3->Attribute("from_lane");
                            const char *to_link = e3->Attribute("to_link");
                            const char *to_lane = e3->Attribute("to_lane");
                            const char *priority = e3->Attribute("priority");
                            const char *turning = e3->Attribute("turning");
                            const char *length = e3->Attribute("length");
                            const char *width = e3->Attribute("width");
                            const char *ffspeed = e3->Attribute("ff_spd");

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
                                
                            single_node.pushConnection(single_connection);
                        }
                    }
                    m_nodes.push_back(single_node);
                    m_intersectionNodes.push_back(single_node);
                    m_divergingNodes.push_back(single_node);

                    single_node.FreeConnectedLinks();
                    single_node.FreeConnectedTable();
                    single_node.FreePhaseTable();
                }

                else if (!strcmp (nodeType, "terminal"))
                {
                    // create single InputNode instance here
                    InputNode single_node(
                        4, 
                        atol(nodeId), 
                        -1,
                        atoi(numPort),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for terminal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // InputNode
                            int temp = -1;

                            const char *link_id = e3->Attribute("link_id");
                            const char *direction = e3->Attribute("direction");
                            const char *portType = e3->Attribute("type");

                            if (!link_id)   throw std::runtime_error ("Element should have 'link_id' attribute");
                            if (!direction)   throw std::runtime_error ("Element should have 'direction' attribute");
                            if (!portType)   throw std::runtime_error ("Element should have 'type' attribute");

                            if (!strcmp(portType, "in"))
                            {
                                temp = 1;
                            }
                            port single_link(
                                atol(link_id),
                                atoi(direction),
                                temp);
                            single_node.pushLink(single_link);
                        }
                    }
                    m_nodes.push_back(single_node);
                    m_terminalNodes.push_back(single_node);
                    
                    single_node.FreeConnectedLinks();
                }

                else if (!strcmp (nodeType, "garage"))
                {
                    // create single InputNode instance here
                    InputNode single_node(
                        5, 
                        atol(nodeId), 
                        -1,
                        atoi(numPort),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // InputNode
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
                            single_node.pushLink(single_link);
                        }
                        else if (val1 == "connection")
                        {
                            const char *connectionId = e3->Attribute("id");
                            const char *from_link = e3->Attribute("from_link");
                            const char *from_lane = e3->Attribute("from_lane");
                            const char *to_link = e3->Attribute("to_link");
                            const char *to_lane = e3->Attribute("to_lane");
                            const char *priority = e3->Attribute("priority");
                            const char *turning = e3->Attribute("turning");
                            const char *length = e3->Attribute("length");
                            const char *width = e3->Attribute("width");
                            const char *ffspeed = e3->Attribute("ff_spd");

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
                                
                            single_node.pushConnection(single_connection);
                        }
                    }
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