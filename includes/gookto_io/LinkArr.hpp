#ifndef LINKARR_H
#define LINKARR_H

#include <vector>
#include "LinkArr.hpp"
#include "InputLink.hpp"
// #include "InputLane.hpp"
// #include "InputCell.hpp"
// #include "InputSegment.hpp"
// #include "Temporal.hpp"


class LinkArr
{
private:
    std::vector<InputLink*> Links;

public:
    LinkArr();
    ~LinkArr();

    void showArr();

    //access functions
    std::vector<InputLink*> getLinks() { return Links; }


};

#endif