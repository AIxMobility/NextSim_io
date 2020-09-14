//
// Created by Jae Hwan Jeong on 1/7/20.
//
#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>
#include <iostream>
#include <string>

#include <gookto_io/InputLink.hpp>

#include <gookto_io/InputAgents.hpp>
#include <gookto_io/LinkArr.hpp>
#include <gookto_io/NodeArr.hpp>
#include <gookto_io/AgentsArr.hpp>
#include <gookto_io/ParamArr.hpp>

#include <gookto_io/intersection/port.hpp>
#include <gookto_io/intersection/connection.hpp>
#include <gookto_io/intersection/intersectionPhase.hpp>

using namespace std;

/*
	The main file has to be in the same directory as the simple_network.xml
*/

int main(int argc, char* argv[])
{

    // Links Header Test
    LinkArr holy_links;

    NodeArr holy_nodes;
    cout << "read till agents" << endl;


    holy_nodes.getNodes()[0].getType();


    //Example: accessing the nodes attributes --> got to check the type first
    // cout << holy_nodes.getNodes()[0].getConnections()[0].getFromLink() << endl;

    cout << "Number of Nodes :" << endl;

    cout << holy_nodes.getNodes().size() << endl;

    cout << holy_nodes.getNodes()[2].getType() << endl;

    // cout << holy_links.getLinks()[0].getLaneIds()[0] << endl;


    return 0;
}
