#pragma once
#include <vector>
#include <string>
#include <iostream>

class intersectionPhase
{
private:
    int id;
    std::vector<int> connectionRef; 
    std::vector<int> priority;


public:
    intersectionPhase(int id);

    void pushConnectionRef(int val);
    void pushPriority(int val);

    //return connectionRef and Priority

    int getId() { return id; }
    std::vector<int> getConnRef() { return connectionRef; }
    std::vector<int> getPriority() { return priority; }


};