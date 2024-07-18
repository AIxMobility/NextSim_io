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
    ~LinkArr() = default;
    LinkArr(const LinkArr &link) = default;
    LinkArr &operator=(const LinkArr &link) = default;

    void showArr();

    //access functions
    std::vector<InputLink> getLinks() { return Links; }
};

#endif