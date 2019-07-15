#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include <string>

#include "InputLink.hpp"
#include "LinkArr.hpp"
#include "NodeArr.hpp"

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"


using namespace std;

/* 
	The main file has to be in the same directory as the simple_network.xml
*/

int main(int argc, char* argv[])
{
	// Links Header Test
    LinkArr holy_links;

	NodeArr holy_nodes;


	// Intersections Header Test


	// Agents/ Vehicles Header Test

	cout << "Threshold 1" << endl;
	//holy_links.showArr();

	cout << "Threshold 2" << endl;

	//holy_nodes.showArr();


	//Example: accessing the nodes attributes --> got to check the type first
	cout << holy_nodes.getNodes()[0].getConnections()[0].getConnId() << endl;

	return 0;
}
