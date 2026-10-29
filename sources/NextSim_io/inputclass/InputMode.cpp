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

void InputMode::SetMicroNodeVector(std::string nodeVector)
{
    std::stringstream ss(nodeVector);
    int microid;

    while (ss >> microid)
        m_microNodeVector.push_back(microid);
}

void InputMode::SetMesoNodeVector(std::string nodeVector)
{
    std::stringstream ss(nodeVector);
    int mesoid;

    while (ss >> mesoid)
        m_mesoNodeVector.push_back(mesoid);
}
} // namespace NextSimIO