#pragma once
#include <vector>
#include <string>

class InputPax
{
private:
    int id;
    int type;
    double dpt_time;

    double reaction_time = 0;
    double jamgap = 0;
    double max_acc = 0;
    double max_dec = 0;
    double vehlength = 0;
    double vfree = 0;

    std::vector<int> link_seq;
    std::vector<int> node_seq;

public:
    InputPax(int id, int type, double dpt_time);


    void setReactionTime(double val) { reaction_time = val; }
    void setJamGap(double val) { jamgap = val; }
    void setMaxAcc(double val) { max_acc = val; }
    void setMaxDec(double val) { max_dec = val; }
    void setVehLen(double val) { vehlength = val; }
    void setVFree(double val) { vfree = val; }

    void addLink(int val);
    void addNode(int val);

    [[nodiscard]] const std::vector<int>& getLinkSeq() const
    {
        return link_seq;
    }

    [[nodiscard]] const std::vector<int>& getNodeSeq() const
    {
        return node_seq;
    }

    int getType() { return type; }
    int getId() { return id; }
    double getDptTime() { return dpt_time; }


    double getReactionTime() { return reaction_time; }
    double getJamGap() { return jamgap; }
    double getMaxAcc() { return max_acc; }
    double getMaxDec() { return max_dec; }
    double getVehLen() { return vehlength; }
    double getVFree() { return vfree; }
};
