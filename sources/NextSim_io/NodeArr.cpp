#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <NextSim_io/IntersectionNode.hpp>
#include <NextSim_io/NodeArr.hpp>

#include <NextSim_io/intersection/connection.hpp>
#include <NextSim_io/intersection/intersectionPhase.hpp>
#include <NextSim_io/intersection/port.hpp>

#include <NextSim_io/tinyapi/tinystr.h>
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/FilePath.hpp>

namespace NextSimIO
{
NodeArr::NodeArr()
{
    TiXmlDocument doc;

    doc.LoadFile(NextSimIO::NetworkXMLPath.string().c_str());

    if (!doc.LoadFile(NextSimIO::NetworkXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (NodeArr-Network.xml)" << std::endl;
        // std::cerr << doc.ErrorDesc() << std::endl;
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
                const char *num_connection = e2->Attribute("num_connection");
                const char *num_port = e2->Attribute("num_port");
                const char *v2x = e2->Attribute("v2x");

                if (!nodeId)   throw std::runtime_error ("Element should have 'id' attribute");
                if (!nodeType)   throw std::runtime_error ("Element should have 'type' attribute");
                // if (!num_connection)   throw std::runtime_error ("Element should have 'num_connection' attribute");
                if (!num_port)   throw std::runtime_error ("Element should have 'num_port' attribute");
                if (!v2x)   v2x = "off";

                
                if (!strcmp (nodeType, "normal"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        0, 
                        atol(nodeId), 
                        -1,
                        atoi(num_port),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
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
                    Nodes.push_back(single_node);
                    NormalNodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                    single_node.freeConnectedTable();
                    single_node.freePhaseTable();
                }

                else if (!strcmp (nodeType, "intersection"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        1,
                        atol(nodeId),
                        atoi(num_connection),
                        atoi(num_port),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
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
                    Nodes.push_back(single_node);
                    IntersectionNodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                    single_node.freeConnectedTable();
                    single_node.freePhaseTable();
                }
                
                else if (!strcmp (nodeType, "merging"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        2, 
                        atol(nodeId),
                        atoi(num_connection),
                        atoi(num_port),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
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
                    Nodes.push_back(single_node);
                    IntersectionNodes.push_back(single_node);
                    MergingNodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                    single_node.freeConnectedTable();
                    single_node.freePhaseTable();
                }

                else if (!strcmp (nodeType, "diverging"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        3,
                        atol(nodeId),
                        atoi(num_connection),
                        atoi(num_port),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
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
                    Nodes.push_back(single_node);
                    IntersectionNodes.push_back(single_node);
                    DivergingNodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                    single_node.freeConnectedTable();
                    single_node.freePhaseTable();
                }

                else if (!strcmp (nodeType, "terminal"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        4, 
                        atol(nodeId), 
                        -1,
                        atoi(num_port),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for terminal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
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
                    Nodes.push_back(single_node);
                    TerminalNodes.push_back(single_node);
                    
                    single_node.freeConnectedLinks();
                }

                else if (!strcmp (nodeType, "garage"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        5, 
                        atol(nodeId), 
                        -1,
                        atoi(num_port),
                        strcmp(v2x, "on") == 0 ? true : false);

                    for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL;
                         e3 = e3->NextSiblingElement())
                    {
                        std::string val1 = e3->Value();
                        // port should be the same for normal
                        if (val1 == "port")
                        {
                            // create port instance + pushLink to
                            // IntersectionNode
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
                    Nodes.push_back(single_node);
                    GarageNodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                    single_node.freeConnectedTable();
                }
            }
        }
    }
    doc.Clear();

    TiXmlDocument doc_signal;
    doc_signal.LoadFile(NextSimIO::SignalXMLPath.string().c_str());
    // std::cout << "Loading NodeArr" << std::endl;

    if (!doc_signal.LoadFile(NextSimIO::SignalXMLPath.string().c_str()))
    {
        std::cout << "Loading failed (NodeArr-Signal.xml)" << std::endl;
        // std::cerr << doc_signal.ErrorDesc() << std::endl;
        return;
    }

    TiXmlElement *root_signal = doc_signal.FirstChildElement();

    for (TiXmlElement *e = root_signal->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        const char *nodeId = e->Attribute("id");
        if (!nodeId)   throw std::runtime_error ("Element should have 'id' attribute");

        auto it = std::find_if(
            Nodes.begin(), Nodes.end(),
            [&](IntersectionNode const &n) {
                return n.getId() == atol(nodeId);
            });
        IntersectionNode& node = *it;
        
        const char *cycle = e->Attribute("cycle");
        const char *offset = e->Attribute("offset");
        const char *order = e->Attribute("order");
        const char *phase_length = e->Attribute("phase_length"); 

        if (!cycle)   throw std::runtime_error ("Element should have 'cycle' attribute");
        if (!offset)   throw std::runtime_error ("Element should have 'offset' attribute");
        if (!order)   throw std::runtime_error ("Element should have 'order' attribute");
        if (!phase_length)   throw std::runtime_error ("Element should have 'phase_length' attribute");
        
        node.setCycle(atoi(cycle));
        node.setOffset(atoi(offset));
        auto iss2 = std::istringstream{ order };
        auto str2 = std::string{};
        while (iss2 >> str2)
        {
            node.pushPhaseOrder(atoi(str2.c_str()));
        }
        auto iss1 = std::istringstream{ phase_length };
        auto str1 = std::string{};
        while (iss1 >> str1)
        {
            node.pushPhaseLength(atoi(str1.c_str()));
        }

        for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL;
             e2 = e2->NextSiblingElement())
        {
            const char *phaseId = e2->Attribute("id");

            if (!phaseId)   throw std::runtime_error ("Element should have 'id' attribute");

            intersectionPhase phase(atol(phaseId));
            for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL; 
                 e3 = e3->NextSiblingElement())
            {
                const char *id_ref = e3->Attribute("id_ref");
                const char *priority = e3->Attribute("priority");
                
                if (!id_ref)   throw std::runtime_error ("Element should have 'id_ref' attribute");
                if (!priority)   throw std::runtime_error ("Element should have 'priority' attribute");

                phase.pushConnectionRef(atol(id_ref));
                phase.pushPriority(atof(priority));
            }
            node.pushPhase(phase);
        }

        node.setType(-1);  // signalized normal node
    }
    doc_signal.Clear();
};

void NodeArr::showArr()
{
    if (Nodes.size() == 0)
    {
        std::cout << "ITS EMPTY" << std::endl;
    }

    for (size_t i = 0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i].getId() << " " << Nodes[i].getNumConn() << " "
                  << Nodes[i].getNumLink() << std::endl;

        // Example:: getting the first connection ID of each intersection
        std::cout << "connID :" << Nodes[i].getConnections()[0].getConnId()
                  << std::endl;
    }
}
} // namespace NextSimIO