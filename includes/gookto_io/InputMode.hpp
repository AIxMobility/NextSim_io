#ifndef MODE_H
#define MODE_H

#include <vector>
#include <string>

class InputMode
{
private:
    int id, scycle;
    std::vector<int> microLinkArr;
    std::vector<int> mesoLinkArr;

public:
    InputMode(int id, int scycle);

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