#pragma once
#include <vector>
#include <string>
#include <iostream>

class InputVeh
{
private:
    int id;
    int type;
    std::vector<int> link_seq;


public:
    InputVeh(int id, int type);

};