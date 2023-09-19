#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <gookto_io/InputMode.hpp>

InputMode::InputMode(int id, int scycle) : id(id), scycle(scycle){};

void InputMode::setMicroLinkArr(std::string linkArr)
{
    std::stringstream ss(linkArr);
    int microid;

    while (ss >> microid)
        microLinkArr.push_back(microid);
}

void InputMode::setMesoLinkArr(std::string linkArr)
{
    std::stringstream ss(linkArr);
    int mesoid;

    while (ss >> mesoid)
        mesoLinkArr.push_back(mesoid);
}