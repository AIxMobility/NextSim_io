#include "LinkArr.hpp"
#include <string>
#include <iostream>
#include "InputLink.hpp"

LinkArr::LinkArr(){};

void LinkArr::showArr() 
{
    for (int i=0; i< Links.size(); i++)
    {
        std::cout << Links[i].getId() << std::endl;
    }

}

void LinkArr::putLink(InputLink ele)
{
    Links.push_back(ele);
}

// Function declarations with reference to the name space
