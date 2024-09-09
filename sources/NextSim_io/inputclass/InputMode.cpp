/**
* NextSim Captain
* @file InputMode.cpp
* @version 1.0
* @author Jae Hwan Jung, Justin Kim
*/

#include <sstream>

#include <NextSim_io/inputclass/InputMode.hpp>

namespace NextSimIO
{
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
} // namespace NextSimIO