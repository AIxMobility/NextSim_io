#include "InputVeh.hpp"

#include <string>
#include <iostream>

#include "tinyxml.h"
#include "tinystr.h"

InputVeh::InputVeh(int id, int type) :
id(id), type(type)
{};


void InputVeh::addLink(int val)
{
    link_seq.push_back(val);
};