#include <gookto_io/IntersectionNode.hpp>
#include <gookto_io/intersection/port.hpp>
#include <gookto_io/intersection/connection.hpp>

#include <vector>


IntersectionNode::IntersectionNode(int type, int id, int num_connection, int num_port, bool v2xActive) : 
type(type), id(id), numConnections(num_connection), numLinks(num_port), v2xActive(v2xActive)
{
    //initialize size of connectedLinks --> numLinks
    //initialize size of connectionTable --> numConnections

};




//setting the Variables
void IntersectionNode::pushConnection(connection conn)
{
    connectionTable.push_back(conn);
};

void IntersectionNode::pushLink(port link)
{
    connectedLinks.push_back(link);
};

