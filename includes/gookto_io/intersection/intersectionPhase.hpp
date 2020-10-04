#pragma once
#include <vector>
#include <string>
#include <iostream>

class intersectionPhase
{
private:
    int id;
    std::vector<long int> connectionRef; 
    std::vector<float> priority;


public:
    intersectionPhase(int id);

    void pushConnectionRef(long int val);
    void pushPriority(float val);

    //return connectionRef and Priority

    long int getId() { return id; }
    std::vector<long int> getConnRef() { return connectionRef; }
    std::vector<float> getPriority() { return priority; }


};