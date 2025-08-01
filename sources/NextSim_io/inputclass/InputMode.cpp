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
InputMode::InputMode(int id, int sTime) : m_id(id), m_sTime(sTime){};

void InputMode::SetMicroLinkVector(std::string linkVector)
{
    std::stringstream ss(linkVector);
    int microid;

    while (ss >> microid)
        m_microLinkVector.push_back(microid);
}

void InputMode::SetMesoLinkVector(std::string linkVector)
{
    std::stringstream ss(linkVector);
    int mesoid;

    while (ss >> mesoid)
        m_mesoLinkVector.push_back(mesoid);
}
} // namespace NextSimIO