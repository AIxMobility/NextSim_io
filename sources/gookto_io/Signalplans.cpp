#include <gookto_io/Signalplans.hpp>
#include <gookto_io/intersection/intersectionPhase.hpp>

#include <vector>


Signalplans::Signalplans(int id, double end, double start): 
id(id), start(start), end(end)
{
    //initialize size of connectedLinks --> numLinks
    //initialize size of connectionTable --> numConnections

};



//setting the Variables


void Signalplans::pushPhase(intersectionPhase phase)
{
    phaseTable.push_back(phase);
};

void Signalplans::pushPhaseLength(int length)
{
    phaseLength.push_back(length);
}

void Signalplans::pushPhaseOrder(int order)
{
    phaseOrder.push_back(order);
}

void Signalplans::setPhaseOffset( int offset )
{
    phaseOffset = offset;
}
