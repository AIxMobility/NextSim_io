#ifndef INPUTVEH_H
#define INPUTVEH_H

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


    void addLink(int val);

    //access functions
    int getId() { return id; }
    int getType() { return type; }
    std::vector<int> getLinkSeq() { return link_seq; }

};


#endif