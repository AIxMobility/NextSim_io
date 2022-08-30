#include <iostream>
#include <sstream>
#include <string>

#include <gookto_io/IntersectionNode.hpp>
#include <gookto_io/NodeArr.hpp>

#include <gookto_io/intersection/connection.hpp>
#include <gookto_io/intersection/port.hpp>

#include <gookto_io/tinyapi/tinystr.h>
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/FilePath.hpp>

NodeArr::NodeArr()
{
    TiXmlDocument doc;

    doc.LoadFile(STSIO::NetworkXMLPath.string().c_str());
    std::cout << "Loading NodeArr" << std::endl;

    if (!doc.LoadFile(STSIO::NetworkXMLPath.string().c_str()))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *e = root->FirstChildElement(); e != NULL;
         e = e->NextSiblingElement())
    {
        std::string elemName2 = e->Value();

        if (elemName2 == "nodes")
        {
            std::cout << "Got nodes" << std::endl;

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

                // TYPES OF NODES --> intersection, normal, terminal
                if (!strcmp (nodeType, "intersection"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        0,
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
                            const char *length = e3->Attribute("length");
                            const char *priority = e3->Attribute("priority");

                            if (!connectionId)   throw std::runtime_error ("Element should have 'id' attribute");
                            if (!from_link)   throw std::runtime_error ("Element should have 'from_link' attribute");
                            if (!from_lane)   throw std::runtime_error ("Element should have 'from_lane' attribute");
                            if (!to_link)   throw std::runtime_error ("Element should have 'to_link' attribute");
                            if (!to_lane)   throw std::runtime_error ("Element should have 'to_lane' attribute");
                            if (!length)   throw std::runtime_error ("Element should have 'length' attribute");
                            if (!priority)   priority = "1";

                            connection single_connection(
                                atol(connectionId),
                                atol(from_link),
                                atol(from_lane),
                                atol(to_link),
                                atol(to_lane),
                                atof(priority),
                                atof(length));
                            single_node.pushConnection(single_connection);
                        }


                    }
                    Nodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                    single_node.freeConnectedTable();
                }

                else if (!strcmp (nodeType, "normal"))
                {
                    // std::cout << "got normal" << std::endl;
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        1, atol(nodeId), -1,
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
                            const char *length = e3->Attribute("length");
                            const char *priority = e3->Attribute("priority");

                            if (!connectionId)   throw std::runtime_error ("Element should have 'id' attribute");
                            if (!from_link)   throw std::runtime_error ("Element should have 'from_link' attribute");
                            if (!from_lane)   throw std::runtime_error ("Element should have 'from_lane' attribute");
                            if (!to_link)   throw std::runtime_error ("Element should have 'to_link' attribute");
                            if (!to_lane)   throw std::runtime_error ("Element should have 'to_lane' attribute");
                            if (!length)   throw std::runtime_error ("Element should have 'length' attribute");
                            if (!priority)   priority = "1";

                            connection single_connection(
                                atol(connectionId),
                                atol(from_link),
                                atol(from_lane),
                                atol(to_link),
                                atol(to_lane),
                                atof(priority),
                                atof(length));
                            single_node.pushConnection(single_connection);
                        }
                    }
                    Nodes.push_back(single_node);

                    single_node.freeConnectedLinks();
                }

                else if (!strcmp (nodeType, "terminal"))
                {
                    // create single IntersectionNode instance here
                    IntersectionNode single_node(
                        2, atol(nodeId), -1,
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

                    single_node.freeConnectedLinks();
                }
            }
        }
    }
    doc.Clear();
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