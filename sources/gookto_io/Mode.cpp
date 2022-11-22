#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/Mode.hpp>

Mode::Mode(int id, int scycle) : id(id), scycle(scycle){};

void Mode::setMicroLinkArr(std::string linkArr)
{
    std::string tempStr;
    size_t pos = 0;
    while ((pos = linkArr.find(" ")) != std::string::npos)
    {
        tempStr = linkArr.substr(0, pos);
        microLinkArr.push_back(std::stoi(tempStr));
        linkArr.erase(0, pos + 1);
    }
}

void Mode::setMesoLinkArr(std::string linkArr)
{
    std::string tempStr;
    size_t pos = 0;
    while ((pos = linkArr.find(" ")) != std::string::npos)
    {
        tempStr = linkArr.substr(0, pos);
        mesoLinkArr.push_back(std::stoi(tempStr));
        linkArr.erase(0, pos + 1);
    }
}