#pragma once
#include <vector>
#include <string>

class InputPax
{
private:
    int id;
    int type;
    float dpt_time;

    float reaction_time;
    float jamgap;
    float max_acc;
    float max_dec;
    float vehlength;
    float vfree;

    std::vector<int> link_seq;
    std::vector<int> node_seq;

public:
    InputPax(int id, int type, float dpt_time);

    
    void setReactionTime(float val) { reaction_time = val; }
    void setJamGap(float val) { jamgap = val; }
    void setMaxAcc(float val) { max_acc = val; }
    void setMaxDec(float val) { max_dec = val; }
    void setVehLen(float val) { vehlength = val; }
    void setVFree(float val) { vfree = val; }

    void addLink(int val);
    void addNode(int val);

    std::vector<int> getLinkSeq() { return link_seq; }
    std::vector<int> getNodeSeq() { return node_seq; }

    int getType() { return type; }
    int getId() { return id; }
    float getDptTime() { return dpt_time; }

    
    float getReactionTime() { return reaction_time; }
    float getJamGap() { return jamgap; }
    float getMaxAcc() { return max_acc; }
    float getMaxDec() { return max_dec; }
    float getVehLen() { return vehlength; }
    float getVFree() { return vfree; }
};