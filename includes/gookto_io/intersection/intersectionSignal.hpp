#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <intersectionPhase.hpp>

class intersectionSignal
{
private:
    int id;
    std::vector<intersectionPhase> phaseTable; //intersectionPhase:  ID, connectionId (list), priority(list)


public:
    intersectionSignal(int id);

    void pushConnectionRef(int val);
    void pushPriority(double val);

    //return connectionRef and Priority

    int getId() { return id; }
    std::vector<int> getConnRef() { return connectionRef; }
    std::vector<double> getPriority() { return priority; }


};