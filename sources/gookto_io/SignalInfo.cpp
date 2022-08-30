#include <gookto_io/Signalplans.hpp>
#include <gookto_io/intersection/signalInfo.hpp>

#include <gookto_io/intersection/intersectionPhase.hpp>

#include <vector>


signalInfo::signalInfo(int node) : 
node(node)
{
    //initialize size of connectedLinks --> numLinks
    //initialize size of connectionTable --> numConnections

};



//setting the Variables


void signalInfo::pushPhase(intersectionPhase phase)
{
    phaseTable.push_back(phase);
};

void signalInfo::pushPhaseLength(int length)
{
    phaseLength.push_back(length);
}

void signalInfo::pushPhaseOrder(int order)
{
    phaseOrder.push_back(order);
}

void signalInfo::setPhaseOffset( int offset )
{
    phaseOffset = offset;
}
