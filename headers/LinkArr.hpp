#ifndef LINKARR_H
#define LINKARR_H

#include <vector>
#include "InputLink.hpp"

class LinkArr
{
private:
    std::vector<InputLink> Links;

public:
    LinkArr();
    
    void showArr();

    //access functions
    std::vector<InputLink> getLinks() { return Links; }


};

#endif