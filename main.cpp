#include "tinyapi/tinyxml.h"
#include "tinyapi/tinystr.h"
#include <iostream>
#include <string>

#include "includes/gookto_io/InputLink.hpp"
#include "includes/gookto_io/InputAgents.hpp"
#include "includes/gookto_io/LinkArr.hpp"
#include "includes/gookto_io/NodeArr.hpp"
#include "includes/gookto_io/AgentsArr.hpp"
#include "includes/gookto_io/ParamArr.hpp"

#include "includes/gookto_io/intersection/port.hpp"
#include "includes/gookto_io/intersection/connection.hpp"
#include "includes/gookto_io/intersection/intersectionPhase.hpp"

using namespace std;

/* 
	The main file has to be in the same directory as the simple_network.xml
*/

int main(int argc, char* argv[])
{
	// Links Header Test
    LinkArr holy_links;

	NodeArr holy_nodes;

	AgentsArr holy_vehicles;

	ParamArr holy_params;

	cout << "read till agents" << endl;


	holy_nodes.getNodes()[0].getType();

	// Intersections Header Test


	// Agents/ Vehicles Header Test

	cout << "Threshold 1" << endl;
	//holy_links.showArr();

	cout << "Threshold 2" << endl;

	//holy_nodes.showArr();

	cout << "Threshold 3" << endl;

	holy_vehicles.showArr();
	// WORKS


	//Example: accessing the nodes attributes --> got to check the type first
	// cout << holy_nodes.getNodes()[0].getConnections()[0].getFromLink() << endl;

	cout << "Number of Nodes :" << endl;
	cout << holy_nodes.getNodes().size() << endl;

	cout << holy_nodes.getNodes()[2].getType() << endl;

	cout << "ParamArr test, meso max_flow:" << endl;

	cout << holy_params.getMaxFlow() << endl;

	return 0;
}
