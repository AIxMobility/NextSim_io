#include "IntersectionNode.hpp"

#include "intersection/port.hpp"
#include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"

#include <vector>

#include "tinyxml.h"
#include "tinystr.h"

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
