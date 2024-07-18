#pragma once
#include <vector>
#include <string>
#include <iostream>

class intersectionPhase
{
private:
    int id;
    std::vector<int> connectionRef; 
    std::vector<double> priority;


public:
    intersectionPhase(int id);

    void pushConnectionRef(int val);
    void pushPriority(double val);

    //return connectionRef and Priority

    int getId() { return id; }
    std::vector<int> getConnRef() { return connectionRef; }
    std::vector<double> getPriority() { return priority; }


};