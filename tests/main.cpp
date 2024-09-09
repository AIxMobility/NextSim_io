//
// Created by Jae Hwan Jeong on 1/7/20.
//
#include <NextSim_io/tinyapi/tinyxml.h>
#include <NextSim_io/tinyapi/tinystr.h>
#include <iostream>
#include <string>

#include <NextSim_io/parser/LinkArr.hpp>
#include <NextSim_io/parser/NodeArr.hpp>
#include <NextSim_io/parser/AgentsArr.hpp>
#include <NextSim_io/parser/ParamArr.hpp>

using namespace std;

/*
	The main file has to be in the same directory as the simple_network.xml
*/

namespace NextSimIO
{
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

    // cout << holy_links.getLinks()[0].GetLaneIds()[0] << endl;


    return 0;
}
} // namespace NextSimIO
