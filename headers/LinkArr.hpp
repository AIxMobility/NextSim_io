#ifndef LINKARR_H
#define LINKARR_H

#pragma once
#include <vector>
#include "InputLink.hpp"

class LinkArr
{
private:
    std::vector<InputLink> Links;

public:
    LinkArr();

    //
    void showArr();
    void putLink(InputLink ele);


};

#endif