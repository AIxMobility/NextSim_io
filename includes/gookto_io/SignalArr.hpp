#ifndef SIGNALARR_H
#define SIGNALARR_H

#include <vector>
#include "Signalplans.hpp"

// #include "intersection/port.hpp"
// #include "intersection/connection.hpp"
#include "intersection/intersectionPhase.hpp"


class SignalArr
{
private:
    std::vector<Signalplans> Signals;

public:
    SignalArr();

    //access functions
    std::vector<Signalplans> getSignals() { return Signals; }

    //check
    //void showArr();
};

#endif