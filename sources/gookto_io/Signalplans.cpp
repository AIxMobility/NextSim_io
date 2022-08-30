#include <gookto_io/Signalplans.hpp>
#include <gookto_io/intersection/signalInfo.hpp>

#include <gookto_io/intersection/intersectionPhase.hpp>

#include <vector>


Signalplans::Signalplans(int id, double end, double start): 
id(id), end(end),start(start)
{
    //initialize size of connectedLinks --> numLinks
    //initialize size of connectionTable --> numConnections

};



//setting the Variables


void Signalplans::pushInfo(signalInfo node)
{
    nodeSignal.push_back(node);
};
