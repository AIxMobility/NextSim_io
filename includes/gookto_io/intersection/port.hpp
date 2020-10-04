#pragma once
#include <vector>
#include <string>
#include <iostream>

class port
{
private:
    long int linkId;
    int direction;
    int type;

public:
    port(long int id, int dir, int type);

    //access functions
    long int getLinkId() { return linkId; }
    int getDir() { return direction; }
    int getType() { return type; }
    /*
        link coming in: 1
        link going out: -1
     */

};