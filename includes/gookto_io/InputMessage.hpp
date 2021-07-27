#ifndef INPUTMESSAGE_H
#define INPUTMESSAGE_H

#include <iostream>
#include <string>
#include <vector>

class InputMessage
{
private:
    int id;
    int stime;
    int etime;
    int msg_type;
    int value;

    // unique to Region Message
    int node_id = 0;

    // unique to Vehicle Message
    int veh_id = 0;

public:
    // Constructor
    InputMessage(int id, int stime, int etime, int msg_type, int value);

    // access functions
    int getId()
    {
        return id;
    }
    int getStime()
    {
        return stime;
    }
    int getEtime()
    {
        return etime;
    }
    int getMsg_type()
    {
        return msg_type;
    }
    int getvalue()
    {
        return value;
    }
    int getNode_id()
    {
        return node_id;
    }
    int getVeh_id()
    {
        return veh_id;
    }
    void setNode_id (int nnode_id)
    {
        node_id = nnode_id;
    }
    void setVeh_id (int nveh_id)
    {
        veh_id = nveh_id;
    }
};

#endif