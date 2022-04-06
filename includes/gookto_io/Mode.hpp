#ifndef MODE_H
#define MODE_H

#include <vector>
#include <string>

class Mode
{
private:
    int id, scycle, ecycle;
    std::vector<int> microLinkArr;
    std::vector<int> mesoLinkArr;

public:
    Mode(int id, int scycle, int ecycle);

    // string to vector
    void setMicroLinkArr(std::string linkArr);
    void setMesoLinkArr(std::string linkArr);

    //access function
    int getId()
    {
        return id;
    }
    int getScycle()
    {
        return scycle;
    }
    int getEcycle()
    {
        return ecycle;
    }
    std::vector<int> getMicroLinkArr()
    {
        return microLinkArr;
    }
    std::vector<int> getMesoLinkArr()
    {
        return mesoLinkArr;
    }
};

#endif