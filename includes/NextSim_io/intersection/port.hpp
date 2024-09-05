#pragma once
#include <vector>
#include <string>
#include <iostream>

class port
{
private:
    int linkId;
    int direction;
    int type;

public:
    port(int id, int dir, int type);

    int getLinkId() { return linkId; }
    int getDir() { return direction; }
    int getType() { return type; }
    /*
        link coming in: 1
        link going out: -1
     */

};