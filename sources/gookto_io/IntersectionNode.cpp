#include <gookto_io/IntersectionNode.hpp>

#include <gookto_io/intersection/port.hpp>
#include <gookto_io/intersection/connection.hpp>
#include <gookto_io/intersection/intersectionPhase.hpp>

#include <vector>

#include <gookto_io/tinyapi/tinyxml.h>
#include <gookto_io/tinyapi/tinystr.h>

#include <string>
#include <iostream>


IntersectionNode::IntersectionNode(int type, int id, int num_connection, int num_port) : 
type(type), id(id), numConnections(num_connection), numLinks(num_port)
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

void IntersectionNode::pushPhase(intersectionPhase phase)
{
    phaseTable.push_back(phase);
};

void IntersectionNode::pushPhaseLength(int length)
{
    phaseLength.push_back(length);
}



//Setting the Connection Priority from given Phase #
void IntersectionNode::initPhase()
{
    for (int i=0; i < numConnections; i++)
    {
        //connectionTable[i].priority = 0;
        //getPriority()
    }
};

void IntersectionNode::setPhase( int phase )
{
    //phaseTable[phase]
};
