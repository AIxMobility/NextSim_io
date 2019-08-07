#include "NodeArr.hpp"
#include <string>
#include <iostream>
#include "IntersectionNode.hpp"

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"

#include "tinyxml.h"
#include "tinystr.h"

NodeArr::NodeArr()
{
    TiXmlDocument doc;

    doc.LoadFile("simple_network.xml");
    std::cout << "got xml file loaded" << std::endl;

    if (!doc.LoadFile("simple_network.xml"))
    {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        std::string elemName = elem->Value();

        const char *attr;
        if (elemName == "roads")
        {
            std::cout << "Got roads" << std::endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                std::string elemName2 = e->Value();

                if (elemName2 == "nodes")
                {
                    std::cout << "Got nodes" << std::endl;

                    for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL; e2 = e2->NextSiblingElement())
                    {   
                        std::string att1 = e2->Attribute("type");

                        // TYPES OF NODES --> intersection, normal, terminal
                        if (att1 == "intersection")
                        {
                            //create single IntersectionNode instance here
                            IntersectionNode single_node(0, atoi(e2->Attribute("id")), atoi(e2->Attribute("num_connection")), atoi(e2->Attribute("num_port")));
                            
                            for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL; e3 = e3->NextSiblingElement())
                            {   
                                std::string val1 = e3->Value();
                                if (val1 == "port")
                                {
                                    //create port instance + pushLink to IntersectionNode
                                    int temp = -1;
                                    std::string att2 = e3->Attribute("type");
                                    if (att2 == "in")
                                    {
                                        temp = 1;
                                    }
                                    port single_link(atoi(e3->Attribute("link_id")), atoi(e3->Attribute("direction")), temp);
                                    single_node.pushLink(single_link);
                                }

                                else if (val1 == "connection")
                                {
                                    connection single_connection(atoi(e3->Attribute("id")), atoi(e3->Attribute("from_link")), atoi(e3->Attribute("from_lane")),atoi(e3->Attribute("to_link")), atoi(e3->Attribute("to_lane")), 0);
                                    single_node.pushConnection(single_connection);
                                }

                                else if (val1 == "phase")
                                {
                                    intersectionPhase single_phase(atoi(e2->Attribute("id")));
                                    for (TiXmlElement *e4 = e3->FirstChildElement(); e4 != NULL; e4 = e4->NextSiblingElement())
                                    {
                                        std::string val2 = e4->Value();
                                        if (val2 == "connection")
                                        {
                                            single_phase.pushConnectionRef( atoi(e4->Attribute("id_ref")) );
                                            single_phase.pushPriority( atof(e4->Attribute("priority")) );
                                        }
                                    }
                                    single_node.pushPhase(single_phase);
                                }

                                else if (val1 =="signal_plan")
                                {

                                }
                            }
                            Nodes.push_back(single_node);
                            
                            single_node.freeConnectedLinks();
                            single_node.freeConnectedTable();
                            single_node.freePhaseTable();
                        }

                        else if (att1 == "normal")
                        {
                            //create single IntersectionNode instance here
                            IntersectionNode single_node(1, atoi(e2->Attribute("id")), -1, atoi(e2->Attribute("num_port")));

                            for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL; e3 = e3->NextSiblingElement())
                            {
                                std::string val1 = e3->Value();
                                //port should be the same for normal 
                                if (val1 == "port")
                                {
                                    //create port instance + pushLink to IntersectionNode
                                    int temp = -1;
                                    std::string att2 = e3->Attribute("type");
                                    if (att2 == "in")
                                    {
                                        temp = 1;
                                    }
                                    port single_link(atoi(e3->Attribute("link_id")), atoi(e3->Attribute("direction")), temp);
                                    single_node.pushLink(single_link);
                                }
                            }
                            Nodes.push_back(single_node);

                            single_node.freeConnectedLinks();
                        }

                        else if (att1 == "terminal")
                        {
                            //create single IntersectionNode instance here
                            IntersectionNode single_node(2, atoi(e2->Attribute("id")), -1, atoi(e2->Attribute("num_port")));

                            for (TiXmlElement *e3 = e2->FirstChildElement(); e3 != NULL; e3 = e3->NextSiblingElement())
                            {
                                std::string val1 = e3->Value();
                                //port should be the same for normal
                                if (val1 == "port")
                                {
                                    //create port instance + pushLink to IntersectionNode
                                    int temp = -1;
                                    std::string att2 = e3->Attribute("type");
                                    if (att2 == "in")
                                    {
                                        temp = 1;
                                    }
                                    port single_link(atoi(e3->Attribute("link_id")), atoi(e3->Attribute("direction")), temp);
                                    single_node.pushLink(single_link);
                                }
                            }
                            Nodes.push_back(single_node);

                            single_node.freeConnectedLinks();
                        }
                    }
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

    for (int i=0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i].getId() << " " << Nodes[i].getNumConn() << " " << Nodes[i].getNumLink() << std::endl;

        //Example:: getting the first connection ID of each intersection
        std::cout <<"connID :" << Nodes[i].getConnections()[0].getConnId() << std::endl;
    }
} 